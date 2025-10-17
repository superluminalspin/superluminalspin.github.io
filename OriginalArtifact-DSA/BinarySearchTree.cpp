//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Daryn Mann
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>
#include <string.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
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
    Node* removeNode(Node* node, string bidId);
    int treeNodeCounter = 0;
    

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    int TreeNodeCount();
   
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    this->root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe (2)
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (3a): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (4a): Post order root
    // postOrder root
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (5a): Pre order root
    // preOrder root
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (6a) Implement inserting a bid into the tree
    // set newNode as the root
    Node* newNode = root;
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(bid);
    }
    // else
    else {
        // add Node root and bid
        while (newNode != nullptr) {
            // if bid to be inserted is less than the newNode
            if (bid.bidId.compare(newNode->bid.bidId) < 0) {
                // if newNode left node is null
                if (newNode->left == nullptr) {
                    // set newNode left node to the bid
                    newNode->left = new Node(bid);
                    // set newNode node to null
                    newNode = nullptr;
                } else { newNode = newNode->left; } // move to next left node
                // else bid to be inserted is larger than the newNode
            } else {
                // if newNode right is null
                if (newNode->right == nullptr) {
                    // set right node to bid
                    newNode->right = new Node(bid);
                    // set newNode to null
                    newNode = nullptr;
                    // else move to next right node
                } else { newNode = newNode->right; }
            }
        }

        ++treeNodeCounter;
    }
}
int BinarySearchTree::TreeNodeCount() {
    return treeNodeCounter;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (7a) Implement removing a bid from the tree
    // create new parent node initialized to null
    Node* parentNode = nullptr;
    // create current node initalized to the root node
    Node* currNode = root;
    // loop until current node is null
    while (currNode != nullptr) {
        // if current nodes value is equivalent to passed value
        if (currNode->bid.bidId.compare(bidId) == 0) {
            // REMOVE LEAF
            // if the left child node is null and right child node is null
            if (currNode->left == nullptr && currNode->right == nullptr) {
                // if parent is null
                if (parentNode == nullptr) {
                    // set root to null
                    root = nullptr;
                }
                // if the parent nodes left child is equal to the current node
                else if (parentNode->left == currNode) {
                    // set left child to null
                    parentNode->left = nullptr;
                } else { parentNode->right = nullptr; } // otherwise set right child to null
            }
            // REMOVE NODE WITH ONLY LEFT CHILD
            else if (currNode->right == nullptr) {
                if (parentNode == nullptr) {
                    root = currNode->left;
                }
                else if (parentNode->left == currNode) {
                    parentNode->left = currNode->left;
                } else { parentNode->right = currNode->left; }
            }
            // REMOVE NODE WITH ONLY RIGHT CHILD
            // if current nodes left child is null
            else if (currNode->left == nullptr) {
                // if the parent node is null
                if (parentNode == nullptr) {
                    // set root to the current nodes right child
                    root = currNode->right;
                }
                // if parent nodes left child is equal to current node
                else if (parentNode->left == currNode) {
                    // set parent nodes left child to current nodes right child
                    parentNode->left = currNode->right;
                } else { parentNode->right = currNode->right; } // otherwise set parent nodes right child equal to current nodes right child
            }
            // REMOVE NODE WITH TWO CHILDREN
            else {
                // Find successor (leftmost child of right subtree)
                Node* succNode = currNode->right;
                // loop until the leftmost child is found
                while (succNode->left != nullptr) {
                    // move to next left node
                    succNode = succNode->left;
                }
                // create new object node with the leftmosts child's object
                Node succObj = Node(succNode->bid);
                // recursively call remove function using leftmost childs bidId
                Remove(succNode->bid.bidId);
                // assign current nodes object with what is held in successor nodes object
                currNode->bid = succObj.bid;
            }
            treeNodeCounter--;
            cout << "Bid #" << bidId << " removed. " << treeNodeCounter << " bids remain in the tree." << endl;
            return; // Node found and removed
        }
        // search right side
        else if (currNode->bid.bidId.compare(bidId) < 0) {
            parentNode = currNode;
            currNode = currNode->right;
        } else {
            parentNode = currNode;
            currNode = currNode->left;
        }
    }
    return; // Node not found
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (8) Implement searching the tree for a bid
    // set current node equal to root
    Node* currNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (currNode != nullptr) {
        // if match found, return current bid
        if (bidId.compare(currNode->bid.bidId) == 0) {
            // return bid
            return currNode->bid;
        }
        // if bid is smaller than current node then traverse left
        else if (bidId.compare(currNode->bid.bidId) < 0) {
            // set current node to the left child of the current node
            currNode = currNode->left;
        } else { currNode = currNode->right; }// else larger so traverse right
    }
    // return empty bid if nothing found
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (6b) Implement inserting a bid into the tree
    // if node is larger then add to left
        // if no left node
            // this node becomes left
        // else recurse down the left node
    // else
        // if no right node
            // this node becomes right
        //else
            // recurse down the left node
}
void BinarySearchTree::inOrder(Node* node) {
      // FixMe (3b): Pre order root
      //if node is not equal to null ptr
    if (node == nullptr) {
        return;
      }
    // inOrder left
    inOrder(node->left);
    // output bid info
    //displayBid(node->bid);
    cout << "Bid ID# " << node->bid.bidId << " / " << " Title: " << node->bid.title << " / " << " Amount: " << node->bid.amount << endl;
    //InOder right
    inOrder(node->right);
}
void BinarySearchTree::postOrder(Node* node) {
      // FixMe (4b): Pre order root
      //if node is not equal to null ptr
      //postOrder left
      //postOrder right
      //output bidID, title, amount, fund

}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (5b): Pre order root
      //if node is not equal to null ptr
      //output bidID, title, amount, fund
      //postOrder left
      //postOrder right      
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // FIXME (7b) Implement removing a bid from the tree
    // if node = nullptr return node
    // (otherwise recurse down the left subtree)
    // check for match and if so, remove left node using recursive call 
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    // (otherwise no children so node is a leaf node)
    // if left node = nullptr && right node = nullptr delete node 
    // (otherwise check one child to the left)
    // if left node != nullptr && right node = nullptr delete node 
    // (otherwise check one child to the right)
    // if left node = nullptr && right node != nullptr delete node
    // (otherwise more than one child so find the minimum)
    // create temp node to right
    // while left node is not nullptr keep moving temp left
    // make node bid (right) equal to temp bid (left)
    // remove right node using recursive call
    // return node
    return node;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;
            cout << bst->TreeNodeCount() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            ticks = clock();
            bst->InOrder();
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            ticks = clock();
            bst->Remove(bidKey);
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
