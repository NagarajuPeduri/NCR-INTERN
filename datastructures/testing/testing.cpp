// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<set>
using namespace std;


int main() {
	set<string> s;
	s.insert("hello");
	s.insert("hi");
	s.insert("wow");

	auto pos = s.find("hello");
	s.erase(pos);

	set<string>::iterator it;

	for (it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
}

