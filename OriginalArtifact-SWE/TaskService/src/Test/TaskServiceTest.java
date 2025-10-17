package Test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import main.Task;
import main.TaskService;

/*
 * Test class for the TestService Class
 */

class TaskServiceTest {
	
	// create new local instance of taskService
	private TaskService taskService = new TaskService();

	// test case for adding a null object
	@Test
	void testTestServiceClassAddTaskNullTask() {
		assertThrows(IllegalArgumentException.class, () -> taskService.addTask(null));
	}
	
	// test case for adding an object that already exists in the map
	@Test
	void testTestServiceClassAddExistingTask() {
		// create new task
		Task task = new Task("55", "Task #1", "The first task");
		// add task to map
		taskService.addTask(task);
		// force error by adding the same task to map
		assertThrows(IllegalArgumentException.class, () -> taskService.addTask(task));
	}
	
	// test case to add task without failure
	@Test
	void testTestServiceClassAddTask() {
		// create new task
		Task task = new Task("55", "Task #1", "The first task");
		// add task to map
		taskService.addTask(task);
		// check map for taskId
		assertTrue(taskService.tasks.containsKey(task.getTaskId()));
	}
	
	// test case to delete null task object
	@Test
	void testTestServiceClassDeleteNullTask() {
		// force error by attempting to delete null task object
		assertThrows(IllegalArgumentException.class, ()-> taskService.deleteTask(null));
	}
	
	// test case to delete a task that isn't in map
	@Test
	void testTestServiceClassDeleteTaskThatDoesntExist() {
		// force error by attempting to delete an task object that isn't in map
		assertThrows(IllegalArgumentException.class, ()-> taskService.deleteTask("55"));
	}
	
	// test case to delete a task whose taskId is longer than 10 characters
	@Test
	void testTestServiceClassDeleteTaskIdTooLong() {
		// force error by attempting to delete a task when taskId is 11 characters
		assertThrows(IllegalArgumentException.class, ()-> taskService.deleteTask("01234567890"));
	}
	
	// test case to update task when the taskId is null
	@Test
	void testTaskServiceClassUpdateTaskIdIsNull() {
		// check for exception thrown when id is null
		assertThrows(IllegalArgumentException.class, 
				() -> taskService.updateTask(null, "Task #1", "The first task"));
	}
	
	// test case to update task using a taskId that isn't in the map
	@Test
	void testTaskServiceClassUpdateTaskUsingTaskIdThatDoesntExist() {
		// force exception by attempting to update an empty map
		assertThrows(IllegalArgumentException.class, 
				() -> taskService.updateTask("55", "Task #1", "The first task"));
	}
	
	// test case to update task when taskId is longer than 10 characters
	@Test
	void testTestServiceClassUpdateTaskIdTooLong() {
		// force exception by attempting to update a task with a taskId of 11 characters
		assertThrows(IllegalArgumentException.class, 
				()-> taskService.updateTask("01234567890", "Task #1", "The first task"));
	}
	
	// test case to update task successfully
	@Test
	void testTestServiceClassUpdateTaskUpdatedSucessfully() {
		// create new task object
		Task task = new Task("55", "Task #1", "The first task");
		// add task to map
		taskService.addTask(task);
		// call update task method with a different name and description
		taskService.updateTask("55", "Task #2", "The first task, again");
		// check that the name was changed
		assertEquals("Task #2", taskService.tasks.get("55").getName());
		// check that the description was changed
		assertEquals("The first task, again", taskService.tasks.get("55").getDescription());
	}
	
	// test case to confirm that multiple tasks can be added to and retrieved from the hash map
	@Test
	void testTestServiceClassMultipleTasksAddedSuccessfully() {
		// create first task object
		Task task1 = new Task("55", "Task #1", "The first task");
		// create second task object
		Task task2 = new Task("66", "Task #2", "The second task");
		// add first task object to hash map
		taskService.addTask(task1);
		// add second task object to hash map
		taskService.addTask(task2);
		// verify the objects are in map by boolean comparison
		assertEquals("Task #1", taskService.tasks.get("55").getName());
		assertEquals("Task #2", taskService.tasks.get("66").getName());
	}
}
