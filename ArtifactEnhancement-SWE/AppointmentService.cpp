#include "AppointmentService.hpp"

/*
        Implementations of function declarations provided by AppointmentService.h
*/

// Constructor and destructor
AppointmentService::AppointmentService() {}
AppointmentService::~AppointmentService() {}

// Singleton instance
AppointmentService& AppointmentService::getInstance() {
    static AppointmentService instance;
    return instance;
}

// Add appointment
void AppointmentService::addAppointment(const Appointment& appointment) {
    appointments[appointment.getId()] = appointment;
}

// Update task
void AppointmentService::updateAppointment(const std::string& appointmentId, const Appointment& appointment) {
    appointments[appointmentId] = appointment;
}

// Delete task
void AppointmentService::deleteAppointment(const std::string& taskId) {
    appointments.erase(taskId);
}

// Number of task
int AppointmentService::numberOfAppointments() const {
    return appointments.size();
}