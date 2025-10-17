package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import main.Contact;
import main.ContactService;


class ContactServiceTest {
	
	// initialize an instance of the Contact Service class to be used in unit tests.
	private ContactService contactService = new ContactService();
	
	/*
	 * The following unit tests pertain to the addContact method of the ContactService class.
	 */
	
	// This test checks for cases in which the contact object is null.
	@Test
	void testContactServiceClassAddContactNullContact() {
		// check for exception thrown by adding a null object
		assertThrows(IllegalArgumentException.class, () -> contactService.addContact(null));
	}
	
	// This test checks for cases in which the contact's id already exists in the map.
	@Test
	void testContactServiceClassAddContactExistingContact() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add contact to the map in the ContactService class.
		contactService.addContact(contactA);
		// check for exception thrown if the contact's id already exists in the map.
		assertThrows(IllegalArgumentException.class, () -> contactService.addContact(contactA));
	}
	
	// This test checks if the contact object was added to the map successfully.
	@Test
	void testContactServiceClassAddContact() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add contact to the map in the ContactService class.
		contactService.addContact(contactA);
		// test passes when contact is found in the map after being added successfully
		assertTrue(contactService.contacts.containsKey(contactA.getId()));
	}
	
	/*
	 * The following unit tests pertain to the deleteContact method of the ContactService class.
	 */
	
	// This test checks if the object passed to the method is null.
	@Test
	void testContactServiceClassDeleteContactNullParameter() {
		// check for exception thrown when the object is null
		assertThrows(IllegalArgumentException.class, ()-> contactService.deleteContact(null));
	}
	
	// This test checks if a key is passed that is not in the map and cannot be deleted.
	@Test
	void testContactServiceClassDeleteContactKeyNotInMap() {
		// check for exception thrown when the key(id) is not eligible for deletion
		assertThrows(IllegalArgumentException.class, ()-> contactService.deleteContact("1"));
	}
	
	// This tests if the key(id) passed is longer than 10 characters.
	@Test
	void testContactServiceClassDeleteContactKeyTooLong() {
		// check for exception thrown when key(id) is too long
		assertThrows(IllegalArgumentException.class, 
				()-> contactService.deleteContact("01234567890"));
	}
	
	// This tests if the contact object is successfully deleted.
	@Test
	void testContactServiceClassDeleteContact() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add contact to the map in the ContactService class
		contactService.addContact(contactA);
		// delete contact using the contact's id
		contactService.deleteContact("0");
		// test passes if the map does not contain the key(id)/value pair anymore
		assertFalse(contactService.contacts.containsKey("0"));
	}
	
	/*
	 *  The following unit tests pertain to the updateContact method of the ContactService class.
	 */
	
	// This test checks if the id of the contact object is null
	@Test
	void testContactServiceClassUpdateContactNullId() {
		// check for exception thrown when id is null
		assertThrows(IllegalArgumentException.class, 
				() -> contactService.updateContact(null, "Daryn", "Mann", "5555555555", "123 Oak Street"));
	}
	
	// This test checks if the map does not contain the id passed as an argument
	@Test
	void testContactServiceClassUpdateContactKeyDoesntExist() {
		// test passes if the map does not contain the key(id)
		assertFalse(contactService.contacts.containsKey("0"));
	}
	
	// This test checks if the key(id) passed is longer than 10 characters.
	@Test
	void testContactServiceClassUpdateContactKeyTooLong() {
		// check for exception thrown when key(id) is too long
		assertThrows(IllegalArgumentException.class, 
				() -> contactService.updateContact("01234567890", "Daryn", "Mann", "5555555555", "123 Oak Street"));
	}
	
	// This test checks if the value (Contact object) of the key(id)/value pairs is updated
	@Test
	void testContactServiceClassUpdateContactContactUpdated() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add the contact to map
		contactService.addContact(contactA);
		// update the contact using the same id
		contactService.updateContact("0", "Dwayne", "Mann", "5555555555", "123 Oak Street");
		// true if contact object at the key(id) of the map is updated
		assertEquals("Dwayne", contactService.contacts.get("0").getFirstName());
	}
	
	/*
	 * The following tests pertain to confirming and retrieving objects added to hashmap
	 */
	// test case to confirm that multiple contacts can be added to and retrieved from the hash map
	@Test
	void testContactServiceClassMultipleContactsAddedSuccessfully() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// create new contact object using Contacts constructor
		Contact contactB = new Contact("1", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add first task object to hash map
		contactService.addContact(contactA);
		// add second task object to hash map
		contactService.addContact(contactB);
		// verify the objects are in map by boolean comparison
		assertEquals("0", contactService.contacts.get("0").getId());
		assertEquals("1", contactService.contacts.get("1").getId());
	}
	
	// Test that multiple contacts can be added to and retrieved from hash map
	@Test
	void testContactServiceClassAddMultipleContacts() {
		// create new contact object using Contacts constructor
		Contact contactA = new Contact("0", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// create new contact object using Contacts constructor
		Contact contactB = new Contact("1", "Daryn", "Mann", "5555555555", "123 Oak Street");
		// add first contact object to hash map
		contactService.addContact(contactA);
		// add second contact object to hash map
		contactService.addContact(contactB);
		// confirm contact objects are added by checking if their keys exist within it
		assertTrue(contactService.contacts.containsKey(contactA.getId()));
		assertTrue(contactService.contacts.containsKey(contactB.getId()));
		// confirm contact objects are added to the map by checking if their values exist within it
		assertTrue(contactService.contacts.containsValue(contactA));
		assertTrue(contactService.contacts.containsValue(contactB));
	}
}
