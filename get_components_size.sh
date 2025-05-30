#!/bin/bash

target=disk.img

if ls | grep $target
then
disk_size_in_sectors=$((($(ls -l disk.img | tr -s ' ' | cut -d ' ' -f 5)+511) / 512))
second_bootloader_size=$(($(ls -l boot2part.bin | tr -s ' ' | cut -d ' ' -f 5) / 512))
kernel_size=$((disk_size_in_sectors - second_bootloader_size - 1))
echo "Size of disk getted: $disk_size_in_sectors"
echo "First bootloader: 1"
echo "Second bootloader: $second_bootloader_size"
echo "Kernel: $kernel_size"
else
echo "$target not found"
fi