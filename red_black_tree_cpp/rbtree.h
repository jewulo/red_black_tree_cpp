#pragma once


// FIXED ALL THE BUGS. :-)

// Red Black Tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#include <iostream>

// Node Colors
enum struct Color : int { NO_COLOR = -1, BLACK, RED };

// TODO: convert all naked pointers to smart pointers
// data structure that represents a node in the tree
struct Node
{	
	int data;		// holds the key
	Node* parent;	// pointer to parent
	Node* left;		// pointer to left child
	Node* right;	// pointer to right child
	Color color;	// 0 -> Black, 1 -> Red, NO_COLOR = -1
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

				if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
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

	void rbTransplant(Node* u, Node* v)
	{
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(Node* node, int key)
	{
		// find the node containing key
		Node* z = TNULL;
		Node* x;
		Node* y;
		while (node != TNULL) {
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			std::cout << "Couldn't find key in the tree" << std::endl;
			return;
		}

		y = z;
		Color y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == Color::BLACK) {
			fixDelete(x);
		}
	}
	// fix the red-black tree
	void fixInsert(Node* k)
	{
		Node* u;
		while (k->parent->color == Color::RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // Uncle
				if (u != NULL && u->color == Color::RED) {
					// case 3.1
					u->color = Color::BLACK;
					k->parent->color = Color::BLACK;
					k->parent->parent->color = Color::RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = Color::BLACK;
					k->parent->parent->color = Color::RED;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u != NULL && u->color == Color::RED) {
					// mirror case 3.1
					u->color = Color::BLACK;
					k->parent->color = Color::BLACK;
					k->parent->parent->color = Color::RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = Color::BLACK;
					k->parent->parent->color = Color::RED;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = Color::BLACK;
	}

	// fix the red-black tree from Node root
	void printHelper(Node* root, std::string indent, bool last)
	{
		// print the tree structure on the screen
		if (root != TNULL) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "     ";
			}
			else {
				std::cout << "L----";
				indent += "|    ";
			}
			std::string sColor;
			if (root->color == Color::BLACK) {
				sColor = "BLACK";
			}
			else if (root->color == Color::RED) {
				sColor = "RED";
			}
			std::cout << root->data << "(" << sColor << ")" << std::endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

public:
	RBTree() {}

	// Pre-Order traversal
	// Node -> Left Subtree -> Right Suntree
	void preorder()
	{
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Suntree
	void inorder()
	{
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Suntree -> Node
	void postorder()
	{
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	Node* searchTree(int k)
	{
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimmum key
	Node* minimum(Node* node)
	{
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	Node* maximum(Node* node)
	{
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	Node* successor(Node* x)
	{
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x
		Node* y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// find the predecessor of a given node
	Node* predecessor(Node* x)
	{
		// if the left subtree is not null,
		// the successor is the rightmost node in the
		// left subtree
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x
		Node* y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(Node* x)
	{
		Node* y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropraite position
	// and fix the tree
	void insert(int key)
	{
		// Ordinary Binary Search Insertion
		Node* node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = Color::RED;

		Node* y = nullptr;
		Node* x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		// if new node is a root node, simply return 
		if (node->parent == nullptr) {
			node->color = Color::BLACK;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// fix the tree
		fixInsert(node);
	}

	Node* getRoot()
	{
		return this->root;
	}

	// delete the data node from the tree
	void deleteNode(int data)
	{
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void prettyPrint()
	{
		if (root) {
			printHelper(this->root, "", true);
		}
		std::cout << std::endl;
	}
};
