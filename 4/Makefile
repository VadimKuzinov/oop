CC=g++
STD=-std=c++20
SRC=$(wildcard src/*.cpp)
FLAGS= -g
CUR_DIR=$(shell pwd)
LIB_NAME=game
LIB_PATH=build
LIB=-L$(LIB_PATH)/ -l$(LIB_NAME) -Wl,-rpath,$(LIB_PATH)/

#test: $(LIB_PATH)/lib$(LIB_NAME).a
#	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(LIB_PATH)/lib$(LIB_NAME).a $(STD)
all: testTerrain

testTerrain: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -o $(LIB_PATH)/$@ src/Terrain.cpp src/Point.cpp $(CUR_DIR)/$@.cpp $(LIB_PATH)/lib$(LIB_NAME).a $(STD)

$(LIB_NAME):
	$(CC) -fPIC -c $(SRC) $(STD)
	ar rc $(LIB_PATH)/lib$@.a *.o
	rm *.o

