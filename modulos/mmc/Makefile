include ../../Makefile.inc

SRC=./mmc.c  \
	./pff.c  \
	
ROOT_DIR =../..

OBJ = ${SRC:.c=.o}

#Primeiro alvo
all: $(OBJ)
	mv *.o ../obj
	
#Gerando objetos
.c.o:
	$(CC) -Wall -c $(SRC) $(CC_FLAGS)
	
#Limpando os objetos
clean:
	clear
	rm -rf *.o *.elf *.hex *.map *.s *.list

