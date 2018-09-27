#pragma once
#include "typedef.h"


// Add two Integers a and b given in base, and returns the output as an Integer.
Integer add( Integer a, Integer b,unsigned int base);

// Multiply two Integers a and b given in base using the Karatsuba algorithm, and
// returns the output as an Integer.
Integer kmul( Integer a,  Integer b,unsigned int base);
