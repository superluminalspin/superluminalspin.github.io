#include "pch.h"
#include "TaskService.hpp"
#include "Task.hpp"
#include "InputValidator.hpp"
#include <vector>

/*
		Test package for TaskService.cpp
*/



/*
	Test that Tasks are correctly inserted into hashmap
*/
TEST(TaskServiceTest, AddTaskInsertsIntoMap)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// Create task object and get its id
	Task task("Walking", "Walking for one hour in the park");
	std::string generateId = task.getId();

	// Add Task object to map
	service.addTask(task);

	EXPECT_EQ(service.tasks.size(), 1);
	
	// Search task's map for object with id
	auto it = service.tasks.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.tasks.end());

	EXPECT_EQ(it->second.getId(), "0001");
	EXPECT_EQ(it->second.getName(), "Walking");
	EXPECT_EQ(it->second.getDescription(), "Walking for one hour in the park");
}

/*
	Test that duplicate inserts into hashmap fails, will apply a new ID to update task
*/
TEST(TaskServiceTest, DuplicateTasksInsertionIntoMapFails)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// Create task object and get its id
	Task task("Walking", "Walking for one hour in the park");
	std::string generateId = task.getId();

	// Attempt to add the same task twice
	service.addTask(task);
	service.addTask(task);

	EXPECT_NE(service.tasks.size(), 2);

	// Search task's map for object with id
	auto it = service.tasks.find(generateId);
	// Assert that the object is found in the map -- sanity check
	ASSERT_NE(it, service.tasks.end());

	EXPECT_EQ(it->second.getId(), "0002");
	EXPECT_EQ(it->second.getName(), "Walking");
	EXPECT_EQ(it->second.getDescription(), "Walking for one hour in the park");
}

/*
	Tests that multiple Task objects can be inserted into the map without issue.
*/
TEST(TaskServiceTest, MultipleAddTasksInsertsIntoMap)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// vector to store id's
	std::vector<std::string> ids;

	// Construct five tasks and add their id's to vector
	Task task1("Walking", "Walking for one hour in the park");
	ids.push_back(task1.getId());
	Task task2("Running", "Running for two hours up the hill");
	ids.push_back(task2.getId());
	Task task3("Hiking", "Hiking for one hour in the mountains");
	ids.push_back(task3.getId());
	Task task4("Driving", "Driving for twenty hours to Colorado");
	ids.push_back(task4.getId());
	Task task5("Working", "Working for eight hours on Monday");
	ids.push_back(task5.getId());

	// add tasks to map
	service.addTask(task1);
	service.addTask(task2);
	service.addTask(task3);
	service.addTask(task4);
	service.addTask(task5);

	// Expect that map size equals 5 with 5 tasks in it
	EXPECT_EQ(service.tasks.size(), 5);

	// Iterate through id's and prove each exists in the map
	for (int i = 0; i < 5; i++) {
		auto it = service.tasks.find(ids.at(i));
		EXPECT_NE(it, service.tasks.end());
	}
}

/*
	Basic test for numberOfTasks function
*/
TEST(TaskServiceTest, NumberOfTasksFunctionGivesCorrectResult)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// construct task and add to service
	Task task("Walking", "Walking for one hour in the park");
	service.addTask(task);

	// expect that number of tasks is 1
	EXPECT_EQ(service.numberOfTasks(), 1);
}

/*
	Test that Task object is deleted from map when function is called.
*/
TEST(TaskServiceTest, DeleteTaskRemovesTaskFromMap)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// construct task and add to service
	Task task("Walking", "Walking for one hour in the park");
	service.addTask(task);

	// Assert that the object is in the map -- sanity check
	ASSERT_EQ(service.tasks.size(), 1);

	// Get task object id
	std::string id = task.getId();

	// Delete object
	service.deleteTask(id);

	EXPECT_EQ(service.tasks.size(), 0);
}

/*
	Test to show that the update function changes member variables on objects in the map
*/
TEST(TaskServiceTest, UpdateTaskChangesTaskFields)
{
	// stand up singleton instance of service
	TaskService& service = TaskService::getInstance();

	// clear previous state of hashmap
	service.tasks.clear();

	// construct task and add to service
	Task task("Walking", "Walking for one hour in the park");
	service.addTask(task);

	// Get task object id
	std::string id = task.getId();

	// Check object existence in map and verify its name -- sanity check
	ASSERT_EQ(service.tasks.size(), 1);
	ASSERT_EQ(service.tasks[id].getName(), "Walking");

	// Create a new task to update the current one
	Task taskUpdate("Cycling", "Downtown Monday");

	// Pass new task to update function with original objects id
	service.updateTask(id, taskUpdate);

	// Check object still exists in map -- sanity check
	ASSERT_EQ(service.tasks.size(), 1);

	EXPECT_EQ(service.tasks[id].getName(), "Cycling");
}

