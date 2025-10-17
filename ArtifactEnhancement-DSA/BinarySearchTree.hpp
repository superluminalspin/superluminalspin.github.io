#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "Bid.hpp"
#include <iostream>

// Internal structure for tree node
struct Node {
	Bid bid;
	Node* left;
	Node* right;
	int height;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
		height = 1;
	}

	// initialize with a bid
	Node(Bid aBid) :
		Node() {
		bid = aBid;
	}
};


//============================================================================
// Binary Search Tree class definition
//============================================================================
/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
private:

	Node* root;
	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	Node* removeNode(Node* node, std::string bidId);
	int treeNodeCounter = 0;

public:

	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void PostOrder();
	void PreOrder();
	void Insert(Bid bid);
	Node* Insert(Node* node, Bid bid, std::string bidId);
	void Remove(std::string bidId);
	Node* Remove(Node* root, std::string bidId);
	Bid Search(std::string bidId);
	int TreeNodeCount();
	int Height(Node* node);
	int BalanceFactor(Node* node);
	Node* MinKeyValue(Node* node);
	Node* RotateRight(Node* nodeY);
	Node* RotateLeft(Node* nodeX);

};

#endif // !BINARYSEARCHTREE_H
