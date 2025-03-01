# For Mac OS add
# PREFIX = x86_64-elf-
CC=$(PREFIX)gcc
ASMCC=nasm
LD=$(PREFIX)ld
CFLAGS=-m32 -Werror -nostdlib -nostdinc -fno-builtin -fno-stack-protector
ASMFLAGS=-f
ASMFORMAT=elf
KERNELSRC=src/kernel/
KERNELOBJ=obj/kernel

build:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(KERNELSRC)kernel_preparation.asm -o $(KERNELOBJ)kasm.o
	$(CC) $(CFLAGS) -c $(KERNELSRC)kernel_handler.c -o $(KERNELOBJ)kc.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(KERNELOBJ)kasm.o $(KERNELOBJ)kc.o

with_temp:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) src/temp_functions/temp.asm -o obj/temp_functions/temp.o
	$(LD) 