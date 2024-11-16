CXX = g++
CXXFLAGS = -std=c++11 -I../src -L../bin -lbuzzdb

all: udf_test

udf_test: udf_test.cpp
	$(CXX) $(CXXFLAGS) -o udf_test udf_test.cpp

clean:
	rm -f udf_test
