package main;

import java.time.*;

public class Appointment {
	
	private String appointmentId;
	private LocalDate appointmentDate;
	private String appointmentDescription;
	
	// hide parameterless constructor so the class cannot be instantiated using it
	@SuppressWarnings("unused")
	private Appointment() {}
	
	// constructor used to form Appointment objects
	// requires instantiation of date object with the appointment date prior to calling this constructor
	public Appointment(String appointmentId, LocalDate appointmentDate,
			String appointmentDescription) {
		
		// object containing current date
		LocalDate now = LocalDate.now();
		System.out.println(now);
		
		// input validation when calling constructor for appointment ID parameter
		if (appointmentId == null || appointmentId.length() > 10 || appointmentId == "") {
			throw new IllegalArgumentException("Invalid appointment ID");
		}
		
		// input validation when calling constructor for appointment date parameter
		if (appointmentDate == null || appointmentDate.isBefore(now)) {
			throw new IllegalArgumentException("Invalid appointment date");
		}
		
		// input validation when calling constructor for appointment description parameter
		if (appointmentDescription == null || appointmentDescription == ""
				|| appointmentDescription.length() > 50) {
			throw new IllegalArgumentException("Invalid appointment description");
		}
		
		// if all input is validated, assign object values
		this.appointmentId = appointmentId;
		this.appointmentDate = appointmentDate;
		this.appointmentDescription = appointmentDescription;
	}
	
	// function to return appointment id -- used for testing purposes
	public String getAppointmentId() {
		return this.appointmentId;
	}
	
	// function to return appointment date -- used for testing purposes
	public LocalDate getAppointmentDate() {
		return this.appointmentDate;
	}
	
	// function to return appointment description -- used for testing purposes
	public String getAppointmentDescription() {
		return this.appointmentDescription;
	}
}
