include ../Makefile.inc

MMC=./mmc
SPI=./spi

	
ROOT_DIR =..

OBJS = ${SRCS:.c=.o}

#Primeiro alvo
all: lib

#Gerando documentação	
docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
	cd ./doc/gen/latex; $(MAKE) ; rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl

lib:lib/lib$(NAME).a
	
lib/lib$(NAME).a: modules
#	@echo -n "Creating lib ... "
	$(AR) $(AR_FLAGS) ./$(LIB_DIR)/lib$(NAME).a ./obj/*.o
	@echo lib$(NAME).a "Done."

clean:
	rm obj/*.o -v
	echo "Objects deleted"

modules:
	@if find $(SPI) -quit; then \
		make -C spi/; \
		echo "SPI support added" ;\
	else \
		echo "Without SPI support" ;\
	fi
	@if find $(MMC) -quit ; then \
		make -C mmc/; \
		echo "MMC support added" ;\
	else \
		echo "Without MMC support" ;\
	fi
