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
    cout << "\nQueue elements: \n";
    if (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

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

        switch (flag) {
        case 1:         //Enqueuing into the queue
            cout << "Enter: ";
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
            break;

        case 2:     //Dequeuing from the queue
            if (length == 0)
                cout << "\nEmpty\n\n";

            else {
                length--;
                front = deleteHead(front, rear);
            }
            break;

        case 3:     //size
            cout << "\Queue size is " << length << "\n\n";
            break;

        case 4:     //display
            if (length == 0)
                cout << "\nEmpty\n\n";
            else
                display(front);
            break;

        case 5:     //exit
            return 0;
        }
    }
}

