#pragma once
#include "typedef.h"
#include <string>

// Return an Integer with length dim all filled with zero digits
Integer zeros_with_digits(unsigned int dim);


// Pad specified number (n) of zeros to the least significant end.
void pad_back(Integer &in, unsigned int n);

//  Pad specified number (n) of zeros to the most significant end.
void pad_front( Integer &in, unsigned int n);

// Return the string representation of the Integer. If ignore_most_sig_zeros == true, 
// then any leading zeros will not be in the string.
std::string to_string(Integer a,bool ignore_most_sig_zeros = false);

// Convert a sequence of digit string to an Integer with the specified base.
Integer to_integer(std::string str,unsigned int base);
