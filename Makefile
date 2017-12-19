#Makefile for cpp basic project
#@Author:Vishal Nambiar

#VPATH is env variable in which make searches for user created .c and .h files
VPATH = ./src:./include 
CC11 = g++ -std=c++11
CC14 = g++ -std=c++1y
CC = g++

COMPILER_FLAGS = -g3 -I ./include -c 

LINKER_FLAGS = -o  

SRC_PATH = ./src
INCLUDE_PATH = ./include 
BUILD_PATH = ./release
OBJ_PATH = ./objs

TARGETS = $(BUILD_PATH)/cppBasics $(BUILD_PATH)/moveSemantics $(BUILD_PATH)/smartPointer $(BUILD_PATH)/castingexe $(BUILD_PATH)/functors_lambda $(BUILD_PATH)/singleton $(BUILD_PATH)/linkedList $(BUILD_PATH)/bubbleSort $(BUILD_PATH)/insertionSort $(BUILD_PATH)/selectionSort $(BUILD_PATH)/stdarray



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

$(BUILD_PATH)/smartPointer : $(OBJ_PATH)/smartPointer.o 
	$(CC11) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/smartPointer.o : smartPointers.cpp 
	$(CC11) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/castingexe : $(OBJ_PATH)/casting.o 
	$(CC11) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/casting.o : casting.cpp 
	$(CC11) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/functors_lambda : $(OBJ_PATH)/functors_lambda.o 
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/functors_lambda.o : functors_lambda.cpp 
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/singleton : $(OBJ_PATH)/singleton.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/singleton.o : designPatterns/singleton.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/linkedList : $(OBJ_PATH)/linkedList.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/linkedList.o : dataStructures/linkedList.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/bubbleSort : $(OBJ_PATH)/bubbleSort.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/bubbleSort.o : sortalgo/bubbleSort.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/insertionSort : $(OBJ_PATH)/insertionSort.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/insertionSort.o : sortalgo/insertionSort.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/selectionSort : $(OBJ_PATH)/selectionSort.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/selectionSort.o : sortalgo/selectionSort.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@

$(BUILD_PATH)/stdarray : $(OBJ_PATH)/stdarray.o
	$(CC14) $^ $(LINKER_FLAGS) $@ 

$(OBJ_PATH)/stdarray.o : stl/stdarray.cpp
	$(CC14) $(COMPILER_FLAGS) $^ $(LINKER_FLAGS) $@
clean :
	find . -name *.o | xargs rm
