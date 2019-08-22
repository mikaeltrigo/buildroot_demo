#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <asm/io.h>

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/rwsem.h>
#include <linux/slab.h>

#include "control.h"

static struct rw_semaphore rw_sem;
static struct control_struct {
	dev_t dev_maj_min;
	struct class *class;
	struct device *device;
	struct cdev cdev;
	void* iomem;
} control_data;

#ifdef FAKE_FPGA
static char fpga_mem_space[FPGA_MEM_SIZE];
#endif

/*-------------------------------------------------------------------------*/
int control_is_in_fpga_boundary(loff_t pos, size_t length)
{
	return pos + length < FPGA_MEM_SIZE;
}

/*-------------------------------------------------------------------------*/
static ssize_t control_read(struct file *filep, char *buff,	size_t len,
		loff_t *offset)
{
	int error, retVal;
	char *temp_buf;

	if(control_is_in_fpga_boundary(*offset, len))
	{
		down_read(&rw_sem);
#ifdef FAKE_FPGA
		error = copy_to_user(buff, control_data.iomem + *offset, len);
#else
		/* XXX :
		 * Is it safe to do so or should we use copy_to_user and a kernel space
		 * buffer?
		 */
		temp_buf = kmalloc(len, GFP_KERNEL);
		if (temp_buf == 0) {
			printk(KERN_WARNING "Allocation of temp_buf for read failed\n");
			return -ENOMEM;
		}
		memcpy_fromio(temp_buf, control_data.iomem + *offset, len);
		error = copy_to_user(buff, temp_buf, len);
		kfree(temp_buf);
#endif
		up_read(&rw_sem);

		if(error < 0)
			retVal = error;
		else
			retVal = len;
	}
	else
	{
		printk(KERN_WARNING "Reading outside of FPGA boundary\n");
		return -EINVAL;
	}

	return retVal;
}

/*-------------------------------------------------------------------------*/
static ssize_t control_write(struct file *filep, const char *buff,
		size_t len, loff_t * offset)
{
	int error, retVal;
	char *temp_buf;

	if(control_is_in_fpga_boundary(*offset, len))
	{
		down_write(&rw_sem);
#ifdef FAKE_FPGA
		error = copy_from_user(control_data.iomem + *offset, buff, len);
#else
		temp_buf = kmalloc(len, GFP_KERNEL);
		if (temp_buf == 0) {
			printk(KERN_WARNING "Allocation of temp_buf for write failed\n");
			return -ENOMEM;
		}
		error = copy_from_user(temp_buf, buff, len);
		memcpy_toio(control_data.iomem + *offset, temp_buf, len);
		kfree(temp_buf);
#endif
		up_write(&rw_sem);

		if(error < 0)
			retVal = error;
		else
			retVal = len;
	}
	else
	{
		printk(KERN_WARNING "Writing outside of FPGA boundary\n");
		return -EINVAL;
	}

	return retVal;
}

/*-------------------------------------------------------------------------*/
static loff_t control_llseek(struct file *filep, loff_t off, int whence)
{
	loff_t new_pos;

	// SEEK_SET
	if(whence == 0)
	{
		if(off > FPGA_MEM_SIZE)
		{
			printk("Seeking outside of FPGA boundaries\n");
			return -EINVAL;
		}
		new_pos = off;
	}

	// SEEK_CUR
	else if(whence == 1)
	{
		new_pos = filep->f_pos + off;
		if(new_pos > FPGA_MEM_SIZE)
		{
			printk("Seeking outside of FPGA boundaries\n");
			return -EINVAL;
		}
	}

	// SEEK_END
	else if(whence == 2)
	{
		if(off != 0)
		{
			printk("Cannot seek further than the end of FPGA address space\n");
			return -EINVAL;
		}
		new_pos = FPGA_MEM_SIZE;
	}

	// Should never happen
	else return -EINVAL;

	filep->f_pos = new_pos;
	return new_pos;
}

/*-------------------------------------------------------------------------*/
static struct file_operations control_fops = {
		.owner   = THIS_MODULE,
		.read    = control_read,
		.write   = control_write,
		.llseek  = control_llseek,
};

/*-------------------------------------------------------------------------*/
static int __init control_init(void)
{
	int ret = 0;

	// Allocate major, minor number
	ret = alloc_chrdev_region(&control_data.dev_maj_min, 0, 1,
			CHAR_DEV_NAME);
	if (ret < 0)
	{
		printk(KERN_ERR "Couldn't allocate major number: %i\n", ret);
		return ret;
	}

	// Create the driver class
	control_data.class = class_create(THIS_MODULE, "fpga");
	if (IS_ERR(control_data.class))
	{
		ret = PTR_ERR(control_data.class);
		printk(KERN_ERR "Couldn't create class: %i\n", ret);
		goto error_chardev;
	}

	// Create the device itself
	control_data.device = device_create(control_data.class, NULL,
			control_data.dev_maj_min, NULL, CHAR_DEV_NAME);
	if (IS_ERR(control_data.device))
	{
		ret = PTR_ERR(control_data.device);
		printk(KERN_ERR "Couldn't create device: %i\n", ret);
		goto error_class;
	}

	// Make the device ready to get file operations
	cdev_init(&control_data.cdev, &control_fops);
	ret = cdev_add(&control_data.cdev, control_data.dev_maj_min, 1);
	if(ret < 0)
	{
		printk(KERN_ERR "Couldn't add char device: %i\n", ret);
		goto error_device;
	}

	// Map FPGA memory
#ifdef FAKE_FPGA
	control_data.iomem = &fpga_mem_space;
#else
	control_data.iomem = ioremap(FPGA_START_ADD, FPGA_MEM_SIZE);
	if(control_data.iomem == NULL)
	{
		printk(KERN_ERR "Couldn't map FPGA memory area\n");
		ret = -ENOMEM;
		goto error_cdev;
	}
#endif

	// Misc internal variable initalization
	init_rwsem(&rw_sem);

	// Sucess
	printk(KERN_INFO "fpga-control module successfully loaded!\n");
	return 0;

#ifndef FAKE_FPGA
error_cdev:
	cdev_del(&control_data.cdev);
#endif
error_device:
	device_destroy(control_data.class, control_data.dev_maj_min);
error_class:
	class_destroy(control_data.class);
error_chardev:
	unregister_chrdev_region(control_data.dev_maj_min, 1);

	return ret;
}

/*-------------------------------------------------------------------------*/
static void __exit control_exit(void)
{
#ifndef FAKE_FPGA
	iounmap(control_data.iomem);
#endif
	cdev_del(&control_data.cdev);
	device_destroy(control_data.class, control_data.dev_maj_min);
	class_destroy(control_data.class);
	unregister_chrdev_region(control_data.dev_maj_min, 1);
}

/*-------------------------------------------------------------------------*/

module_init(control_init);
module_exit(control_exit);

MODULE_AUTHOR("MIKAEL TRIGO");
MODULE_DESCRIPTION("FPGA control module");
MODULE_LICENSE("GPL");
