# For Mac OS add
# PREFIX = x86_64-elf-
CC=$(PREFIX)gcc
ASMCC=nasm
LD=$(PREFIX)ld
CFLAGS=-m32 -Werror -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wno-implicit-function-declaration
DEBUGFLAGS=-g -DDEBUG_MODE
ASMFLAGS=-f
ASMFORMAT=elf
KERNELSRC=src/kernel/
KERNELOBJ=obj/kernel/
TEMPFUNCTIONSSRC=src/temp_functions/
TEMPFUNCTIONSOBJ=obj/temp_functions/

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

clean:
	rm -rf $(KERNELOBJ)*
	rm -rf $(TEMPFUNCTIONSOBJ)*
	rm -f obj/*.o
