package main;

import java.util.HashMap;

public class ContactService {
	/*
	 * Class declarations... Hash map was chosen because it offers the ability to store objects based
	 * on a unique key, making sure that every contact has a unique id.
	 */
	public HashMap<String, Contact> contacts = new HashMap<String, Contact>();

	// This method is used to add a contact object to the hash map.
	public void addContact(Contact contact) {
		// input verification, value cannot be a null value and key(id) cannot exist in map
		if (contact == null || contacts.containsKey(contact.getId())) {
			throw new IllegalArgumentException("Object is null or Contact already exists");
		}
		// add key (id) / value (Contact object) pair to the map
		contacts.put(contact.getId(), contact);
	}
	
	// This method is used to delete a contact object from the hash map.
	public void deleteContact(String contactId) {
		// input verification, value cannot be a null value, key(id) must be in the map
		// and cannot be longer than 10 characters
		if (contactId == null || contacts.containsKey(contactId) == false || contactId.length() > 10) {
			throw new IllegalArgumentException("Invalid id");
		}
		// remove key(id) from the map
		contacts.remove(contactId);
	}
	
	// This method is used to update a Contact object. It uses the id to first check if the contact is in
	// the map, then a new Contact object is created using the values passed to the function.
	public void updateContact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
		if (contactId == null || contacts.containsKey(contactId) == false || contactId.length() > 10) {
			throw new IllegalArgumentException("Invalid id");
		}
		// create a new contact object using passed variables
		Contact newContact = new Contact(contactId, firstName, lastName, phoneNumber, address);
		// update contact in hash map using the contactId
		contacts.put(contactId, newContact);	
	}
}
