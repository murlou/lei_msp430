NAME = lei-msp
TARGET=$(notdir $(PWD))

#########################################
#				Doxygen 				#
#########################################

# doxygen executable
DOXYGEN = doxygen

# doxygen flags
DOXYGENFLAGS = ./doxygen.conf

#########################################
#				msp430-gcc				#
#		libs in /usr/msp430/lib/		#
#########################################
DEVICE=msp430g2553
COMPILER = msp430
#TARGET = saida
MMCU =-lfp -mmcu=$(DEVICE)
LIB_LOCAL = -L/usr/msp430/lib/

#########################################
#				arm-elf-gcc				#
#	libs in /usr/lib/gcc/arm-elf/4.0.2/	#
#########################################
#DEVICE=LPC2100
#COMPILER = arm-elf
#TARGET = teste
#MMCU =  -mcpu=arm7tdmi
#LIB_LOCAL = -L/usr/lib/gcc/arm-elf/4.0.2/

#########################################
#				avr-gcc					#
#		libs in /usr/lib/avr/lib/		#
#########################################
#DEVICE = avr
#COMPILER = avr
#TARGET = teste
#MMCU =  -mmcu=atmega8
#LIB_LOCAL = -L/usr/lib/avr/lib/

#---------------------------------------

MODULES_DIR = modulos
SRC_DIR = src
LIB_DIR = $(MODULES_DIR)/lib
#ROOT_DIR =.

CC = $(COMPILER)-gcc
AR = $(COMPILER)-ar
LD = $(COMPILER)-ld -v 
AS = $(COMPILER)-as
CP = $(COMPILER)-objcopy
OD = $(COMPILER)-objdump


# Flags de warning
WAR=-pedantic -Wall
OPT = -O3 -Os
DEBUG=

CC_FLAGS = -c -fno-common $(OPT) $(MMCU) $(INCLUDES) $(DEBUG)
AR_FLAGS = rcs
LD_FLAGS = $(LIB_LOCAL) -L$(ROOT_DIR)/$(LIB_DIR)/ -l$(NAME) -lc -lfp -lm $(MMCU) $(INCLUDES)
CP_FLAGS = -O ihex
OD_FLAGS = -x --syms

INCLUDES = -I$(ROOT_DIR)/$(MODULES_DIR)/ -I./

# Objetos
OBJ=$(SRC:.c=.o)

# Se for gerar um arquivo HEX
HEX=_$(TARGET).hex

# Nome do arquivo ELF
ELF=$(TARGET).elf


#.SILENT:
