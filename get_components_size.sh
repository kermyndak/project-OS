#!/bin/bash

target_boot2part=boot2part.bin
target_disk=disk.img

if [ -f $target_disk ] && [ -f $target_boot2part ]
then
disk_size_in_sectors=$((($(ls -l $target_disk | tr -s ' ' | cut -d ' ' -f 5)+511) / 512))
second_bootloader_size=$(($(ls -l $target_boot2part | tr -s ' ' | cut -d ' ' -f 5) / 512))
kernel_size=$((disk_size_in_sectors - second_bootloader_size - 1))
echo "Size of disk getted: $disk_size_in_sectors"
echo "First bootloader: 1"
echo "Second bootloader: $second_bootloader_size"
echo "Kernel: $kernel_size"
else
echo "$target_disk or $target_boot2part not found"
fi