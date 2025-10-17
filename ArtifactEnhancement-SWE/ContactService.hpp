#ifndef CONTACTSERVICE_H
#define CONTACTSERVICE_H

#include <iostream>
#include <unordered_map>
#include "Contact.hpp"


/*
		Service class to provide functionality for Contact objects
*/

class ContactService {
private:
	// Hide default constructor and destructor
	ContactService();
	~ContactService();

public:
	// Hashmap to store contacts, key = id, value = contact object
	std::unordered_map<std::string, Contact> contacts;

	// Delete copy constructor and assignment operator to prevent copying
	ContactService(const ContactService&) = delete;
	ContactService& operator=(const ContactService&) = delete;

	// Static function to access singleton instance
	static ContactService& getInstance();

	// Class function to add contact to map
	void addContact(const Contact& contact);
	// Class function to update contact in map
	void updateContact(const std::string& contactId, const Contact& contact);
	// Class function to delete contact in map
	void deleteContact(const std::string& contactId);

	// Class function to find number of contact objects in map
	int numberOfContacts() const;
};
#endif