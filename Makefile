# For Mac OS with arm arch compiler x86_64-elf-gcc
ifeq ($(shell uname), Linux)
CC=gcc
LD=ld
else
ifeq ($(shell x86_64-elf-gcc --help 2>/dev/null| grep "Options:"),)
$(error x86_64-elf-gcc not installed...)
else
CC=x86_64-elf-gcc
LD=x86_64-elf-ld
endif
endif
ASMCC=nasm
CFLAGS=-m32 -Werror -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wno-implicit-function-declaration
DEBUGFLAGS=-g -DDEBUG_MODE
TESTFLAG=-DTEST_MODE
ASMFLAGS=
ASMFORMAT=-f elf
BOOTSRC=src/boot/
BOOTOBJ=obj/boot/
KERNELSRC=src/kernel/
KERNELOBJ=obj/kernel/
TEMPFUNCTIONSSRC=src/temp_functions/
TEMPFUNCTIONSOBJ=obj/temp_functions/
DEFAULT_COLOR= # Color for text in OS
DEFAULT_TAB_SIZE=

ifneq ($(DEFAULT_COLOR),)
ifeq ($(shell if [ $(DEFAULT_COLOR) -ge 0 ] && [ $(DEFAULT_COLOR) -le 15 ]; then echo true; fi), true)
CFLAGS+= -DDEFAULT_COLOR=$(DEFAULT_COLOR)
ASMFLAGS+= -DDEFAULT_COLOR=$(DEFAULT_COLOR)
else
$(error Bad color, value between 0 and 15.)
endif
endif

ifneq ($(DEFAULT_TAB_SIZE),)
ifeq ($(shell if [ $(DEFAULT_TAB_SIZE) -eq 2 ] || [ $(DEFAULT_TAB_SIZE) -eq 4 ]; then echo true; fi), true)
CFLAGS+= -DDEFAULT_TAB_SIZE=$(DEFAULT_TAB_SIZE)
else
$(error Bad tab size, only 2 or 4.)
endif
endif

build:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(BOOTSRC)kernel_preparation.asm -o $(BOOTOBJ)kasm.o
	$(CC) $(CFLAGS) -c $(KERNELSRC)kernel_handler.c -o $(KERNELOBJ)kc.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(BOOTOBJ)kasm.o $(KERNELOBJ)kc.o

with_temp:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(BOOTSRC)kernel_preparation.asm -o $(BOOTOBJ)kasm.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) src/cpu/interrupts.asm -o $(KERNELOBJ)interrupts.o
	$(CC) $(CFLAGS) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(CC) $(CFLAGS) -c src/cpu/isr.c -o $(KERNELOBJ)isr.o
	$(CC) $(CFLAGS) -c src/cpu/irq.c -o $(KERNELOBJ)irq.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(BOOTOBJ)kasm.o $(KERNELOBJ)kc0-1.o $(KERNELOBJ)interrupts.o $(KERNELOBJ)isr.o $(KERNELOBJ)irq.o

debug_mode:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(BOOTSRC)kernel_preparation.asm -o $(BOOTOBJ)kasm.o
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(BOOTOBJ)kasm.o $(KERNELOBJ)kc0-1.o

test_mode:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(BOOTSRC)kernel_preparation.asm -o $(BOOTOBJ)kasm.o
	$(CC) $(CFLAGS) $(TESTFLAG) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(BOOTOBJ)kasm.o $(KERNELOBJ)kc0-1.o

disk_format:
	$(ASMCC) $(ASMFLAGS) -f bin src/boot/bootloader.asm -o bootpart.bin
	$(ASMCC) -g -F dwarf $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) -g -F dwarf $(ASMFLAGS) $(ASMFORMAT) $(BOOTSRC)kernel_preparation.asm -o $(BOOTOBJ)kasm.o
	$(ASMCC) -g -F dwarf $(ASMFLAGS) $(ASMFORMAT) src/cpu/interrupts.asm -o $(KERNELOBJ)interrupts.o
	$(CC) -g $(CFLAGS) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(CC) -g $(CFLAGS) -c src/cpu/isr.c -o $(KERNELOBJ)isr.o
	$(CC) -g $(CFLAGS) -c src/cpu/irq.c -o $(KERNELOBJ)irq.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(BOOTOBJ)kasm.o $(TEMPFUNCTIONSOBJ)temp.o $(KERNELOBJ)kc0-1.o $(KERNELOBJ)interrupts.o $(KERNELOBJ)isr.o $(KERNELOBJ)irq.o --oformat binary
	cat bootpart.bin kernel > disk.img
# dd if=/dev/zero of=disk.img bs=1M count=10 2>/dev/null
# dd if=bootpart.bin of=disk.img conv=notrunc 2>/dev/null
# dd if=kernel of=disk.img bs=512 conv=notrunc seek=1 2>/dev/null
	qemu-system-i386 -drive file=disk.img,format=raw


clean:
	rm -rf $(KERNELOBJ)*
	rm -rf $(TEMPFUNCTIONSOBJ)*
	rm -f obj/*.o