package test;

import static org.junit.jupiter.api.Assertions.*;
import java.time.*;
import org.junit.jupiter.api.Test;
import main.Appointment;

class AppointmentTest {
	
	// appointment date object to be used for unit testing
	private LocalDate apptDate = LocalDate.now();
	
	/*
	 * Class constructor testing
	 */
	
	// Test to ensure that Appointment objects are instantiated correctly
	@Test
	void testAppointmentClassConstructor() {
		// construct appointment object using date object
		Appointment appointment = new Appointment("01", apptDate, "description");
		// compare returned values from appointment's getter functions to those passed in the constructor
		assertTrue(appointment.getAppointmentId().equals("01"));
		assertTrue(appointment.getAppointmentDate().equals(apptDate));
		assertTrue(appointment.getAppointmentDescription().equals("description"));
	}
	
	/*
	 * Null input testing
	 */
	
	// Test to ensure that a null appointment ID cannot be passed to the constructor
	@Test
	void testAppointmentClassAppointmentIdIsNotNull() {
		// force exception by passing a null appointment ID into constructor
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment(null, apptDate, "description"));
	}
	
	// Test to ensure that a null appointment date cannot be passed to the constructor
	@Test
	void testAppointmentClassAppointmentDateIsNotNull() {
		// force exception by passing a null appointment date into constructor
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("01", null, "description"));
	}
	
	// Test to ensure that a null appointment description cannot be passed to the constructor
	@Test
	void testAppointmentClassAppointmentDescriptionIsNotNull() {
		// force exception by passing a null appointment description into constructor
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("01", apptDate, null));
	}
	
	/*
	 * Empty string input testing
	 */
	
	// Test to ensure that the appointment ID passed is not an empty string
	@Test
	void testAppointmentClassAppointmentIdIsNotEmptyString() {
		// force exception by passing an empty string into constructor for appointment ID
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("", apptDate, "description"));
	}
	
	// Test to ensure that the appointment description passed is not an empty string
	@Test
	void testAppointmentClassAppointmentDescriptionIsNotEmptyString() {
		// force exception by passing an empty string into constructor for appointment description
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("01", apptDate, ""));
	}
	
	/*
	 * Input length testing
	 */
	
	// Test to ensure that the appointment ID passed is not longer than 10 characters
	@Test
	void testAppointmentClassAppointmentIdIsNotTooLong() {
		// pass appointment ID with 11 characters to force exception
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("01234567890", apptDate, "description"));
	}
	
	// Test to ensure that the appointment description passed is not longer than 50 characters
	@Test
	void testAppointmentClassAppointmentDescriptionIsNotTooLong() {
		// pass appointment description with 51 characters to force exception
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("0123456789", apptDate, 
						"012345678901234567890123456789012345678901234567890"));
	}

	/*
	 * Date testing
	 */
	
	// Test to ensure that appointment objects cannot be created with dates older than present day
	@Test
	void testAppointmentClassCreateAppointmentWithPastDate() {
		// create local date object with a date older than present day
		LocalDate pastDate = LocalDate.of(2020, 11, 22);
		// force exception by attempting to construct appointment object with a date older than present day
		assertThrows(IllegalArgumentException.class, 
				() -> new Appointment("01", pastDate, "description"));
	}
	
	// Test that appointments with the current date can be added
	@Test
	void testAppointmentClassCreateAppointmentWithCurrentDate() {
		// create object using current date
		LocalDate currDate = LocalDate.now();
		// ensure no exceptions are thrown when passing current date into the appointment constructor
		assertDoesNotThrow(() -> new Appointment("01", currDate, "description"));
	}
}
