CXX = g++
CXXFLAGS = -std=c++11 -shared -fPIC

all: my_sum_udf.so

my_sum_udf.so: my_sum_udf.cpp
    $(CXX) $(CXXFLAGS) -o my_sum_udf.so my_sum_udf.cpp

clean:
    rm -f my_sum_udf.so
