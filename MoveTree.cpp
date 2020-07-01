// MoveTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
#include "Node.h"
#include "Valindex.h"
#include <vector>
#include <stdio.h>

using namespace std;

int main()
{
  //will have an interface that builds the tree and for each Position
  //it finds all moves for either white or black then creates nodes for each one,
  //each node holding the naive analysis of just that positions value.
  //then starting at the current position, we update the values
  //for each move choice based on recursively going deeper into the tree
  //and finding the best reply for the other player...
    Tree* T = new Tree(NULL);
    Node* root = new Node(NULL, WHITE, 2.0, 1.0);
    T->root = root;
    //root

    //layer n=1 children
    Node* n11 = new Node(root, BLACK, 1.0, 1.0);
    Node* n12 = new Node(root, BLACK, 1.0, 2.0);
    Node* n13 = new Node(root, BLACK, 3.0, 1.0);
    root->add_child(n11);
    root->add_child(n12);
    root->add_child(n13);
    //layer n=2 children
    //n11's chilldren
    Node *n111 = new Node(n11, WHITE, 3.0, 1.0);
    Node *n112 = new Node(n11, WHITE, 1.0, 1.0);
    n11->add_child(n111);
    n11->add_child(n112);
    //n12's children
    Node *n121 = new Node(n12, WHITE, 6.0, 1.0);
    Node *n122 = new Node(n12, WHITE, 2.0, 1.0);
    Node *n123 = new Node(n12, WHITE, 1.0, 1.0);
    n12->add_child(n121);
    n12->add_child(n122);
    n12->add_child(n123);
    //n13's children
    Node *n131 = new Node(n13, WHITE, 3.0, 1.0);
    Node *n132 = new Node(n13, WHITE, 1.0, 10.0);
    n13->add_child(n131);
    n13->add_child(n132);
    //layer n=3
    //n111's children
    Node *n1111 = new Node(n111, BLACK, 4.0, 1.0);
    Node *n1112 = new Node(n111, BLACK, 1.0, 8.0);
    n111->add_child(n1111);
    n111->add_child(n1112);
    //n112's
    Node *n1121 = new Node(n112, BLACK, 1.0, 4.0);
    Node *n1122 = new Node(n112, BLACK, 1.0, 8.0);
    n112->add_child(n1121);
    n112->add_child(n1122);
    ///n121s
    Node *n1211 = new Node(n121, BLACK, 6.0, 1.0);
    Node *n1212 = new Node(n121, BLACK, 5.0, 1.0);
    n121->add_child(n1211);
    n121->add_child(n1212);
    //n122s children
    Node *n1221 = new Node(n122, BLACK, 2.0, 1.0);

    n122->add_child(n1221);
    //n123s children
    //NONE
    //layer n=4
    //n131s children
    Node *n1311 = new Node(n131, BLACK, 3.0, 10.0);
    n131->add_child(n1311);

    //n132s chidlren
    Node *n1321 = new Node(n132, BLACK, 1.0, 10.0);
    n132->add_child(n1321);

    T->eval_tree_white(root, 0, 2, WHITE, true);




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
