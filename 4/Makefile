CC=g++
STD=-std=c++20
SRC=$(wildcard src/*.cpp)
FLAGS= -g -Wall
CUR_DIR=$(shell pwd)
LIB_NAME=game
LIB_PATH=build
LIB=-L$(LIB_PATH)/ -l$(LIB_NAME) -Wl,-rpath,$(LIB_PATH)/


#test: $(LIB_PATH)/lib$(LIB_NAME).a
#	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(LIB_PATH)/lib$(LIB_NAME).a $(STD)
all: run

testTerrain: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(LIB) $(STD) $(FLAGS)

main: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(CUR_DIR)/game/Application.cpp $(CUR_DIR)/game/MenuWindow.cpp $(LIB) -lSDL2main -lSDL2_ttf -lSDL2 $(STD) $(FLAGS)

lib$(LIB_NAME).a: $(SRC)
	$(CC) -fPIC -c $(SRC) $(STD) $(FLAGS)
	ar rc $(LIB_PATH)/$@ *.o
	rm *.o

run: lib$(LIB_NAME).a

