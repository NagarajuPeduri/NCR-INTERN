//pnr7
// rotateMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program to rotate outer region anticlockwise and inner region clockwise by one step at every entry of 1.

#include <iostream>
using namespace std;

void rotateMatrix(int arr[][4]) {
    int a, b, c, d;
    a = arr[0][0]; b = arr[3][0]; c = arr[3][3]; d = arr[0][3];

    // We'll be moving k and l to rotate outer region. 
    for (int k = 2, l = 1; l < 4 && k >= 0; l++, k--) {
        arr[0][l - 1] = (l < 3) ? arr[0][l] : d;
        arr[k + 1][0] = (k > 0) ? arr[k][0] : a;
        arr[3][k + 1] = (k > 0) ? arr[3][k] : b;
        arr[l - 1][3] = (l < 3) ? arr[l][3] : c;
    }

    //rotating inner region.
    int e = arr[1][1];
    arr[1][1] = arr[2][1];
    arr[2][1] = arr[2][2];
    arr[2][2] = arr[1][2];
    arr[1][2] = e;
}

int main()
{
    int arr[4][4], rotateNumber = 0;

    cout << "Enter matrix(4x4) elements: ";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> arr[i][j];
        }
    }

    cout << "\nEntered matrix: \n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }

    while (true) {
        cout << "\n\Enter 1 to rotate\nEnter 2 to exit\nPlease enter a key: ";
        int flag;
        cin >> flag;

        if (flag == 2)
            break;

        rotateNumber++;

        rotateMatrix(arr);

        cout << "\nAfter " << rotateNumber << " rotations: \n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << arr[i][j] << "  ";
            }
            cout << endl;
        }
    }
}


