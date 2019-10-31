#!/bin/sh

BOARD_DIR="$(dirname $0)"

MKIMAGE=${HOST_DIR}/bin/mkimage
DTC=${HOST_DIR}/bin/dtc
MKBOOTIMAGE=${BUILD_DIR}/../../utils/mkbootimage

cp ${BOARD_DIR}/pre-built/fpga.bit ${BINARIES_DIR}/fpga.bit
cp ${BOARD_DIR}/pre-built/fsbl.elf ${BINARIES_DIR}/fsbl.elf
cp ${BINARIES_DIR}/u-boot ${BINARIES_DIR}/u-boot.elf

echo "Creating boot.bin..."
cp ${BOARD_DIR}/boot.bif ${BINARIES_DIR}
(cd ${BINARIES_DIR}; ${MKBOOTIMAGE} boot.bif boot.bin)

echo "Compiling the boot-script for mmcboot-rootfs ..."
${MKIMAGE} -A arm -O linux -T script -C none -a 0 -e 0 -n "Uboot mmc start script" \
	 -d ${BOARD_DIR}/uboot/mmcboot-rootfs \
	 ${BINARIES_DIR}/uboot.scr

echo "Compiling the boot-script for ramdisk..."
${MKIMAGE} -A arm -O linux -T script -C none \
	 -d ${BOARD_DIR}/uboot/mmcboot-ramdisk \
	 ${BINARIES_DIR}/uboot-ramdisk.scr


echo "copying device-tree..."
${DTC} -I dts -O dtb -o ${BINARIES_DIR}/devicetree.dtb ${BOARD_DIR}/kernel/dts/zynq-mars-zx2.dts
#cp ${BOARD_DIR}/kernel/dts/dts/zynq-mars-zx2.dts ${BINARIES_DIR}/devicetree.dtb

#FIRST_DT=$(sed -n \
#           's/^BR2_LINUX_KERNEL_INTREE_DTS_NAME="\([a-z0-9\-]*\).*"$/\1/p' \
#           ${BR2_CONFIG})

#[ -z "${FIRST_DT}" ] || ln -fs ${FIRST_DT}.dtb ${BINARIES_DIR}/devicetree.dtb

echo "Creating the sd-card image..."
support/scripts/genimage.sh -c ${BOARD_DIR}/genimage.cfg

