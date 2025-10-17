package main;

import java.util.HashMap;


public class TaskService {
/*
 * Task Service Requirements

	The task service shall be able to add tasks with a unique ID.
	The task service shall be able to delete tasks per task ID.
	The task service shall be able to update task fields per task ID. The following fields are updatable:
	Name and Description
 */
	// class declaration of data structure: hashmap
	// This is public for testing purposes only, it normally would be instantiated when the TaskService object
	// is constructed.
	public HashMap<String, Task> tasks = new HashMap<String, Task>();

	// default constructor, may be changed in future iterations
	public TaskService() {}
	
	// function to add task object to map
	public void addTask(Task task) {
		// handle the case where task object is null or task already exists in map
		if (task == null || tasks.containsKey(task.getTaskId())) {
			throw new IllegalArgumentException("Object is null or Task already exists");
		}
		// add task to map
		tasks.put(task.getTaskId(), task);
	}
	
	// function to delete task object from map
	public void deleteTask(String taskId) {
		// handle the case where task object is null, task isn't in map, or taskId is too long
		if (taskId == null || tasks.containsKey(taskId) == false || taskId.length() > 10) {
			throw new IllegalArgumentException("Invalid id");
		}
		// delete task from map
		tasks.remove(taskId);
	}
	
	// function to update task in the map
	public void updateTask(String taskId, String name, String description) {
		// handle the case where taskId is null, task isn't in map, or taskId is too long
		if (taskId == null || tasks.containsKey(taskId) == false || taskId.length() > 10) {
			throw new IllegalArgumentException("Invalid id");
		}
		// create a new task object using passed values
		Task task = new Task(taskId, name, description);
		
		// update task object in map using passed taskId and newly created task object
		tasks.put(taskId, task);
	}

}
