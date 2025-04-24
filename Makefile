# For Mac OS add
# PREFIX = x86_64-elf-
ifeq ($(shell uname), Linux)
CC=gcc
else
ifeq ($(shell x86_64-elf-gcc --help 2>/dev/null| grep "Options:"),)
$(error x86_64-elf-gcc not installed...)
else
CC=$(PREFIX)gcc
endif
endif
ASMCC=nasm
LD=$(PREFIX)ld
CFLAGS=-m32 -Werror -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wno-implicit-function-declaration
DEBUGFLAGS=-g -DDEBUG_MODE
TESTFLAG=-DTEST_MODE
ASMFLAGS=-f
ASMFORMAT=elf
KERNELSRC=src/kernel/
KERNELOBJ=obj/kernel/
TEMPFUNCTIONSSRC=src/temp_functions/
TEMPFUNCTIONSOBJ=obj/temp_functions/
DEFAULT_COLOR= # Color for text in OS

ifneq ($(DEFAULT_COLOR),)
CFLAGS+= -DDEFAULT_COLOR=$(DEFAULT_COLOR)
endif

build:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(KERNELSRC)kernel_preparation.asm -o $(KERNELOBJ)kasm.o
	$(CC) $(CFLAGS) -c $(KERNELSRC)kernel_handler.c -o $(KERNELOBJ)kc.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(KERNELOBJ)kasm.o $(KERNELOBJ)kc.o

with_temp:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(KERNELSRC)kernel_preparation.asm -o $(KERNELOBJ)kasm.o
	$(CC) $(CFLAGS) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(KERNELOBJ)kasm.o $(KERNELOBJ)kc0-1.o

debug_mode:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(KERNELSRC)kernel_preparation.asm -o $(KERNELOBJ)kasm.o
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(KERNELOBJ)kasm.o $(KERNELOBJ)kc0-1.o

test_mode:
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(TEMPFUNCTIONSSRC)temp.asm -o $(TEMPFUNCTIONSOBJ)temp.o
	$(ASMCC) $(ASMFLAGS) $(ASMFORMAT) $(KERNELSRC)kernel_preparation.asm -o $(KERNELOBJ)kasm.o
	$(CC) $(CFLAGS) $(TESTFLAG) -c $(KERNELSRC)kernel_handler0-1.c -o $(KERNELOBJ)kc0-1.o
	$(LD) -m elf_i386 -T link.ld -o kernel $(TEMPFUNCTIONSOBJ)temp.o $(KERNELOBJ)kasm.o $(KERNELOBJ)kc0-1.o

clean:
	rm -rf $(KERNELOBJ)*
	rm -rf $(TEMPFUNCTIONSOBJ)*
	rm -f obj/*.o
