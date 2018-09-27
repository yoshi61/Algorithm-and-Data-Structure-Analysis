#include <iostream>
#include <string>
#include "hash_table.h"

using namespace std;

Hash_table::Hash_table(){
  this->table = new string[26];
  for(int i = 0; i<26; i++){
    this->table[i] = "never used";
  }
  cout << "hash table initialised!"<<endl;
}

bool Hash_table::findKey(std::string key){
  return true;
}

void Hash_table::insertKey(std::string key){

}

void Hash_table::removeKey(std::string key){

}

void Hash_table::printTable(){
  for(int i =0; i<26; i++){
    if(this->table[i] != "never used"){
      cout<<this->table[i]<<" ";
    }
  }
  cout<<endl;
}

Hash_table::~Hash_table(){

}
