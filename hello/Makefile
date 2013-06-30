
COMPILER_BASE ?= arm-none-eabi

NAME = hello

CC = $(COMPILER_BASE)-gcc -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding
AS = $(COMPILER_BASE)-as -Wall 
LD = $(COMPILER_BASE)-ld 
OBJCOPY = $(COMPILER_BASE)-objcopy

out : $(NAME).bin
	cp $(NAME).bin ../out/

all : $(NAME).bin $(NAME).hex

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf

bootstrap.o : bootstrap.S
	$(CC) -c bootstrap.S -o bootstrap.o

platform.o : platform.c
	$(CC) -c platform.c -o platform.o

$(NAME).o : $(NAME).c
	$(CC) -c $(NAME).c -o $(NAME).o

$(NAME).elf : layout bootstrap.o $(NAME).o  platform.o
	$(LD) bootstrap.o platform.o $(NAME).o -T layout -o $(NAME).elf

$(NAME).bin : $(NAME).elf
	$(OBJCOPY) $(NAME).elf -O binary $(NAME).bin

$(NAME).hex : $(NAME).elf
	$(OBJCOPY) $(NAME).elf -O ihex $(NAME).hex
