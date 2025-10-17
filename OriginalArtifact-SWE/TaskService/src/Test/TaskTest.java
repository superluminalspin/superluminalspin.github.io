package Test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import main.Task;
/*
 * Test Class for the Task Class
 */
class TaskTest {
		
	// test case to make sure that the class instantiates properly using the constructor
	@Test
	void testTaskClass() {
		// create task object
		Task task = new Task("0123456789", "Task #1", "The first task");
		// run comparisons to make sure that the task object has the expected values
		assertTrue(task.getTaskId().equals("0123456789"));
		assertTrue(task.getName().equals("Task #1"));
		assertTrue(task.getDescription().equals("The first task"));
	}
	
	/*
	 * Tests to handle when input is longer than the maximum characters allowed
	 */
	
	// test case to make sure class cannot be instantiated with taskId longer than 10 characters
	@Test
	void testTaskClassTaskIdTooLong() {
		// force error by passing a taskId of 11 characters to the constructor
		assertThrows(IllegalArgumentException.class, 
				() -> new Task("01234567890", "Task #1", "The first task"));
	}
	
	// test case to make sure class cannot be instantiated with a name variable longer than 20 characters
	@Test
	void testTaskClassNameTooLong() {
		// force error by passing a name variable with 26 characters
		assertThrows(IllegalArgumentException.class, 
				() -> new Task("0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "The first task"));
	}
	
	
	// test case to make sure that the description variable isn't longer than 50 characters
	@Test
	void testTaskClassDescriptionTooLong() {
		// force error by passing a description variable of 78 characters
		assertThrows(IllegalArgumentException.class, 
				() -> new Task("01234567890", "Task #1", 
						"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	}
	
	/*
	 * Test cases to handle when input is null
	 */
	
	// test case to make sure class cannot be instantiated with null taskId
	@Test
	void testTaskClassTaskIdIsNull() {
		// force error by passing a null taskId into the constructor
		assertThrows(IllegalArgumentException.class, 
				() -> new Task(null, "Task #1", "The first task"));
	}
	
	// test case to make sure that the name variable isn't null
	@Test
	void testTaskClassNameIsNull() {
		// force error by passing a null name variable
		assertThrows(IllegalArgumentException.class, 
				() -> new Task("0123456789", null, "The first task"));
	}
	
	// test case to make sure that the description variable isn't null
	@Test
	void testTaskClassDescriptionIsNull() {
		// force error by passing a description variable that is null
		assertThrows(IllegalArgumentException.class, 
				() -> new Task("01234567890", "Task #1", null));
	}
	
	/*
	 * Test to handle when ID is an empty string
	 */
	@Test
	void testTaskClassIdIsEmptyString() {
		// force error by passing an empty string as an ID
		assertThrows(IllegalArgumentException.class, 
					() -> new Task("", "Task #1", "The first task"));
	}
	
}
