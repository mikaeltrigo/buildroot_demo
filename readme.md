# Table of Contents
1. [Introduction](##Introduction)
2. [Preparation](##Preparation)
3. [Inittal Build](##InitialBuild)
4. [Create-SD-card](##Create-SD-card)
5. [Update-an-existing-Build](##Update-an-existing-Build)
	5a. [Update-FPGA-FSB](###Update-FPGA-FSB)
	5b. [Update-Buildroot ](###Update-Buildroot)
	5c. [Update-Package](###Update-Package)
	5d. [Update-Uboot](###Update-Uboot)
	5e. [Update-kernel](###Update-kernel)
	5f.  [Update-Overlay](###Update-Overlay)


## Introduction

This document describes how to use this repository to build a minimal Linux system for the powertime with Buildroot

If you are interested on the base of this, you can check what Pavol has done below:

Furthermore it shows how to integrate a third-party [package](https://github.com/pavolk/xilinx_axidma.git) into a buildroot-based system.

In the subdirectory [doc](https://github.com/pavolk/buildroot_demo/blob/master/doc/) you'll find some slides, that you can follow to get started with the repository and/or use it as a base for your system.

## Preparation

1. Clone this repository with the buildroot as submodule

```
git clone https://github.com/mikaeltrigo/buildroot_swisstiming.git
cd buildroot_swisstiming
git submodule update --init
```

if you want to download the example from Pavol:

```
git clone https://github.com/pavolk/buildroot_demo.git
cd buildroot_demo
git submodule update --init
```

## InitialBuild


```
cd buildroot_swisstiming
mkdir build
cd build
make -C ../buildroot O=$(pwd) BR2_EXTERNAL=.. powertime3_defconfig
make
```

## Create-SD-card

I have created a script that is found in buildroot_swisstiming/board/powertime3/install-sd.sh.

After an initial build, you have to copy it to the images folder (only need to do it once, or after you do a make clean)

```
cd buildroot_swisstiming
cp ../board/powertime3/install-sd.sh images/
```

Then you can insert an SD card: 
```
cd images
sudo ./install-sd.sh /dev/sde boot.bin rootfs.tar format
```
**NOTE:** The output device name (of="device name") may vary (e.g. /dev/sde), check with dmesg when inserting the SD crd what is the device name

For information , this is how Pavol is proposing to do it :
```
cd buildroot_demo/build
umount /dev/mmcblk0p*
sudo dd if=images/sdcard.img of=/dev/mmcblk0
```
## Update-an-existing-Build
the command make will always build the change that the system see in buildroot.  it will the execute the post image script : [post-image.sh](https://github.com/mikaeltrigo/buildroot_swisstiming/blob/master/board/powertime3/post-image.sh)
it will do the following:

 - Creating boot.bin.
- Compiling the boot-script for mmcboot-rootfs 
- compiling the  device-tree 
- copying all the images in images/

### Update-FPGA-FSBL
copy the bit file and the FSBL to  fpga.bit and FSBL.elf in [http://buildroot_swisstiming/board/powertime3/pre-built/](http://buildroot_swisstiming/board/powertime3/pre-built/)
the command make will automatically build a new boot.bin


### Update-Buildroot 
If you mean to change a buildroot config( for exemple adding a package etc)  with menuconfig , you  must  always save the config (with savedefconfig)  if you do a change that you want to keep
```
make menuconfig
make savedefconfig
make
```
### Update-Package
All the Linux driver written by us , the modules, the external source such as PTP SoCe, the Lua libraries written by us, our application, they are all declared in the packages. We usually don't put the source, but a download Git link with release version to be downloaded.

If you have to update a package ( buildroot_swisstiming/package) , you should always go and update the version in **mk file** of the packages.

For example, there is a new pwr_lcd_app version. See the steps below in order to have it in next release of the system:
- You push the latest stable change of the app 
- go to [https://github.com/](https://github.com/) and to the app project  (here ) [https://github.com/mikaeltrigo/pwrt3_lcd_app](https://github.com/mikaeltrigo/pwrt3_lcd_app)) 
- go the tab release
- Draft a new release
- edit  buildroot_swisstiming/package/pwrt3lcdapp/pwrt3lcdapp.mk with the correct version
- do the follwing command

```
cd build
make pwrt3lcdapp-dirclean
make
```
If for exemple you have a patch that you applied  to the source you downloaded , it will only be applied when you do the first make. In this case you shoudl do 
```
cd build
make pwrt3lcdapp-dirclean
make pwrt3lcdapp
make
```
### Update -uBoot
The commande to update uboot is the same as the package 
```
cd build
make uboot-rebuild
make
```
or if there is patch modification
```
cd build
make uboot-dirclean
make uboot
make
```

Attention Builroot is configure to take external DTS ,config  and patches that are found in 
[http://buildroot_swisstiming/board/powertime3/uboot/](http://buildroot_swisstiming/board/powertime3/uboot/) under DTS and config.  
ps: this buildroot can be seen in the powertime3_defconfig : 
```
BR2_TARGET_UBOOT_CUSTOM_DTS_PATH="${BR2_EXTERNAL}/board/powertime3/uboot/dts/zynq-mars-zx2.dts" 
```
If you want to update the DTS please modify directly zynq-mars-zx2.dts under the DTS.

There is some patch also applied. The most important is the patch for board.c patch, which perform some specific powertime configuration. The current patch does the following:
- update board.c
- add LCD access to initialize the LCD at uboot time
- add marvel driver
### Update-kernel
The commande to update uboot is the same as the package 
```
cd build
make linux-rebuild
make
```
or if there is patch modification or if a new config does not compile correctly 
```
cd build
make linux-dirclean
make linux
make
```
Same as uboot, Builroot is configure to take external DTS ,config  and patches that are found in 
[http://buildroot_swisstiming/board/powertime3/kernel/](http://buildroot_swisstiming/board/powertime3/kernel/) under DTS , config and patches.
Here the most crucial files when adding new interfaces is the kernel DTS: 
[zynq-mars-zx2.dts](https://github.com/mikaeltrigo/buildroot_swisstiming/blob/master/board/powertime3/kernel/dts/zynq-mars-zx2.dts "zynq-mars-zx2.dts") and [zynq-enclustra-zx-common.dtsi](https://github.com/mikaeltrigo/buildroot_swisstiming/blob/master/board/powertime3/kernel/dts/zynq-enclustra-zx-common.dtsi "zynq-enclustra-zx-common.dtsi")

if you want to navigate in to the menuconfig of the kernel, it is not possible to do it directly in build folder . Do the following :

```
cd build/build/linux-custom/
make make menuconfig
```
If you have added a new configuration, you must double check what was added in .config (under linux-custom root) and add to the kernel configuration in[xilinx_zynq_defconfig](https://github.com/mikaeltrigo/buildroot_swisstiming/blob/master/board/powertime3/kernel/config/xilinx_zynq_defconfig "xilinx_zynq_defconfig") 

For example I've added the GMII to RGMII driver with
```
CONFIG_XILINX_GMII2RGMII=y 
```
The overlay (under buildroot_swisstiming/board/powertime3/rootfs_overlay/ )  are files that are automatically added in the file system when pressing make.

We can observe two major files: 
### Update-Overlay 

( add some files in the system, change network)


- Network configuration [interfaces](https://github.com/mikaeltrigo/buildroot_swisstiming/blob/master/board/powertime3/rootfs_overlay/etc/network/interfaces "interfaces")

- Init Script (script that starts after booting the system) : [init.d](https://github.com/mikaeltrigo/buildroot_swisstiming/tree/master/board/powertime3/rootfs_overlay/etc/init.d/)




## Setup Eclipse/Buildroot development environment

please check the [readme-cmake.md](https://github.com/mikaeltrigo/Quantum/blob/master/readme-cmake.md "readme-cmake.md") in the quantum app git Repo
