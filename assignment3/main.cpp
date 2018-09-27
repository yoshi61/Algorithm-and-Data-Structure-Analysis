#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
//a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z

class Hash_table{

  private:

    const int BASE = 97;

    string nothing = "";

    string *table;

    char hash(string str){
      return str[str.length()-1];
    }

    int char2index(char ch){
      return (int)ch-BASE;
    }

    string& findKey(string key){
      char lastCh = this->hash(key);
      int index = char2index(lastCh);
      if(table[index] == key){
        return table[index];
      }
      else{
        int i = index+1;
        while(i != index){
          if(i == 26){
            i = 0;
          }
          if(table[i] == key){
            return table[i];
          }
          else if(table[i] == "never used"){
            return nothing;
          }
          i++;
        }
        return nothing;
      }
    }

  public:

    Hash_table(){
      this->table = new string[26];
      for(int i = 0; i<26; i++){
        this->table[i] = "never used";
      }
    }

    void insertKey(string key){
      //check if exist
      string &result = this->findKey(key);
      if(result != ""){
        return;
      }

      char lastCh = this->hash(key);
      int index = char2index(lastCh);
      if(table[index] == "never used" || table[index] == "tombstone"){
        table[index] = key;
      }
      else{
        int i = index+1;
        while(i != index){
          if(i == 26){
            i = 0;
          }
          if(table[i] == "never used" || table[i] == "tombstone"){
            table[i] = key;
            break;
          }
          i++;
        }
      }
    }

    void removeKey(string key){
      string &result = this->findKey(key);
      if(result != ""){
        result = "tombstone";
      }
    }

    void printTable(){
      for(int i =0; i<26; i++){
        if(this->table[i] != "never used" && this->table[i] != "tombstone"){
          cout<<this->table[i]<<" ";
        }
      }
      cout<<endl;
    }

    void printAll(){
      for(int i =0; i<26; i++){
        cout<<this->table[i]<<" ";
      }
      cout<<endl;
    }

    ~Hash_table(){}
};

int main(void) {
    //create a hash table
    Hash_table t;
    //collect input in one line and put in vectors
    string input;
    getline( cin, input );
    istringstream is( input );
    vector<string> L( ( istream_iterator<string>( is ) ), istream_iterator<string>() );
    for(unsigned int i = 0; i < L.size(); i++){
      if(L[i][0] == 'A'){
        t.insertKey(L[i].substr(1));
      }
      else if(L[i][0] == 'D'){
        t.removeKey(L[i].substr(1));
      }
    }
    t.printTable();
    return 0;
}
