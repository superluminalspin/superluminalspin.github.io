#ifndef BID_HPP
#define BID_HPP

#include <iostream>


// Structore to hold bid information
struct Bid {
	std::string bidId;
	std::string title;
	std::string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

#endif
