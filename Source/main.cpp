// A simple program that computes the square root of a number

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CMakeTestConfig.h"
#include "sodium.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char *argv[]) {

    int inputValue = 2;
    
#ifdef USE_MYMATH
    int outputValue = mysqrt(inputValue);
#else
    int outputValue = sqrt(inputValue);
#endif
    
    fprintf(stdout, "The square root of %d is %d\n", inputValue, outputValue);
    fprintf(stdout, "Sodium init: %d\n", sodium_init());
    return 0;
}
