#include "pch.h"
#include "AppointmentService.hpp"
#include "Appointment.hpp"
#include "InputValidator.hpp"
#include <vector>
#include <chrono>

/*
		Test package for AppointmentService.cpp
*/

/*
	Test that only one instance of the service class is allowed
*/
TEST(AppointmentServiceSingletonTest, ReturnSameInstance)
{
	AppointmentService& service1 = AppointmentService::getInstance();
	AppointmentService& service2 = AppointmentService::getInstance();

	// Expect that both references to Appointment Service classes are the same address
	EXPECT_EQ(&service1, &service2);
}

// Function to convert parse string date due to member function being unreachable from tests.
static std::chrono::year_month_day parseDate(const std::string& dateStr) {
	std::istringstream iss(dateStr);
	std::chrono::year_month_day ymd;
	iss >> std::chrono::parse("%Y-%m-%d", ymd);
	if (iss.fail()) throw std::invalid_argument("Invalid date format");
	return ymd;
}

/*
	Test that Appointments are correctly inserted into hashmap
*/
TEST(AppointmentServiceTest, AddAppointmentInsertsIntoMap)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// Create appointment object and get its id
	Appointment appointment("2025-09-20", "Doctor visit");
	std::string generateId = appointment.getId();

	// Add appointment to map
	service.addAppointment(appointment);

	EXPECT_EQ(service.appointments.size(), 1);

	// Search appointments's map for object with id
	auto it = service.appointments.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.appointments.end());

	EXPECT_EQ(it->second.getId(), "0001");
	EXPECT_EQ(it->second.getDate(), parseDate("2025-09-20"));
	EXPECT_EQ(it->second.getDescription(), "Doctor visit");
}

/*
	Test that duplicate inserts into hashmap fails, will apply a new ID to update appointment
*/
TEST(AppointmentServiceTest, DuplicateAppointmentsInsertionIntoMapFails)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// Create appointment object and get its id
	Appointment appointment("2025-09-20", "Doctor visit");
	std::string generateId = appointment.getId();

	// Add appointment to map twice
	service.addAppointment(appointment);
	service.addAppointment(appointment);

	EXPECT_NE(service.appointments.size(), 2);

	// Search appointments's map for object with id
	auto it = service.appointments.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.appointments.end());

	EXPECT_EQ(it->second.getId(), "0002");
	EXPECT_EQ(it->second.getDate(), parseDate("2025-09-20"));
	EXPECT_EQ(it->second.getDescription(), "Doctor visit");
}

/*
	Tests that multiple Appointment objects can be inserted into the map without issue.
*/
TEST(AppointmentServiceTest, MultipleAddAppointmentsInsertsIntoMap)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// vector to store id's
	std::vector<std::string> ids;

	// Construct five appointments and add their id's to vector
	Appointment appointment1("2025-09-20", "Doctor visit");
	ids.push_back(appointment1.getId());
	Appointment appointment2("2025-10-31", "Halloween!");
	ids.push_back(appointment2.getId());
	Appointment appointment3("2025-12-25", "Christmas dinner");
	ids.push_back(appointment3.getId());
	Appointment appointment4("2026-08-20", "Summer vacation");
	ids.push_back(appointment4.getId());
	Appointment appointment5("2026-09-01", "Labor Day");
	ids.push_back(appointment5.getId());


	// add appointments to map
	service.addAppointment(appointment1);
	service.addAppointment(appointment2);
	service.addAppointment(appointment3);
	service.addAppointment(appointment4);
	service.addAppointment(appointment5);

	// Expect that map size equals 5 with 5 appointments in it
	EXPECT_EQ(service.appointments.size(), 5);

	// Iterate through id's and prove each exists in the map
	for (int i = 0; i < 5; i++) {
		auto it = service.appointments.find(ids.at(i));
		EXPECT_NE(it, service.appointments.end());
	}
}

/*
	Basic test for numberOfAppointments function
*/
TEST(AppointmentServiceTest, NumberOfAppointmentsFunctionGivesCorrectResult)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// construct appointment and add to service
	Appointment appointment("2025-09-20", "Doctor visit");
	service.addAppointment(appointment);

	// expect that number of appointments is 1
	EXPECT_EQ(service.numberOfAppointments(), 1);
}

/*
	Test that Contact object is deleted from map when function is called.
*/
TEST(AppointmentServiceTest, DeleteAppointmentRemovesAppointmentFromMap)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// construct appointment, get id and add to service
	Appointment appointment("2025-09-20", "Doctor visit");
	std::string id = appointment.getId();
	service.addAppointment(appointment);

	// Check that appointment object is in map -- sanity check
	ASSERT_EQ(service.appointments.size(), 1);
	
	// Delete appointment object from map
	service.deleteAppointment(id);

	EXPECT_EQ(service.appointments.size(), 0);
}

/*
	Test to show that the update function changes member variables on objects in the map
*/
TEST(AppointmentServiceTest, UpdateAppointmentChangesAppointmentFields)
{
	// stand up singleton instance of service
	AppointmentService& service = AppointmentService::getInstance();

	// clear previous state of hashmap
	service.appointments.clear();

	// construct appointment, id and add to service
	Appointment appointment("2025-09-20", "Doctor visit");
	service.addAppointment(appointment);
	std::string id = appointment.getId();

	// Check object existence in map and verify its date -- sanity check
	ASSERT_EQ(service.appointments.size(), 1);
	ASSERT_EQ(service.appointments[id].getDate(), parseDate("2025-09-20"));

	// Create new object to update appointment
	Appointment appointmentUpdate("2025-11-21", "Thanksgiving");

	// call update function using previous object ID and new object
	service.updateAppointment(id, appointmentUpdate);

	// Check object still exists in map -- sanity check
	ASSERT_EQ(service.appointments.size(), 1);

	EXPECT_EQ(service.appointments[id].getDate(), parseDate("2025-11-21"));
	EXPECT_EQ(service.appointments[id].getDescription(), "Thanksgiving");
}