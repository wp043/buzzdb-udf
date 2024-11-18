#include "sample_udf.h"

extern "C" {

int add_integers(int a, int b) {
    return a + b;
}

double multiply_doubles(double x, double y) {
    return x * y;
}

}
