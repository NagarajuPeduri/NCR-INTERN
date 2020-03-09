// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<set>
#include <vector>
#include<string>
using namespace std;

//signature function_name and number arguments. 

class testing {
private:
	int a, b;

public:
	void setter(int x) {
		a = x;
	}

	int getter() {
		return a;
	}
};

int main() {
	
	testing obj;
	obj.setter(10);
	cout << obj.getter();
}

