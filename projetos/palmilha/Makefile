include ../../Makefile.inc

ROOT_DIR = ../..

SRCS = 				\
	main.c

OBJS = ${SRCS:.c=.o}

.SUFFIXES:.c.o

.c.o:
	@echo "Compiling ..."
	$(CC) $(CC_FLAGS) $<
	$(CC) -S $(INCLUDES) $< 

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	@echo "Converting to hex:" $(OBJS)
	$(CP) $(CP_FLAGS) $(OBJS) $(ROOT_DIR)/$@
	$(OD) $(OD_FLAGS) $(OBJS) > _$(TARGET).dmp
	$(CC) -fno-common -Os -g $(LD_FLAGS) $(INCLUDES) $(SRCS) -o $(TARGET).elf -l$(NAME) -Wl,-Map=_$(TARGET).map
	$(OD) -S -g $(ELF) > _$(TARGET).list
	rm $(TARGET).out *.o
	@echo "Done."

$(TARGET).out: $(OBJS)
	@echo "Linking..."
#	$(LD) $(LD_FLAGS) -o $@ $(OBJS) -l$(NAME)-$(DEVICE) $(INCLUDES) -Os -O3
	$(CC) $(LD_FLAGS) -o $@ $(OBJS) -l$(NAME) $(INCLUDES) -Os -O3
	@echo "Done."

upload: $(TARGET).hex
	@echo "burning µC with" $(TARGET).elf
	mspdebug rf2500	$(TARGET).elf

clean:
	rm -rf *.o *~ *.s *.hex *.map *.dmp *.list
	
clean-all: clean
	rm *.elf *.out
