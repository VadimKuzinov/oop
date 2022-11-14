CC=g++
STD=-std=c++20
SRC=$(shell ls src/ | grep \.cpp | tr '\n' ' ')
SRC_PATH=src
OBJ=$(SRC:.cpp=.o)
#$(info $$OBJ is [${OBJ}])
FLAGS=-g -Wall
CUR_DIR=$(shell pwd)
LIB_NAME=game
LIB_PATH=build
LIB=-L$(LIB_PATH)/ -l$(LIB_NAME) -Wl,-rpath,$(LIB_PATH)/

all: $(LIB_PATH)/lib$(LIB_NAME).a

main: $(LIB_PATH)/lib$(LIB_NAME).a
	$(CC) -O3 -o $(LIB_PATH)/$@ $(CUR_DIR)/$@.cpp $(wildcard game/*.cpp) $(LIB) -lSDL2main -lSDL2_ttf -lSDL2 $(STD) $(FLAGS)

$(LIB_PATH)/lib$(LIB_NAME).a: $(addprefix $(LIB_PATH)/, $(OBJ))
	ar rc $@ $^

$(LIB_PATH)/%.o: $(SRC_PATH)/%.cpp $(SRC_PATH)/%.h
	$(CC) -O3 -c $< -o $@ $(STD) $(FLAGS)

run: lib$(LIB_NAME).a

clean:
	rm $(LIB_PATH)/*.o
