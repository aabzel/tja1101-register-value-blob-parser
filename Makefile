#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

PATH_PROJECT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
#@echo $(error PATH_PROJECT= $(PATH_PROJECT))
SRC_PATH :=  $(dir $(abspath $(dir $$PWD) ))
#@echo $(error SRC_PATH=$(SRC_PATH))

OBJDIR := $(SRC_PATH)/obj
# the compiler to use
#CC = clang
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
CFLAGS  += -DHAS_PARSE_REG
CFLAGS  += -DHAS_UTESTS
CFLAGS  += -DHAS_TJA1101

#files to link:
LFLAGS =
  
EXECUTABLE=reg_parser
# the name to use for both the target source file, and the output file:
#TARGET = main


SOURCES = $(SRC_PATH)/main.c 
SOURCES += $(SRC_PATH)/utils.c 
SOURCES += $(SRC_PATH)/arrays.c  
SOURCES += $(SRC_PATH)/test_arrays.c  
SOURCES += $(SRC_PATH)/convert.c  
SOURCES += $(SRC_PATH)/test_convert.c  
SOURCES += $(SRC_PATH)/float_utils.c  
SOURCES += $(SRC_PATH)/parse_regs.c

SOURCES += $(SRC_PATH)/parse_tja1101_regs.c

SOURCES += $(SRC_PATH)/uTests.c   
SOURCES += $(SRC_PATH)/str_ops.c
SOURCES += $(SRC_PATH)/test_str_ops.c    
SOURCES += $(SRC_PATH)/algorithms.c 


OBJECTS =$(SOURCES:.c=.o)

#@echo $(error OBJECTS= $(OBJECTS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE).exe

%.o: %.c
	$(CC) $(CFLAGS) -c $^  
	mv *.o $(SRC_PATH)
