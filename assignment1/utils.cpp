#include "utils.h"
#include "typedef.h"
#include <sstream>
#include <stdexcept> 

Integer zeros_with_digits(unsigned int dim)
{
    Integer out(dim,0);
    return out;
}

void pad_back(Integer &in, unsigned int n)
{
    for (unsigned int i = 0;i<n;i++){
        in.push_back(0);
    }
}
void pad_front( Integer &in, unsigned int n)
{
    
    for (unsigned int i = 0;i<n;i++){
        in.insert(in.begin(),0);
    }
}

std::string to_string(Integer a,bool ignore_most_sig_zeros)
{
    std::stringstream ss;
    bool ignore=ignore_most_sig_zeros;
    for (auto it = a.begin();it!=a.end();it++){
        if (ignore && *it==0)
        {
            continue;
        }else{
            ignore=false;
        }
        ss << *it;
    }

    return ss.str();
}

Integer to_integer(std::string str,unsigned int base)
{
   Integer out;
    for (unsigned int i = 0;i<str.size();i++){
        auto digit = (unsigned int)str[i]-48;
        if (digit >=base){
            throw std::invalid_argument("Input contains invalid characters");
        }
        out.push_back(digit);
    } 

    return out;
}
