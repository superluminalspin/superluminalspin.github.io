#include "gtest/gtest.h"
#include "BinarySearchTree.hpp"
#include <time.h>
#include <string.h>
#include <iostream>


//============================================================================
// Static methods used for testing
//============================================================================


// Test clock time for 100 consecutive searches
TEST(BinarySearchTree, ClockTimeForAHundredSearches) {
	BinarySearchTree* bst = new BinarySearchTree();


	for (int i = 0; i < 100; i++) {
		Bid bid;
		bid.bidId = i;
		bst->Insert(bid);
	}

	EXPECT_EQ(bst->TreeNodeCount(), 100);
}