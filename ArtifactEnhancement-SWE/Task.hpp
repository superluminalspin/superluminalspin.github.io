#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <iomanip>
#include <sstream>

/*
		Model class for Task objects to be handled by TaskService.cpp
*/

class Task {
private:
	// Class member variables
	std::string taskId;
	std::string name;
	std::string description;

public:
	Task() {}
	// Constructor does not take an ID number and instead generates a unique one when called.
	Task(
		const std::string& name, 
		const std::string& description) 
		: taskId(generateIdNumber()), // generate unique ID on object creation
		  name(name),
		  description(description)
			{}

	// Getter functions
	const std::string& getId() const { return taskId; }
	const std::string& getName() const { return name; }
	const std::string& getDescription() const { return description; }

	// Generate sequential 4 digit ID number starting with 0001
	static std::string generateIdNumber(int width = 4)
	{
		static int counter = 1;
		std::ostringstream oss;
		oss << std::setw(width) << std::setfill('0') << counter++;
		return oss.str();
	}

	// Object to string method for output
	std::string toString() const
	{
		return "Task ID: " + taskId + " -- Task Name: " + name + " -- Description: " + description + "\n";
	}
};

#endif