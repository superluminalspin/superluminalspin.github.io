package main;

public class Contact {
	
	/*
	 * Class declarations.
	 */
	private String id;
	private String firstName;
	private String lastName;
	private String phoneNumber;
	private String address;
	
	@SuppressWarnings("unused")
	// Don't allow class to be instantiated using no argument constructor
	private Contact() {
	}
	
	// Class constructor to create Contact objects
	public Contact(String id, String firstName, String lastName, String phoneNumber, String address) {
		
		// input verification, value cannot be a null value and cannot be longer than 10 characters
		if (firstName == null || firstName.length() > 10) {
			throw new IllegalArgumentException("Invalid first name");
		}
		
		// input verification, value cannot be a null value and cannot be longer than 10 characters
		if (lastName == null || lastName.length() > 10) {
			throw new IllegalArgumentException("Invalid last name");
		}
		
		// input verification, value cannot be a null value and cannot be longer than 10 characters
		if (id == null || id.length() > 10) {
			throw new IllegalArgumentException("Invalid id");
		}
		
		// input verification, value cannot be a null value and cannot be longer than 10 characters
		if (phoneNumber == null || phoneNumber.length() > 10) {
			throw new IllegalArgumentException("Invalid phone number");
		}
		
		// input verification, value cannot be a null value and cannot be longer than 30 characters
		if (address == null || address.length() > 30) {
			throw new IllegalArgumentException("Invalid address");
		}
		
		// if all input verification passes, set objects variable values
		this.id = id;
		this.firstName = firstName;
		this.lastName = lastName;
		this.phoneNumber = phoneNumber;
		this.address = address;
	}
	
	// method to get ID for key/value assignment in hash map
	public String getId() {
		return this.id;
	}
	
	// getter methods used for unit testing
	public String getFirstName() {
		return this.firstName;
	}
	
	// getter methods used for unit testing
	public String getLastName() {
		return this.lastName;
	}
	
	// getter methods used for unit testing
	public String getPhoneNumber() {
		return this.phoneNumber;
	}
	
	// getter methods used for unit testing
	public String getAddress() {
		return this.address;
	}

}
