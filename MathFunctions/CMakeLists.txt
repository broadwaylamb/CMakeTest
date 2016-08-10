add_library(MathFunctions MathFunctions.h mysqrt.cpp)

install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
