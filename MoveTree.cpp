// MoveTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
#include "Node.h"
using namespace std;

int main()
{
    Tree* T = new Tree();
    Node* root = new Node(nullptr, WHITE, 1.0, 1.0);
    T->root = root;

    Node* n1 = new Node(T->root, BLACK, 1.0, 1.0);
    Node* n2 = new Node(T->root, BLACK, 1.0, 1.0);

   
    Node* n11 = new Node(n1, WHITE, 0.0, 1.0);
    Node* n12 = new Node(n1, WHITE, 1.0, 1.0);

    Node* n21 = new Node(n2, WHITE, 1.0, 1.0);
    Node* n22 = new Node(n2, WHITE, 1.0, 1.0);

    n1->add_child(n11);
    n1->add_child(n12);

    n2->add_child(n21);
    n2->add_child(n22);

    T->root->add_child(n1);
    T->root->add_child(n2);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
