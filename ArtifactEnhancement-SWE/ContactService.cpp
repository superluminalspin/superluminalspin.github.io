#include "ContactService.hpp"

/*
        Implementations of function declarations provided by ContactService.h
*/

// Constructor and destructor
ContactService::ContactService() {}
ContactService::~ContactService() {}

// Singleton instance
ContactService& ContactService::getInstance() {
    static ContactService instance;
    return instance;
}

// Add contact
void ContactService::addContact(const Contact& contact) {
    contacts[contact.getId()] = contact;
}

// Update contact
void ContactService::updateContact(const std::string& contactId, const Contact& contact) {
    contacts[contactId] = contact;
}

// Delete contact
void ContactService::deleteContact(const std::string& contactId) {
    contacts.erase(contactId);
}

// Number of contacts
int ContactService::numberOfContacts() const {
    return contacts.size();
}