CC=g++
STD=-std=c++20
CUR_DIR=$(shell pwd)
LIB_PATH=$(CUR_DIR)/build
LIB_FLAGS=-L$(LIB_PATH)/ -lstack -Wl,-rpath,$(LIB_PATH)/
LIB_FLAGS_GTEST=-lgtest -lgtest_main
LIB_NAME=stack

test: $(LIB_PATH)/lib$(LIB_NAME).so
	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/tests/$@.cpp $(LIB_FLAGS) $(LIB_FLAGS_GTEST) $(STD)

menu: $(LIB_PATH)/lib$(LIB_NAME).so
	$(CC) -o $(LIB_PATH)/$@ $(CUR_DIR)/menu/$@.cpp $(LIB_FLAGS) $(STD)

$(LIB_NAME):
	$(CC) -c -fPIC $(CUR_DIR)/src/$@.cpp $(STD)
	$(CC) -shared -o $(LIB_PATH)/lib$@.so *.o
	rm *.o

