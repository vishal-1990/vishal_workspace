#Makefile for cpp basic project
#@Author:Vishal Nambiar

#VPATH is env variable in which make searches for user created .c and .h files
VPATH = ./src:./include 
CC11 = g++ -std=c++11
CC = g++

COMPILER_FLAGS = -g3 -I ./include -c 

LINKER_FLAGS = -o  

SRC_PATH = ./src
INCLUDE_PATH = ./include 
BUILD_PATH = ./release
OBJ_PATH = ./objs

TARGETS = $(BUILD_PATH)/cppBasics $(BUILD_PATH)/moveSemantics


.PHONY : all
all : $(TARGETS)

#$@ represents the targets
#$^ represents all the prerequisites

$(BUILD_PATH)/cppBasics : $(OBJ_PATH)/cppBasics.o 
	$(CC11) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/cppBasics.o : cppBasics.cpp 
	$(CC11) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@


$(BUILD_PATH)/moveSemantics : $(OBJ_PATH)/moveSemantics.o 
	$(CC11) $^ $(LINKER_FLAGS) $@ 


$(OBJ_PATH)/moveSemantics.o : moveSemantics.cpp 
	$(CC11) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@


clean :
	find . -name *.o | xargs rm
