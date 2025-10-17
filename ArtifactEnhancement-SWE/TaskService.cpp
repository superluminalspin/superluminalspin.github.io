#include "TaskService.hpp"

/*
        Implementations of function declarations provided by TaskService.h
*/

// Constructor and destructor
TaskService::TaskService() {}
TaskService::~TaskService() {}

// Singleton instance
TaskService& TaskService::getInstance() {
    static TaskService instance;
    return instance;
}

// Add task
void TaskService::addTask(const Task& task) {
    tasks[task.getId()] = task;
}

// Update task
void TaskService::updateTask(const std::string& taskId, const Task& task) {
    tasks[taskId] = task;
}

// Delete task
void TaskService::deleteTask(const std::string& taskId) {
    tasks.erase(taskId);
}

// Number of task
int TaskService::numberOfTasks() const {
    return tasks.size();
}