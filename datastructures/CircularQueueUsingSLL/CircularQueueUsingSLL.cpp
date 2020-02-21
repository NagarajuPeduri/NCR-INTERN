// CircularQueueUsingSLL.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

Node* insert(Node* front, Node* rear, int ele) {
    Node* newNode = createNode(ele);
    if (rear == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    rear->next = newNode;
    newNode->next = front;
    rear = rear->next;

    return rear;
}

Node* deleteHead(Node* front, Node* rear) {
    cout << "\deQueued element: " << front->data << "\n\n";
    Node* temp = front;
    front = front->next;
    rear->next = front;
    free(temp);
    return front;
}

void display(Node* front) {
    Node* temp = front;
    cout << "\nStack elements: \n";
    while (temp!=front) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n\n";
}

int main()
{
    int element, length = 0;
    Node *front = NULL, *rear = NULL;

    while (true) {
        cout << "Enter 1 to enQueue\nEnter 2 to deQueue\nEnter 3 to get size\nEnter 4 to display Circular queue\nEnter 5 to exit\nEnter: ";
        int flag;
        cin >> flag;

        if (flag == 1) {        //insert
            cin >> element;
            cout << "\n";
            length++;
            if (length == 1) {
                front = insert(front, rear, element);
                rear = front;
            }
            else {
                rear = insert(front, rear, element);
            }
        }

        else if (flag == 2) {       //delete

            if (length == 0)
                cout << "\nEmpty\n\n";

            else {
                length--;
                front = deleteHead(front, rear);
            }
        }

        else if (flag == 3)         //size
            cout << "\Queue size is " << length << "\n\n";

        else if (flag == 4) {
            if (length == 0)
                cout << "\nEmpty\n\n";
            else
                display(front);
        }

        else
            break;
    }
}

