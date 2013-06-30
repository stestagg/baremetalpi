ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -g -nostdlib -nostartfiles -ffreestanding 

kernelout: kernel.img
	cp kernel.img ../out/kernel.img

all : kernelout

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.img
	rm -f ../out/kernel.img


vectors.o : vectors.s
	$(ARMGNU)-gcc -c vectors.S -o vectors.o

bootloader.o : bootloader.c
	$(ARMGNU)-gcc $(COPS) -c bootloader.c -o bootloader.o

periph.o : periph.c
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

bootloader.elf : loader vectors.o periph.o bootloader.o 
	$(ARMGNU)-ld vectors.o periph.o bootloader.o -T loader -o bootloader.elf

kernel.img : bootloader.elf
	$(ARMGNU)-objcopy bootloader.elf -O binary kernel.img

bootloader.hex : bootloader.elf
	$(ARMGNU)-objcopy bootloader.elf -O ihex bootloader.hex

bootloader.list : bootloader.elf
	$(ARMGNU)-objdump -D bootloader.elf > bootloader.list

