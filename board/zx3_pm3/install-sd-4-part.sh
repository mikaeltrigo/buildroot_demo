#!/bin/bash

ROOTFS_MNT="/mnt/root"
BOOT_MNT="/mnt/boot"
#Change to script directory
execDir=$(pwd)

usage()
{
    programName=$(basename $0)
    echo "usage:  $programName <dev> <boot.bin> <image.tar> --format"
    echo "  dev:             SD device"
    echo "  boot.bin:         boot bin"
    echo "  attention dtb,uimage an uboot.src must be in the exec directory"
    echo "  image.tar:   Rootfs"
    echo "  --format : optional, add it to prior format the sd card "
    echo "  --norootfs : optional, add it to burn only bootbin "
}

exitScript()
{
    cd $execDir
    exit $1
}

# For more information about this formatting procedure visit
# http://www.wiki.xilinx.com/Prepare+Boot+Medium
formatSD()
{
    dd if=/dev/zero of=$1 bs=1024 count=1
    sleep 1
    size=$(fdisk -l |grep "Disk $1:")
    size=${size#*, }
    size=${size%% bytes*}
    let newCylinders=size/8225280
    
    echo "New Cylinders: $newCylinders"
    
    fdisk $1 <<CYLINDERS_END
x
h
255
s
63
c
$newCylinders
r
w
CYLINDERS_END

    fdisk $1 <<"FDISK_END"
n
p
1

+200M
n
p
2

+512M
n
p
3

+512M
n
p


a
1
t
1
c
t
2
83
t
3
83
t
4
83
w
FDISK_END
}

# Format the partition to appropriate file system
formatPartitions()
{
    mkfs.vfat -s 4 -S 512 -F 32 -n boot "$1"1
    mkfs.ext4 -F -L root1 "$1"2
    mkfs.ext4 -F -L root2 "$1"3
    mkfs.ext4 -F -L config "$1"4
}

mountSD()
{
    mkdir -p $BOOT_MNT
    mkdir -p "$ROOTFS_MNT"1
    mkdir -p "$ROOTFS_MNT"2
    mount "$1"1 $BOOT_MNT
    mount "$1"2 "$ROOTFS_MNT"1
    mount "$1"3 "$ROOTFS_MNT"2
}

umountSD()
{
    umount $BOOT_MNT
    umount "$ROOTFS_MNT"1
    umount "$ROOTFS_MNT"2
    rm -r $BOOT_MNT
    rm -r "$ROOTFS_MNT"1
    rm -r "$ROOTFS_MNT"2
}

copyBootBin()
{
    cp $1 $BOOT_MNT/boot.bin
}
copyDTB()
{
    cp $1 $BOOT_MNT/devicetree.dtb
}
copyUbootSrc()
{
    cp $1 $BOOT_MNT/uboot.scr
}
copyuImage()
{
    cp $1 $BOOT_MNT/uImage
}

untarRoot()
{
    tar -xf $1 -C "$ROOTFS_MNT"1
    tar -xf $1 -C "$ROOTFS_MNT"2
}

unmountSDDevice()
{
    for device in $1*; do
        umount -l $device &>/dev/null
    done
}

if [ "$1" == "--help" -o "$1" == "-h" ]; then
    usage
    exitScript 0
fi

if [ "$1" == "" ]; then
    echo "Please specify a SD device"
    exitScript -1
fi

if [ ! -e $1 ]; then
    echo "Please specify a valid SD device"
    exitScript -1
fi

sdDevice="$1"

bootBin="$execDir/boot.bin"
if [ "$2" != "" ]; then
    bootBin="$2"
fi

if [ ! -e $bootBin ]; then
    echo "Bootbin $bootBin does not exist!"
    exitScript -1
fi
if [ ! -e $bootBin ]; then
    echo "Bootbin $bootBin does not exist!"
    exitScript -1
fi

dtb="$execDir/devicetree.dtb"
if [ ! -e $dtb ]; then
    echo "devicetree $dtb does not exist!"
    exitScript -1
fi
uImage="$execDir/uImage"
if [ ! -e $uImage ]; then
    echo "uImage $uImage does not exist!"
    exitScript -1
fi
ubootscr="$execDir/uboot.scr"
if [ ! -e $ubootscr ]; then
    echo "uboot.scr $ubootscr does not exist!"
    exitScript -1
fi
# Third argument must be the image name. Error exit when argument not given.
rootfsImage="${3?Specify Image Name}"

if [ ! -e $rootfsImage ]; then
    echo "Rootfs $rootfsImage does not exist!"
    exitScript -1
fi

echo "Unmount SD Card"
unmountSDDevice $sdDevice
if [ "$4" == "format" ]; then
echo "Format SD Card"
formatSD $sdDevice
echo "Format Partition"
formatPartitions $sdDevice
fi
echo "Mount SD Card"
mountSD $sdDevice

if [ "$4" == "dtbonly" ]; then
echo "Copy dtb"
copyDTB $dtb
elif [ "$4" == "norootfs" ]; then
echo "Copy Boot Bin"
copyBootBin $bootBin
echo "Copy uImage"
copyuImage $uImage
echo "Copy dtb"
copyDTB $dtb
echo "Copy ubootscr"
copyUbootSrc $ubootscr
else
echo "Copy Boot Bin"
copyBootBin $bootBin
echo "Copy uImage"
copyuImage $uImage
echo "Copy dtb"
copyDTB $dtb
echo "Copy ubootscr"
copyUbootSrc $ubootscr
echo "Untar rootfs"
untarRoot $rootfsImage

fi



echo "Unmount SD Card"
umountSD
echo "Congrats you SD card is ready to go"

exitScript 0
