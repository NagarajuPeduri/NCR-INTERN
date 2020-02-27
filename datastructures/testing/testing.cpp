// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<set>
#include <vector>
#include<string>
using namespace std;


vector<string> splitStringsBySlash(char str[])
{
	char* token = strtok(str, "\\");
	vector<string> vec;

	while (token != NULL)
	{
		vec.push_back(token);
		token = strtok(NULL, "\\");
	}
	return vec;
}



int main() {
	char ch[100];
	cin.getline(ch, 100);
	vector<string> vec;
	vec = splitStringsBySlash(ch);
	
}

