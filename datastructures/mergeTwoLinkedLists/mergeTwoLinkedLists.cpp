// mergingTwoLinkedLists.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


Node* creatingLinkedList(Node* head, int num, int size) {
    cout << "\nEnter linked list " << num << " elements :\n";
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


Node* merge(Node* ll1, Node* ll2, int pos) {
    Node* afterPos, * thead;

    if (pos == 0) {            //if pos is 0, then ll2 should be first followed by ll1.
        thead = ll2;
        while (ll2->next != NULL)
            ll2 = ll2->next;

        ll2->next = ll1;
    }
    else {     
        thead = ll1;        // in all other cases. 
        while (--pos) {
            ll1 = ll1->next;
        }

        afterPos = ll1->next;
        ll1->next = ll2;

        while (ll2->next != NULL) {
            ll2 = ll2->next;
        }

        ll2->next = afterPos;
    }
    return thead;
}


void display(Node* head) {
    cout << "After merging: \n";
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
}


int main()
{
    int element, ll1size, ll2size, pos;
    Node* ll1 = NULL, * ll2 = NULL;

    cout << "----Merging two linked lists----\n\n\n";

    cout << "Enter 1st linked list size: ";
    cin >> ll1size;
    ll1 = creatingLinkedList(ll1, 1, ll1size);

    cout << "\nEnter 2nd linked list size: ";
    cin >> ll2size;
    ll2 = creatingLinkedList(ll2, 2, ll2size);

    cout << "\nEnter position: ";
    cin >> pos;         //checking if position is valid.
    if (pos > ll1size) {
        cout << "\nInvalid position!";
        return 0;
    }

    cout << "\n\n";

    ll1 = merge(ll1, ll2, pos);

    display(ll1);
    return 0;
}

