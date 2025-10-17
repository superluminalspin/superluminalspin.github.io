#include "pch.h"
//#include "gtest/gtest.h"
#include "ContactService.hpp"
#include "Contact.hpp"
#include "InputValidator.hpp"
#include <vector>

/*
		Test package for ContactService.cpp
*/



/*
	Test that Contacts are correctly inserted into hashmap
*/
TEST(ContactServiceTest, AddContactInsertsIntoMap) 
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// Create contact object and get its id
	Contact contact("John", "Doe", "12345678901", "123 Main St");
	std::string generateId = contact.getId();

	// Add contact to map
	service.addContact(contact);

	EXPECT_EQ(service.contacts.size(), 1);

	// Search contact's map for object with id
	auto it = service.contacts.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.contacts.end());

	EXPECT_EQ(it->second.getFirstName(), "John");
	EXPECT_EQ(it->second.getLastName(), "Doe");
	EXPECT_EQ(it->second.getPhoneNumber(), "12345678901");
	EXPECT_EQ(it->second.getAddress(), "123 Main St");
}

/*
	Test that duplicate inserts into hashmap fails, will apply a new ID to update contact
*/
TEST(ContactServiceTest, DuplicateInsertionOfContactsIntoMapFails) 
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// Create contact object and get its id
	Contact contact("John", "Doe", "12345678901", "123 Main St");
	std::string generateId = contact.getId();

	// Add contact twice to map
	service.addContact(contact);
	service.addContact(contact);

	EXPECT_NE(service.contacts.size(), 2);

	// Search contact's map for object with id
	auto it = service.contacts.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.contacts.end());

	EXPECT_EQ(it->second.getFirstName(), "John");
	EXPECT_EQ(it->second.getLastName(), "Doe");
	EXPECT_EQ(it->second.getPhoneNumber(), "12345678901");
	EXPECT_EQ(it->second.getAddress(), "123 Main St");
}

/*
	Tests that multiple Contact objects can be inserted into the map without issue.
*/
TEST(ContactServiceTest, MultipleAddContactsInsertsIntoMap)
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// vector to store id's
	std::vector<std::string> ids;

	// Construct five contacts and add their id's to vector
	Contact contact1("John", "Doe", "12345678901", "123 Main St");
	ids.push_back(contact1.getId());
	Contact contact2("Jane", "Doe", "12345678901", "456 Main St");
	ids.push_back(contact2.getId());
	Contact contact3("Jim", "Doe", "12345678901", "789 Main St");
	ids.push_back(contact3.getId());
	Contact contact4("Joan", "Doe", "12345678901", "012 Main St");
	ids.push_back(contact4.getId());
	Contact contact5("Jake", "Doe", "12345678901", "345 Main St");
	ids.push_back(contact5.getId());

	// add contacts to map
	service.addContact(contact1);
	service.addContact(contact2);
	service.addContact(contact3);
	service.addContact(contact4);
	service.addContact(contact5);

	// Expect that map size equals 5 with 5 contacts in it
	EXPECT_EQ(service.contacts.size(), 5);

	// Iterate through id's and prove each exists in the map
	for (int i = 0; i < 5; i++) {
		auto it = service.contacts.find(ids.at(i));
		EXPECT_NE(it, service.contacts.end());
	}
}

/*
	Basic test for numberOfContacts function
*/
TEST(ContactServiceTest, NumberOfContactsFunctionGivesCorrectResult)
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// construct contact and add to service
	Contact contact("John", "Doe", "12345678901", "123 Main St");
	service.addContact(contact);

	// expect that number of contacts is 1
	EXPECT_EQ(service.numberOfContacts(), 1);
}

/*
	Test that Contact object is deleted from map when function is called.
*/
TEST(ContactServiceTest, DeleteContactRemovesContactFromMap)
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// construct contact, get id and add to service
	Contact contact("John", "Doe", "12345678901", "123 Main St");
	std::string id = contact.getId();
	service.addContact(contact);

	// Check that contact object is in map -- sanity check
	ASSERT_EQ(service.contacts.size(), 1);

	// Delete contact from map using id
	service.deleteContact(id);

	EXPECT_EQ(service.contacts.size(), 0);
}

/*
	Test to show that the update function changes member variables on objects in the map
*/
TEST(ContactServiceTest, UpdateContactChangesContactFields)
{
	// stand up singleton instance of service
	ContactService& service = ContactService::getInstance();

	// clear previous state of hashmap
	service.contacts.clear();

	// construct contact, id and add to service
	Contact contact("John", "Doe", "12345678901", "123 Main St");
	service.addContact(contact);
    std::string id = contact.getId();

	// Check object existence in map and verify its name -- sanity check
	ASSERT_EQ(service.contacts.size(), 1);
	ASSERT_EQ(service.contacts[id].getFirstName(), "John");
	
	// Create new object to update contact
	Contact contactUpdate("Jonathan", "Dough", "12345678901", "123 Main St");

	// call update function using previous object ID and new object
	service.updateContact(id, contactUpdate);

	// Check object still exists in map -- sanity check
	ASSERT_EQ(service.contacts.size(), 1);

	EXPECT_EQ(service.contacts[id].getFirstName(), "Jonathan");
}

