#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#include <iostream>
#include <unordered_map>
#include "Task.hpp"

class TaskService {
private:
	// Hide default constructor and destructor
	TaskService();
	~TaskService();

public:
	// Hashmap to store tasks, key = id, value = task object
	std::unordered_map<std::string, Task> tasks;

	// Delete copy constructor and assignment operator to prevent copying
	TaskService(const TaskService&) = delete;
	TaskService& operator=(const TaskService&) = delete;

	// Static function to access singleton instance
	static TaskService& getInstance();

	// Class function to add task to map
	void addTask(const Task& task);

	// Class function to update task in map
	void updateTask(const std::string& taskId, const Task& task);

	// Class function to delete task in map
	void deleteTask(const std::string& taskId);

	// Class function to find number of task objects in map
	int numberOfTasks() const;
};
#endif