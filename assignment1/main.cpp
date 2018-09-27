#include <iostream>
#include <string>
#include "typedef.h" //Type definitions
#include "operations.h" 
#include "utils.h"
using namespace std;

// The main method parses the arguments and check for correctness. Then calls sum and kmul method with the input values.
// Finally, the return values are displayed on the command-line.
int main(int nargs, char *argv[]){

    //Note that in c/c++, the first argument is always the command name.
    if (nargs <4){
        cerr << "Need three arguments.\n1) I1: First integer\n2) I2: Second integer\n3) B: Base of I1 and I2.\n"<<endl;
        return 1;
    }
    
    //Parsing the base, which is the third input.
    unsigned int base = stoul(string(argv[3]));
    if (base<2 || base >10){
        cerr << "Base should be an integer in [2,10]"<<endl;
        return 1;
    }
    
    //Parsing input Integers. In parsed (integer_1 and integer_2) values the zeroth index represent the most significant digit and
    //the least significant digit is at the integer.size()-1 location.
    Integer integer_1 = to_integer(argv[1],base);
    Integer integer_2 = to_integer(argv[2],base);
  
    //Calling school method of summation.
    Integer sum = add(integer_1,integer_2,base);

    //Calling Karatsuba multiplication
    Integer kmultiplication = kmul(integer_1,integer_2,base);

    //Displaying the output; first sum then multiplication.
    cout << to_string(sum)<<" "<<to_string(kmultiplication) << endl;
   return 0;
}
