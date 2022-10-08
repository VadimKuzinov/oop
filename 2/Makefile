CC=g++
STD=-std=c++2a
LIB_PATH=$(shell pwd)/build/
LIB_FLAGS=-L$(LIB_PATH) -lCurve -Wl,-rpath,$(LIB_PATH)
LIB_FLAGS_GTEST=-lgtest -lgtest_main

test: $(LIB_PATH)libCurve.so
	$(CC) -o build/$@ CurveTest/$@.cpp $(LIB_FLAGS) $(LIB_FLAGS_GTEST) $(STD)

menu:
	$(CC) -o build/$@ CurveMenu/$@.cpp $(LIB_FLAGS) $(STD)

$(LIB_PATH)libCurve.so:
	$(CC) -c -fPIC Curve/Curve.cpp $(STD)
	$(CC) -shared -o $(@) *.o

