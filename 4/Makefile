CC=g++
STD=-std=c++20
SRC=BasicSquad.cpp GeneralSquad.cpp ImmoralSquad.cpp GeneralHealingSquad.cpp ImmoralHealingSquad.cpp Summoner.cpp
SRC_FULL=$(addprefix src/, $(SRC))
FLAGS= -g
CUR_DIR=$(shell pwd)
LIB_NAME=game
LIB_PATH=$(CUR_DIR)/build
LIB=-L$(LIB_PATH)/ -l$(LIB_NAME) -Wl,-rpath,$(LIB_PATH)/
LIB_FLAGS_GTEST=-lgtest -lgtest_main

test: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(LIB_PATH)/lib$(LIB_NAME).a $(STD)

testTerrain: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -o $(LIB_PATH)/$@ src/Terrain.cpp src/Point.cpp $(CUR_DIR)/$@.cpp $(LIB_PATH)/lib$(LIB_NAME).a $(STD)

$(LIB_NAME):
	$(CC) -fPIC -c $(SRC_FULL) $(STD)
	ar rc $(LIB_PATH)/lib$@.a *.o
	rm *.o

