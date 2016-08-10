// A simple program that computes the square root of a number

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CMakeTestConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        
        fprintf(stdout,"%s Version %d.%d.%d\n", argv[0],
                CMakeTest_VERSION_MAJOR,
                CMakeTest_VERSION_MINOR,
                CMakeTest_VERSION_PATCH);
        
        fprintf(stdout,"Usage: %s number\n", argv[0]);
        
        return 1;
    }

    const auto inputValue = atof(argv[1]);
    
#ifdef USE_MYMATH
    const auto outputValue = mysqrt(inputValue);
#else
    const auto outputValue = sqrt(inputValue);
#endif
    
    fprintf(stdout,"The square root of %g is %g\n", inputValue, outputValue);
    return 0;
}
