#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <iomanip>
#include <sstream>

/*
		Model class for Contact objects to be handled by ContactService.cpp
*/

class Contact {
private:
	// Class member variables
	std::string id;
	std::string firstName;
	std::string lastName;
	std::string address;
	std::string phoneNumber;
	
public:
	Contact() {}
	// Constructor does not take an ID number and instead generates a unique one when called.
	Contact(
		const std::string& firstName, 
		const std::string& lastName, 
		const std::string& phoneNumber, 
		const std::string& address) 
		: id(generateIdNumber()), // Generate unique ID on object creation
		  firstName(firstName), 
		  lastName(lastName), 
		  phoneNumber(phoneNumber), 
		  address(address) {}
	// Constructor that takes an ID number for update function
	Contact(
		const std::string& id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& phoneNumber,
		const std::string& address) 
		: id(id),
		  firstName(firstName),
		  lastName(lastName),
		  phoneNumber(phoneNumber),
		  address(address) {}

	// Getter functions
	const std::string& getId() const { return id; }
	const std::string& getFirstName() const { return firstName; }
	const std::string& getLastName() const { return lastName; }
	const std::string& getPhoneNumber() const { return phoneNumber; }
	const std::string& getAddress() const { return address; }

	// Generate sequential 4 digit ID number starting with 0001
	static std::string generateIdNumber(int width = 4)
	{
		static int counter = 1;
		std::ostringstream oss;
		oss << std::setw(width) << std::setfill('0') << counter++;
		return oss.str();
	}

	// Object to string method for output
	std::string toString() const
	{
		return "ID: " 
			+ id + " -- " 
			+ lastName 
			+ ", " 
			+ firstName + " Phone: " 
			+ phoneNumber + " Address: " 
			+ address 
			+ "\n";
	}
};

#endif