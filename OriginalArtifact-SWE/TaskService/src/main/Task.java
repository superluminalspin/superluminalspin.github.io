package main;

public class Task {
	
	// variable declarations
	private String taskId;
	private String name;
	private String description;
	
	// hide default constructor so that the class cannot be instantiated with it
	@SuppressWarnings("unused")
	private Task() {
	}
	
	// constructor accessible to other classes to create Task objects
	public Task(String taskId, String name, String description) {
		// input verification, value cannot be a null value, empty string, 
		// and cannot be longer than 10 characters
		if (taskId == null || taskId == "" || taskId.length() > 10) {
			throw new IllegalArgumentException("Invalid task ID");
		}
		// input verification, value cannot be a null value and cannot be longer than 20 characters
		if (name == null || name.length() > 20) {
			throw new IllegalArgumentException("Invalid name");
		}
		// input verification, value cannot be a null value and cannot be longer than 50 characters
		if (description == null || description.length() > 50) {
			throw new IllegalArgumentException("Invalid description");
		}
		// if all input is verified, assign values to object variables
		this.taskId = taskId;
		this.name = name;
		this.description = description;
	}
	
	// getter function for testing and taskService functions
	public String getTaskId() {
		return this.taskId;
	}
	
	// getter function for testing
	public String getName() {
		return this.name;
	}
	
	// getter function for testing
	public String getDescription() {
		return this.description;
	}
}
