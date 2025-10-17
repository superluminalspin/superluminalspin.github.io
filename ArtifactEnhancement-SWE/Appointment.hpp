#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>

/*
		Model class for Appointment objects to be handled by AppointmentService.cpp
*/

class Appointment {
private:
	// Class member variables
	std::string appointmentId;
	std::chrono::year_month_day date;
	std::string description;
	
public:
	Appointment() {}
	// Constructor does not take an ID number and instead generates a unique one when called.
	Appointment(
		const std::string& dateStr,
		const std::string& description)
		: appointmentId(generateIdNumber()),
		  date(parseDate(dateStr)),
		  description(description) {}

	// Class getter functions
	const std::string& getId() const { return appointmentId; }
	const std::chrono::year_month_day& getDate() const { return date; }
	const std::string& getDescription() const { return description; }

	// Generate sequential 4 digit ID number starting with 0001
	static std::string generateIdNumber(int width = 4)
	{
		static int counter = 1;
		std::ostringstream oss;
		oss << std::setw(width) << std::setfill('0') << counter++;
		return oss.str();
	}
	
	// Function to convert a string object into a year_month_day chrono object for accuracy
	// and uniformity.
	static std::chrono::year_month_day parseDate(const std::string& dateStr) {
		std::istringstream iss(dateStr);
		std::chrono::year_month_day ymd;
		iss >> std::chrono::parse("%Y-%m-%d", ymd);
		if (iss.fail()) throw std::invalid_argument("Invalid date format");
		return ymd;
	}

	// Object to string method for output
	std::string toString() const {
		return "Appt ID: " + appointmentId 
			+ " -- Date: " 
			+ std::format("%Y-%m-%d", date) 
			+ " -- Description: " 
			+ description 
			+ "\n";
	}
};

#endif
