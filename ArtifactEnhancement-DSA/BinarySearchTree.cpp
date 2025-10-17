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
#include "BinarySearchTree.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
//double strToDouble(string str, char ch);

// define a structure to hold bid information
//struct Bid {
//    string bidId; // unique identifier
//    string title;
//    string fund;
//    double amount;
//    Bid() {
//        amount = 0.0;
//    }
//};
//
//// Internal structure for tree node
//struct Node {
//    Bid bid;
//    Node *left;
//    Node *right;
//    int height;
//
//    // default constructor
//    Node() {
//        left = nullptr;
//        right = nullptr;
//        height = 1;
//    }
//
//    // initialize with a bid
//    Node(Bid aBid) :
//            Node() {
//        bid = aBid;
//    }
//};




//class BinarySearchTree {
//
//private:
//    Node* root;
//
//    void addNode(Node* node, Bid bid);
//    void inOrder(Node* node);
//    void postOrder(Node* node);
//    void preOrder(Node* node);
//    Node* removeNode(Node* node, string bidId);
//    int treeNodeCounter = 0;
//    
//
//public:
//    BinarySearchTree();
//    virtual ~BinarySearchTree();
//    void InOrder();
//    void PostOrder();
//    void PreOrder();
//    void Insert(Bid bid);
//    Node* Insert(Node* node, Bid bid, string bidId);
//    void Remove(string bidId);
//    Node* Remove(Node* root, string bidId);
//    Bid Search(string bidId);
//    int TreeNodeCount();
//    int Height(Node* node);
//    int BalanceFactor(Node* node);
//    Node* MinKeyValue(Node* node);
//    Node* RotateRight(Node* nodeY);
//    Node* RotateLeft(Node* nodeX);
//   
//};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
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
/*
*  Insert function workaround for loadBids logic, allows inserting a Bid object
*  without including pointers to the root as well as the bid id.
*/
void BinarySearchTree::Insert(Bid bid) {
    root = Insert(root, bid, bid.bidId);
}

/**
 *         INSERT a bid recursively
 */
Node* BinarySearchTree::Insert(Node* node, Bid bid, string bidId) {

    // Base case, creates node object to be inserted, and increments tree counter
    if (node == nullptr) {
        ++treeNodeCounter;
        return new Node(bid);
    }

    // Walk through the existing nodes to find where to insert the new node
    if (bid.bidId < node->bid.bidId) {
        node->left = Insert(node->left, bid, bidId);
    } else if (bid.bidId > node->bid.bidId) {
        node->right = Insert(node->right, bid, bidId);
    } else {
        return node;
    }

    // Increment the height of current node before performing rotations
    node->height = 1 + max(Height(node->left), Height(node->right));

    // Calculate balance factor for the current node
    int balance = BalanceFactor(node);

    // Left Left Case
    if (balance > 1 && bid.bidId < node->left->bid.bidId) {
        // rotate current right
        return RotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && bid.bidId > node->right->bid.bidId) {
        // rotate current left
        return RotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && bid.bidId > node->left->bid.bidId) {
        // rotate left node left
        node->left = RotateLeft(node->left);
        // rotate current right
        return RotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && bid.bidId < node->right->bid.bidId) {
        // rotate right node right
        node->right = RotateRight(node->right);
        // rotate current left
        return RotateLeft(node);
    }

    // return new root node
    return node;
}

/**
 *         REMOVE a bid
 */
void BinarySearchTree::Remove(string bidId) {
    root = Remove(root, bidId);
}

/*
*          REMOVE a bid recursively
*/
Node* BinarySearchTree::Remove(Node* root, string bidId) {
    // Base case
    if (root == nullptr) {
        return root;
    }

    // Move down left side if bidID is less than current node's value
    if (bidId < root->bid.bidId) {
        root->left = Remove(root->left, bidId);
    }
    // Move down right side if bidId is more than current node's value
    else if (bidId > root->bid.bidId) {
        root->right = Remove(root->right, bidId);
    }
    // Otherwise key is identical and remove node
    else {
        // Case for node with 0 or 1 child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        // Case for node with 2 children
        else {
            // Find next highest value node following the root node
            Node* temp = MinKeyValue(root->right);
            // Copy that found object to root
            root->bid = temp->bid;
            // Remove 
            root->right = Remove(root->right, temp->bid.bidId);
        }
    }

    // If tree only had one node then return
    if (root == nullptr) {
        return root;
    }

    // Update height of root node
    root->height = 1 + max(Height(root->left), Height(root->right));

    // Get balance factor of root node
    int balance = BalanceFactor(root);

    /*
    *   Perform rotations if BST is unbalanced
    */
    // Left Left Case
    if (balance > 1 && BalanceFactor(root->left) >= 0) {
        // rotate root right
        return RotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && BalanceFactor(root->right) <= 0) {
        // rotate root left
        return RotateLeft(root);
    }

    // Left Right Case
    if (balance > 1 && BalanceFactor(root->left) < 0) {
        // rotate left node left
        root->left = RotateLeft(root->left);
        // rotate root right
        return RotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && BalanceFactor(root->right) > 0) {
        // rotate right node right
        root->right = RotateRight(root->right);
        // rotate root left
        return RotateLeft(root);
    }

    // return root node
    return root;
}

/*
*  Helper function to get the number of nodes in the BST
*/
int BinarySearchTree::TreeNodeCount() {
    return treeNodeCounter;
}

/*
* Helper function to get the height of a specific node
*/
int BinarySearchTree::Height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

/*
* Function to calculate balance factor of a specific node using
* the difference of the height of the node's children.
*/
int BinarySearchTree::BalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}

/*
* Function to return minimum key value in BST
*/
Node* BinarySearchTree::MinKeyValue(Node* node) {
    Node* current = node;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}
/*
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Node* current = root;
    // Find bid by traversing left or right depending on comparison of passed value
    // and current nodes value
    while (current != nullptr) {
        if (bidId == current->bid.bidId) {
            return current->bid;
        }
        else if (bidId < current->bid.bidId) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // Return empty bid object
    return Bid();
}

/*
*  Rotate node right for AVL tree logic via recursion
*/
Node* BinarySearchTree::RotateRight(Node* nodeY) {
    // left child of node Y (rotation point)
    Node* nodeX = nodeY->left;
    // right child of node X (subtree to be moved)
    Node* T2 = nodeX->right;

    // Rotate nodes
    nodeX->right = nodeY;
    nodeY->left = T2;

    // Update heights
    nodeY->height = 1 + max(Height(nodeY->left), Height(nodeY->right));
    nodeX->height = 1 + max(Height(nodeX->left), Height(nodeX->right));

    // return new root node
    return nodeX;
}

/*
*  Rotate node left for AVL tree logic
*/
Node* BinarySearchTree::RotateLeft(Node* nodeX) {
    // right child of node X (rotation point)
    Node* nodeY = nodeX->right;
    // left child of node X (subtree to be moved)
    Node* T2 = nodeY->left;

    // Rotate nodes
    nodeY->left = nodeX;
    nodeX->right = T2;

    // Update Heights
    nodeX->height = 1 + max(Height(nodeX->left), Height(nodeX->right));
    nodeY->height = 1 + max(Height(nodeY->left), Height(nodeY->right));

    // return new root node
    return nodeY;
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

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}
/*
*  Recursive InOrder Traversal
*/
void BinarySearchTree::inOrder(Node* node) {
    // base case
    if (node == nullptr) {
        return;
    }
    inOrder(node->left);
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
    inOrder(node->right);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (4a): Post order root
    // postOrder root
}

void BinarySearchTree::postOrder(Node* node) {
      // FixMe (4b): Pre order root
      //if node is not equal to null ptr
      //postOrder left
      //postOrder right
      //output bidID, title, amount, fund

}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (5a): Pre order root
    // preOrder root
}

void BinarySearchTree::preOrder(Node* node) {
      // FixMe (5b): Pre order root
      //if node is not equal to null ptr
      //output bidID, title, amount, fund
      //postOrder left
      //postOrder right      
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

/*
*  Simple function to output how long an operation takes
*/
void Time(clock_t ticks) {
    cout << "time: " << ticks << " clock ticks" << endl;
    cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
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

    string searchBidId;
    string removeBidId;

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

        // Load Data
        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            cout << bst->TreeNodeCount() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            
            Time(ticks);

            break;

        // In Order Traversal
        case 2:
            ticks = clock();
            bst->InOrder();
            ticks = clock() - ticks;
            
            Time(ticks);

            break;

        // Search for specific value
        case 3:
            cout << "Enter Bid ID to search for: ";
            cin >> searchBidId;

            ticks = clock();

            bid = bst->Search(searchBidId);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            Time(ticks);

            break;

        // Remove specific value
        case 4:
            cout << "Enter Bid ID to remove: ";
            cin >> removeBidId;

            ticks = clock();

            bst->Remove(removeBidId);

            ticks = clock() - ticks;

            Time(ticks);

            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
