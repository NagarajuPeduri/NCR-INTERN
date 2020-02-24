//pnr7
// selfAdjustingLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


Node* selfAdjust(Node* head, int key) {
    Node* thead, * temp = head;
    thead = head;

    if (head == NULL)       //base conditions
        return head;

    if ((head->next == NULL && key == head->data) || (key == head->data))
        return head;

    while (head->next != NULL) {        //find the node, store and remove it, then join the linked lists. 
        if (head->next->data == key) {
            temp = head->next;
            head->next = head->next->next;
            break;
        }

        head = head->next;
    }

    if (head->next == NULL && head->data!=key) {        //check if the given key node is not present.
        cout << "\nInvalid value";
        return thead;
    }

    temp->next = thead;         //adjust the key node to the first position. 
    thead = temp;
    return thead;
}


// for reading linked list elements
Node* creatingLinkedList(Node* head, int size) {
    cout << "\nEnter linked list elements :\n";
    int ele;
    Node* thead;
    cin >> ele;

    head = createNode(ele);
    thead = head;

    while (--size) {
        cin >> ele;
        thead->next = createNode(ele);
        thead = thead->next;
    }
    return head;
}


void display(Node* head) {
    cout << "\nAfter merging: \n";
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
}


int main()
{
    int element, llsize, key;
    Node* ll = NULL;

    cout << "----Self-adjusting linked list----\n\n\n";

    cout << "Enter linked list size: ";
    cin >> llsize;
    ll = creatingLinkedList(ll, llsize);

    
    while (true) {
        int flag;
        cout << "\nEnter 1 to adjust any value\nEnter 2 to exit\nEnter: ";
        cin >> flag;

        switch (flag) {
        case 1:
            cout << "\nEnter value: ";
            cin >> key;
            ll = selfAdjust(ll, key);
            break;
            
        case 2:
            return 0;
        }

        display(ll);
    }

    return 0;
}

