// stackUsingLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

Node* createNode(int x) {
    Node* n = new Node;
    n->data = x;
    n->next = NULL;
    return n;
}

Node* insert(Node* head, int ele) {
    Node* newNode = createNode(ele);
    newNode->next = head;
    head = newNode;
    return head;
}

Node* deleteHead(Node* head) {
    cout << "\nPopped element: " << head->data << "\n\n";
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void display(Node* head) {
    cout << "\nStack elements: \n";
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n\n";
}

int main()
{
    int element, length=0;
    Node* head = NULL;

    while (true) {
        cout << "Enter 1 to push\nEnter 2 to pop\nEnter 3 to get size\nEnter 4 to display stack\nEnter 5 to exit\nEnter: ";
        int flag;
        cin >> flag;

        if (flag == 1) {        //insert
            cin >> element;
            cout << "\n";
            length++;
            head = insert(head, element);
        }

        else if (flag == 2) {       //delete

            if (length == 0)
                cout << "\nEmpty\n\n";

            else {
                length--;
                head = deleteHead(head);
            }
        }
        else if (flag == 3)         //size
            cout << "\nStack size is " << length << "\n\n";

        else if (flag == 4) {
            if (length == 0)
                cout << "\nEmpty\n\n";
            else
                display(head);
        }

        else
            break;
    }
}

