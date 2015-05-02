##==========================================================================
##                   LPC-bootloader
##
##              Copyright(c) 2015-2016 Yoc Ltd. All rights reserved.
##
##--------------------------------------------------------------------------
## File Description
## ----------------
##      lpc1768 makefile definition.
##
##--------------------------------------------------------------------------
##
##  Created by   :     yoc
##        Date   :     2015.04.29
##==========================================================================


#-------------------------------------------------------------------------------
# Configure version and out target
#-------------------------------------------------------------------------------
PLATFORM = NXP
CPU		 = lpc1768
APP		 = bootloader
VERSION  = V1.1.1

TARGET   = $(strip $(PLATFORM))_$(strip $(CPU))_$(strip $(APP))_$(strip $(VERSION))




#-------------------------------------------------------------------------------
# Configure environment path
#-------------------------------------------------------------------------------

TOPDIR:= .
BUIL_DDIR:= $(TOPDIR)/build
BIN_DIR:=$(BUIL_DDIR)/bin
OBJ_DIR:=$(BUIL_DDIR)/obj
BUILDLOG:=$(BIN_DIR)/build.log


# load other configuration
include $(TOPDIR)/config.mk



#-------------------------------------------------------------------------------
# Configure the include directories
#-------------------------------------------------------------------------------
INCS  = -I$(TOPDIR) 				\
		-I$(GNU_DIR)/include 		\
		-I$(TOPDIR)/src/startup		\
		-I$(TOPDIR)/src/common		\
		-I$(TOPDIR)/src/drivers		\
		-I$(TOPDIR)/src/api			\
		-I$(TOPDIR)/src/app			\


SRC_DIRS=$(TOPDIR)/src/startup		\
		$(TOPDIR)/src/common		\
		$(TOPDIR)/src/drivers		\
		$(TOPDIR)/src/api			\
		$(TOPDIR)/src/app			\
		
     	 


#-------------------------------------------------------------------------------
# Configure source code files to compile in the source code directories
#-------------------------------------------------------------------------------
SRC_APP=$(wildcard $(TOPDIR)/src/startup/*.s)	\
	$(wildcard $(TOPDIR)/src/startup/*.c)	\
	$(wildcard $(TOPDIR)/src/drivers/*.c)	\
	$(wildcard $(TOPDIR)/src/api/*.c)	\
	$(wildcard $(TOPDIR)/src/app/*.c)	\


OBJS  = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_APP)) 
	


#-------------------------------------------------------------------------------
# Configure the newlib Embedded C runtime
#-------------------------------------------------------------------------------
STDLIB = $(GNU_DIR)/lib/thumb2/libc.a
  

#-fno-common 表示不将未初始化的全局变量 仍然放入BSS段 -O -fsigned-char -fno-common
CFLAGS :=  -Wall -c -g2 -mcpu=cortex-m3 -mthumb -fno-common
SFLAGS:= -mcpu=cortex-m3 -mthumb
LDFLAGS:= -T $(TOPDIR)/lds/lpc1768_boot.lds




		



	
	

#-------------------------------------------------------------------------------
# Definition for compiling procedure
#-------------------------------------------------------------------------------

ALL += MAKE_DIR \
	 $(BIN_DIR)/$(TARGET).srec	\
	 $(BIN_DIR)/$(TARGET).dis	\
	 $(BIN_DIR)/$(TARGET).list	\
	 $(BIN_DIR)/$(TARGET).hex 	\
	 $(BIN_DIR)/$(TARGET).bin 	\
	 
all:	$(ALL)

$(BIN_DIR)/$(TARGET).hex: $(BIN_DIR)/$(TARGET).elf
	$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@

$(BIN_DIR)/$(TARGET).srec: $(BIN_DIR)/$(TARGET).elf
	$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@

$(BIN_DIR)/$(TARGET).dis: $(BIN_DIR)/$(TARGET).elf
	$(OBJDUMP) -d $< > $@
$(BIN_DIR)/$(TARGET).list: $(BIN_DIR)/$(TARGET).elf
	$(OBJDUMP) -S $< > $@

$(BIN_DIR)/$(TARGET).bin: $(BIN_DIR)/$(TARGET).elf
	@$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@
	@echo ----------------------------------------------------
	@echo - GCC Compiling Finished Sucessfully.
	@echo - The target image is in the '$(BIN_DIR)' directory.
	@echo ----------------------------------------------------




$(BIN_DIR)/$(TARGET).elf: $(OBJS)
	@echo - Linking  $@
	@$(LD) $(LDFLAGS) -Map $(BIN_DIR)/$(TARGET).map -o $@ $(OBJS) $(USERLIB) $(STDLIB) 
	


$(OBJ_DIR)/%.o: %.S
	
	@echo - Building  $@ 
	@$(AS) $(C_DEF) $(SFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: %.c
	@echo - Building  $@
	@$(CC) $(C_DEF) $(C_PREDEF) $(CFLAGS) $(INCS) -o $@ $<






MAKE_DIR:
    ifeq ($(BIN_DIR), $(wildcard $(BIN_DIR)))
    else
	mkdir -p $(BIN_DIR)
    endif
    ifeq ($(OBJ_DIR), $(wildcard $(OBJ_DIR)))
    else
	mkdir -p $(OBJ_DIR)
    endif
	@for val in $(SRC_DIRS); do \
	mkdir -p $(OBJ_DIR)/$${val};\
	done;

clean:
	@rm -rfv $(OBJ_DIR)
	@rm -rfv $(BIN_DIR)
	@echo -------------------------
	@echo clean finished.
	@echo -------------------------


	
.PHONY: all clean CreateDir




