#ifndef FREEFUNCTIONS_H
#define FREEFUNCTIONS_H

#include "Bid.hpp"
#include "BinarySearchTree.hpp"
#include <iostream>

void displayBid(Bid bid);
void loadBids(std::string csvPath, BinarySearchTree* bst);
void Time(clock_t ticks);
double strToDouble(std::string str, char ch);

#endif // !FREEFUNCTIONS_H
