CXX = g++
CXXFLAGS = -std=c++17 -fPIC -shared

SRCS = sample_udf.cpp

all: libsample_udf.so

libsample_udf.so: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f libsample_udf.so
