#pragma once

// Red Black Tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#include <iostream>

// Node Colors
enum struct Color : int { BLACK, RED, NO_COLOR };

// TODO: convert all naked pointers to smart pointers
// data structure that represents a node in the tree
struct Node
{	
	int data;		// holds the key
	Node* parent;	// pointer to parent
	Node* left;		// pointer to left child
	Node* right;	// pointer to right child
	Color color;
};

// class RBTree implements the operations in the Red-Black Tree
class RBTree
{
private:
	Node* root;
	Node* TNULL;

	// initializes the nodes with appropraite values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(Node* node, Node* parent)
	{
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = Color::BLACK;
	}

	void preOrderHelper(Node* node)
	{
		if (node != TNULL) {
			std::cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(Node* node)
	{
		if (node != TNULL) {			
			inOrderHelper(node->left);
			std::cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	void postOrderHelper(Node* node)
	{
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			std::cout << node->data << " ";
		}
	}

	Node* searchTreeHelper(Node* node, int key)
	{
		if (node == TNULL || key == node->data)
			return node;

		if (key < node->data)
			return searchTreeHelper(node->left, key);

		return searchTreeHelper(node->right, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(Node* x)
	{
		Node* s;
		while (x != root && x->color == Color::BLACK) {
			if (x = x->parent->left) {
				s = x->parent->right;
				if (s->color == Color::RED) {
					// case 3.1
					s->color == Color::BLACK;
					x->parent->color = Color::RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->color == Color::BLACK && s->right->color == Color::BLACK) {
					// case 3.2
					s->color = Color::RED;
					x = x->parent;
				}
				else {
					if (s->right->color == Color::BLACK) {
						// case 3.3
						s->left->color = Color::BLACK;
						s->color = Color::RED;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = Color::BLACK;
					s->right->color = Color::BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == Color::RED) {
					// case 3.1
					s->color = Color::BLACK;
					x->parent->color = Color::RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
					// case 3.2
					s->color = Color::RED;
					x = x->parent;
				}
				else {
					if (s->left->color == Color::BLACK) {
						// case 3.3
						s->right->color = Color::BLACK;
						s->color = Color::RED;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = Color::BLACK;
					s->left->color = Color::BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = Color::BLACK;
	}

	void rbTransplant(Node* u, Node* v) {}
	void deleteNodeHelper(Node* u, Node* v) {}
	void fixInsert(Node* k) {}
	void printHelper(Node* root, std::string indent, bool last) {}

public:
	// rotate left at node x
	void leftRotate(Node* x) {}

	// rotate right at node x
	void rightRotate(Node* x) {}
};