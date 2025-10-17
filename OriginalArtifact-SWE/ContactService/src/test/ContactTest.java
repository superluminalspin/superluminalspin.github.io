package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import main.Contact;

class ContactTest {
	
	// shortcut method to create and return a contact object
	public Contact returnContact(){
		return new Contact("1234567890", "Daryn", "Mann", "5555555555", "123 Oak Street");
	}
	
	
	/*
	 * The following unit tests pertain to the constructor of the Contact class.
	 */
	
	// This test ensures that the constructor creates objects correctly.
	@Test
	void testContactClass() {
		// call contact creation method
		Contact contact = returnContact();
		// five statements that all need to return true in order to pass object creation
		assertTrue(contact.getId().equals("1234567890"));
		assertTrue(contact.getFirstName().equals("Daryn"));
		assertTrue(contact.getLastName().equals("Mann"));
		assertTrue(contact.getPhoneNumber().equals("5555555555"));
		assertTrue(contact.getAddress().equals("123 Oak Street"));
	}
	
	/*
	 * The following unit tests pertain to the length of the values passed into the constructor.
	 */
	
	// This test checks if the id passed to the constructor is longer than 10 characters.
	@Test
	void testContactClassIdTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("123456789000000000000000", "Daryn", "Mann", "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the firstName passed to the constructor is longer than 10 characters.
	@Test
	void testContactClassFirstNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Darynnnnnnnnnnnnnnnnnnnnnn", "Mann", "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the lastName passed to the constructor is longer than 10 characters.
	@Test
	void testContactClassLastNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Daryn", "Mannnnnnnnnnnnnnnnnnnnnnnnn", "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the phoneNumber passed to the constructor is longer than 10 characters.
	@Test
	void testContactClassPhoneNumberTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Daryn", "Mann", "555555555555555555555555555555", "123 Oak Street");
		});
	}

	// This test checks if the address passed to the constructor is longer than 30 characters.
	@Test
	void testContactClassAddressTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "Daryn", "Mann", "5555555555", 
					"123 Oak Streetttttttttttttttttttttttttttttttttttttttttttttttttttt");
		});
	}
	
	/*
	 * The following tests pertain to if the values passed are null.
	 */
	
	// This test checks if the id is null.
	@Test
	void testContactClassIdIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact(null, "Daryn", "Mann", "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the firstName is null
	@Test
	void testContactClassFirstNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("0", null, "Mann", "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the lastName is null
	@Test
	void testContactClassLastNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("0", "Daryn", null, "5555555555", "123 Oak Street");
		});
	}
	
	// This test checks if the phoneNumber is null
	@Test
	void testContactClassPhoneNumberIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("0", "Daryn", "Mann", null, "123 Oak Street");
		});
	}
	
	// FIXME: Add test for non-numeric characters in phone number
	
	// This test checks if the address is null
	@Test
	void testContactClassAddressIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("0", "Daryn", "Mann", "5555555555", null);
		});
	}
}
