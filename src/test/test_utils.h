#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include "cstdlib"
#include "cstdio"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>

#define TEST printf("%s... ", __func__); 
#define END_TEST printf("PASSED\n");
#define IGNORE if(0) 
#define SUPRESS_STDOUT std::cout.setstate(std::ios_base::failbit);
#define ENABLE_STDOUT std::cout.clear(); 
#define given(x)
#define when(x)
#define then(x)
#define And(x)
#define Case(x)
#define cleanup

#endif
