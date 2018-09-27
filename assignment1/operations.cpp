#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include "operations.h"
#include "utils.h"
#include "typedef.h"
using namespace std;

extern string to_string(Integer a,bool ignore_most_sig_zeros);
extern Integer to_integer(string str,unsigned int base);
extern void pad_back(Integer &in, unsigned int n);

int maxLen(Integer a, Integer b);
int conver2d(Integer a, int lenA, int base);
Integer conver2Other(int a, int base);

Integer add( Integer a, Integer b, unsigned int base){
  Integer X = a;
  Integer Y = b;
  int lenX = X.size();
  int lenY = Y.size();
  int maxD = maxLen(a, b);
  int carr = 0;

  //small one filled up with zero at pad_front
  if(lenX > lenY){
    unsigned int diffD = lenX - lenY;
    pad_front(Y, diffD);
  }
  if(lenX < lenY){
    unsigned int diffD = lenY - lenX;
    pad_front(X, diffD);
  }

  unsigned int tempiSum = 0;
  Integer sum;
  for(int i = maxD-1; i >= 0; i--){
    if(carr == 1){
      tempiSum = X[i] + Y[i] + 1;
      if(tempiSum >= base){
        tempiSum = tempiSum - base;
        carr = 1;
      }
      else{
        carr = 0;
      }
    }
    else{
      tempiSum = X[i] + Y[i];
      if(tempiSum >= base){
        tempiSum = tempiSum - base;
        carr = 1;
      }
      else{
        carr = 0;
      }
    }

    sum.push_back(tempiSum);
    if(carr == 1 && i == 0){
      sum.push_back(1);
    }
  }

  reverse(sum.begin(), sum.end());

  return sum;

}

// Multiply two Integers a and b given in base using the Karatsuba algorithm, and
// returns the output as an Integer.
Integer kmul( Integer a,  Integer b,unsigned int base){
  Integer X = a;
  Integer Y = b;
  int lenX = X.size();
  int lenY = Y.size();
  int tLen = lenX + lenY;
  int maxD = maxLen(a, b);
  int halfD = maxD/2;
  int leftD = halfD;
  int rightD = maxD - halfD;

  //base case, if total length is less than 4, calculate straight away
  if(tLen <= 4){
    int tempA = conver2d(a, lenX, base);
    int tempB = conver2d(b, lenY, base);
    int tempiProd = tempA * tempB;
    return conver2Other(tempiProd, base);
  }
  //small one filled up with zero at pad_front
  if(lenX > lenY){
    unsigned int diffD = lenX - lenY;
    pad_front(Y, diffD);
  }
  if(lenX < lenY){
    unsigned int diffD = lenY - lenX;
    pad_front(X, diffD);
  }

  //calculate x1, x0, y1, y0
  string sx1 = to_string(X).substr(0, halfD);
  string sx0 = to_string(X).substr(halfD, maxD-halfD);
  string sy1 = to_string(Y).substr(0, halfD);
  string sy0 = to_string(Y).substr(halfD, maxD-halfD);

  //calcutate z2, z0 and z1 recursively
  Integer z2 = kmul(to_integer(sx1, base), to_integer(sy1, base), base);
  Integer z0 = kmul(to_integer(sx0, base), to_integer(sy0, base), base);
  Integer z1Left = kmul(to_integer(sx1, base), to_integer(sy0, base), base);
  Integer z1Right = kmul(to_integer(sx0, base), to_integer(sy1, base), base);
  Integer z1 = add(z1Left, z1Right, base);
  Integer Z2 = z2;
  pad_back(Z2, rightD);
  pad_back(Z2, rightD);
  Integer Z1 = z1;
  pad_back(Z1, rightD);
  Integer Z21 = add(Z2, Z1, base);
  Integer Z = add(Z21, z0, base);

  return Z;
}

int conver2d(Integer a, int lenA, int base){
  int result = 0;
  for(int i = 0; i < lenA; i++){
    if(i == lenA-1){
      result += a[i];
    }
    else{
      result += (a[i]*pow(base, lenA-i-1));
    }
  }
  return result;
}

Integer conver2Other(int a, int base){
  Integer result;
  if(a == 0){
    result.push_back(a);
    return result;
  }
  if(a == 1){
    result.push_back(a);
    return result;
  }
  int rem = a;
  while(rem >= 1){
    int temp = rem%base;
    rem = rem / base;
    result.push_back(temp);
  }
  reverse(result.begin(), result.end());
  return result;
}


int maxLen(Integer a, Integer b){
  int lenA = a.size();
  int lenB = b.size();
  if(lenA >= lenB){
    return lenA;
  }
  else{
    return lenB;
  }
}
