// red_black_tree_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp

#include <iostream>

#include "rbtree.h"
int main()
{
    std::cout << "Red Black Tree!\n";

    RBTree bst;
    bst.insert(8);
    bst.prettyPrint();
    bst.insert(18);
    bst.prettyPrint();
    bst.insert(5);
    bst.prettyPrint();
    bst.insert(15);
    bst.prettyPrint();
    bst.insert(2); // my test insertion into the left-left
    bst.prettyPrint();
    bst.insert(7); // my test insertion into the left-right
    bst.prettyPrint();

    bst.insert(17); // causes a bug when inserting into an uncle right-left-right
    bst.prettyPrint();

    bst.insert(25); // test insertion into right-right
    bst.prettyPrint();

    bst.insert(40);
    bst.prettyPrint();
    bst.insert(80);
    bst.prettyPrint();
    bst.deleteNode(25);
    bst.prettyPrint();

    std::cin.get();
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
