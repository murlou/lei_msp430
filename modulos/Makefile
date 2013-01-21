include ../Makefile.inc

MMC=./mmc
SPI=./spi
GPS=./gps
ADC=./adc
CAN=./can
I2C=./i2c
UART=./uart
WIFI=./wi-fi
	
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
	$(AR) $(AR_FLAGS) ./lib/lib$(NAME).a ./obj/*.o
	@echo lib$(NAME).a "Done."
	@size ./lib/lib$(NAME).a -Adt

clean:
	rm obj/*.o -v
	echo "Objects deleted"

modules:
	@if test -f $(GPS)/gps.c ; then \
		make -C gps/; \
		echo "GPS support added" ;\
	else \
		echo "Without GPS support" ;\
	fi
	@if test -f $(SPI)/spi.c ; then \
		make -C spi/; \
		echo "SPI support added" ;\
	else \
		echo "Without SPI support" ;\
	fi
	@if test -f $(MMC)/mmc.c  ; then \
		make -C mmc/ ; \
		echo "MMC support added" ;\
	else \
		echo "Without MMC support" ;\
	fi
	
	@if test -f $(ADC)/adc.c  ; then \
		make -C adc/; \
		echo "ADC support added" ;\
	else \
		echo "Without ADC support" ;\
	fi
	@if test -f $(CAN)/can.c  ; then \
		make -C can/; \
		echo "CAN support added" ;\
	else \
		echo "Without CAN support" ;\
	fi
	@if test -f $(I2C)/can.c  ; then \
		make -C can/; \
		echo "I2C support added" ;\
	else \
		echo "Without I2C support" ;\
	fi
	@if test -f $(UART)/can.c  ; then \
		make -C can/; \
		echo "UART support added" ;\
	else \
		echo "Without UART support" ;\
	fi
	@if test -f $(WIFI)/can.c  ; then \
		make -C can/; \
		echo "Wi-fi support added" ;\
	else \
		echo "Without Wi-fi support" ;\
	fi
