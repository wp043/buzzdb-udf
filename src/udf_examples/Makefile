CXX = g++
CXXFLAGS = -std=c++11 -shared -fPIC -I../include

UDFS = my_sum_udf.so

all: $(UDFS)

%.so: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(UDFS)
