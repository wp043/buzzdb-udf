CXX = g++
CXXFLAGS = -std=c++11

all: udf_test

udf_test: udf_test.cpp
    $(CXX) $(CXXFLAGS) -o udf_test udf_test.cpp -lbuzzdb

clean:
    rm -f udf_test
