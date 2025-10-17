package main;
import java.util.*;

public class AppointmentService {
	
	public HashMap<String, Appointment> appointments = new HashMap<>();
	
	public AppointmentService() {}
	
	public void addAppointment(Appointment appointment) {
		if (appointment == null) {
			throw new IllegalArgumentException("Appointment is null");
		}
		appointments.put(appointment.getAppointmentId(), appointment);
	}
	
	public void deleteAppointment(String appointmentId) {
		if (appointmentId == null || appointmentId == "" || appointmentId.length() > 10) {
			throw new IllegalArgumentException("Invalid appointment ID");
		}
		appointments.remove(appointmentId);
	}
}
