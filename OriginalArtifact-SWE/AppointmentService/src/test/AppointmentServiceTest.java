package test;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import main.Appointment;
import main.AppointmentService;
import java.time.*;

class AppointmentServiceTest {

	// create local instance of AppointmentService class
	private AppointmentService appointmentService = new AppointmentService();
	
	// generic appointment date object for appointment object construction
	private LocalDate apptDate = LocalDate.now();
	
	/*
	 * Function testing for the add appointment function in the AppointmentService class
	 */
	
	// Test to confirm that the addAppointment function can add key/value pairs to the hash map
	@Test
	void testAppointmentServiceClassAddAppointment() {
		// create new appointment object using the apptDate object
		Appointment appointment = new Appointment("01", apptDate, "description");
		// put appointment into the hash map using the appointment ID as the key,
		// and the appointment object as the value
		appointmentService.addAppointment(appointment);
		// confirm appointment object added to hash map by checking if the key exists within it
		assertTrue(appointmentService.appointments.containsKey(appointment.getAppointmentId()));
		// confirm appointment object added to hash map by checking if the value exists within it
		assertTrue(appointmentService.appointments.containsValue(appointment));
	}
	
	// Test to confirm that appointment with null Appointment ID cannot be added to hash map
	@Test
	void testAppointmentServiceClassAddAppointmentWithNullAppointmentObject() {
		assertThrows(IllegalArgumentException.class, 
				() -> appointmentService.addAppointment(null));
	}
	
	// Test that multiple appointments can be added to and retrieved from hash map
	@Test
	void testAppointmentServiceClassAddMultipleAppointments() {
		// create new appointment object using the apptDate object
		Appointment appointment1 = new Appointment("01", apptDate, "description");
		// add appointment object to the appointmentService hash map
		appointmentService.addAppointment(appointment1);
		// create another appointment object using the same date object
		Appointment appointment2 = new Appointment("02", apptDate, "description");
		// add appointment object to the appointmentService hash map
		appointmentService.addAppointment(appointment2);
		// confirm appointment objects are added by checking if their keys exist within it
		assertTrue(appointmentService.appointments.containsKey(appointment1.getAppointmentId()));
		assertTrue(appointmentService.appointments.containsKey(appointment2.getAppointmentId()));
		// confirm appointment objects are added to the map by checking if their values exist within it
		assertTrue(appointmentService.appointments.containsValue(appointment1));
		assertTrue(appointmentService.appointments.containsValue(appointment2));
	}
	
	/*
	 * Function testing for the deleteAppointment function in the AppointmentService class
	 */
	
	// Test that appointment objects can be deleted from hash map after being added to it
	@Test
	void testAppointmentServiceClassDeleteAppointmentObject() {
		// create new appointment object using the apptDate object
		Appointment appointment = new Appointment("01", apptDate, "description");
		// add appointment object to the appointmentService hash map
		appointmentService.addAppointment(appointment);
		// confirm that appointment object is in map
		assertTrue(appointmentService.appointments.containsKey(appointment.getAppointmentId()));
		// delete appointment from map using the delete function and the appointment ID
		appointmentService.deleteAppointment(appointment.getAppointmentId());
		// confirm that the appointment doesn't exist in the map
		assertFalse(appointmentService.appointments.containsKey(appointment.getAppointmentId()));
	}
	
	// Test that a null appointment ID cannot be passed through the delete function
	@Test
	void testAppointmentServiceClassDeleteAppointmentAppointmentIdIsNull() {
		// force exception by passing a null appointment ID to the delete function
		assertThrows(IllegalArgumentException.class, 
				() -> appointmentService.deleteAppointment(null));
	}
	
	// Test that a appointment ID longer than 10 characters cannot be passed through the delete function
	@Test
	void testAppointmentServiceClassDeleteAppointmentAppointmentIdTooLong() {
		// force exception by passing a 11 character appointment ID to the delete function
		assertThrows(IllegalArgumentException.class, 
				() -> appointmentService.deleteAppointment("01234567890"));
	}
	
	// Test that a appointment ID that is an empty string cannot be passed through the delete function
	@Test
	void testAppointmentServiceClassDeleteAppointmentAppointmentIdIsEmptyString() {
		// force exception by passing a empty string appointment ID to the delete function
		assertThrows(IllegalArgumentException.class, 
				() -> appointmentService.deleteAppointment(""));
	}
}
