//pnr7
// SortingNonHomogeneousArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono;


bool comparator(string a, string b) {
    if (isalpha(a[0]) && isalpha(b[0])) {       // if a and b are characters. 
        return a < b;
    }
    else if (isdigit(a[0]) && isdigit(b[0])) {      // if a and b are number
        int x, y;
        x = stoi(a);
        y = stoi(b);
        //cout << x << " " << y << endl;
        return x < y;
    }
    else {                                      // if a and b are of different types.
        if (isdigit(a[0]))
            return false;
        else
            return true;
    }
}

int main()
{
    int size;
    vector<string> vec;
    cout << "\nEnter array size: ";
    cin >> size;

    if (size <= 0) {
        cout << "Not a valid size ";
        return 0;
    }

    cout << "Enter " << size << " elements: \n";
    for (int i = 0; i < size; i++) {
        string s;
        cin >> s;
        vec.push_back(s);
    }

    auto start = high_resolution_clock::now();

    sort(vec.begin(), vec.end(), comparator);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nAfter sorting: \n";
    for (string v : vec) {
        cout << v << " ";
    }

    cout << "\n\nTime taken by function: "
        << duration.count() << " microseconds" << endl;

}

