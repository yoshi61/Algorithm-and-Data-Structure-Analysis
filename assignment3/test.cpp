#include <iostream>
#include <string>

using namespace std;

int main(){
	string s = "Random string";
	cout << s.substr(1) << '\n';
	cout << s.replace(0,1,"") << '\n';
}
