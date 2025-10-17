#ifndef APPOINTMENTSERVICE_H
#define APPOINTMENTSERVICE_H

#include <iostream>
#include <unordered_map>
#include "Appointment.hpp"

/*
		Service class to provide functionality for Appointment objects
*/

class AppointmentService {
private:
	// Hide default constructor and destructor
	AppointmentService();
	~AppointmentService();

public:
	// Hashmap to store tasks, key = id, value = appointment object
	std::unordered_map<std::string, Appointment> appointments;

	// Delete copy constructor and assignment operator to prevent copying
	AppointmentService(const AppointmentService&) = delete;
	AppointmentService& operator=(const AppointmentService&) = delete;

	// Static function to access singleton instance
	static AppointmentService& getInstance();

	// Class function to add appointment to map
	void addAppointment(const Appointment& task);

	// Class function to update appointment in map
	void updateAppointment(const std::string& taskId, const Appointment& task);

	// Class function to delete appointment in map
	void deleteAppointment(const std::string& taskId);

	// Class function to find number of appointment objects in map
	int numberOfAppointments() const;
};
#endif