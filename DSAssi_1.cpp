#include <iostream>
#include <string>
using namespace std;

struct Task {
    int taskID;
    string taskDescription;
    int taskPriority;
    Task* nextTask;
};

class TaskManager {
private:
    Task* taskHead;

public:
    TaskManager() : taskHead(nullptr) {}

    void insertTask(int taskID, string taskDescription, int taskPriority) {
        Task* newTask = new Task{taskID, taskDescription, taskPriority, nullptr};
        if (!taskHead || taskHead->taskPriority < taskPriority) {
            newTask->nextTask = taskHead;
            taskHead = newTask;
        } else {
            Task* temp = taskHead;
            while (temp->nextTask && temp->nextTask->taskPriority >= taskPriority) {
                temp = temp->nextTask;
            }
            newTask->nextTask = temp->nextTask;
            temp->nextTask = newTask;
        }
        cout << "Task successfully added!\n";
    }

    void deleteHighestPriorityTask() {
        if (!taskHead) {
            cout << "No tasks available for deletion!\n";
            return;
        }
        Task* temp = taskHead;
        taskHead = taskHead->nextTask;
        delete temp;
        cout << "Top priority task deleted!\n";
    }

    void deleteTaskByID(int taskID) {
        if (!taskHead) {
            cout << "No tasks available for deletion!\n";
            return;
        }
        if (taskHead->taskID == taskID) {
            Task* temp = taskHead;
            taskHead = taskHead->nextTask;
            delete temp;
            cout << "Task successfully deleted!\n";
            return;
        }
        Task* temp = taskHead;
        while (temp->nextTask && temp->nextTask->taskID != taskID) {
            temp = temp->nextTask;
        }
        if (!temp->nextTask) {
            cout << "Task ID not found!\n";
            return;
        }
        Task* toRemove = temp->nextTask;
        temp->nextTask = temp->nextTask->nextTask;
        delete toRemove;
        cout << "Task successfully deleted!\n";
    }

    void displayTaskList() {
        if (!taskHead) {
            cout << "No tasks in the list!\n";
            return;
        }
        Task* temp = taskHead;
        cout << "Task List:\n";
        while (temp) {
            cout << "Task ID: " << temp->taskID << " | Description: " << temp->taskDescription << " | Priority: " << temp->taskPriority << "\n";
            temp = temp->nextTask;
        }
    }
};

int main() {
    TaskManager taskManager;
    int choice, taskID, taskPriority;
    string taskDescription;

    do {
        cout << "\nTask Management Menu\n";
        cout << "1. Add Task\n2. View Tasks\n3. Delete Highest Priority Task\n4. Delete Task by ID\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> taskID;
                cin.ignore();
                cout << "Enter Task Description: ";
                getline(cin, taskDescription);
                cout << "Enter Task Priority: ";
                cin >> taskPriority;
                taskManager.insertTask(taskID, taskDescription, taskPriority);
                break;
            case 2:
                taskManager.displayTaskList();
                break;
            case 3:
                taskManager.deleteHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to delete: ";
                cin >> taskID;
                taskManager.deleteTaskByID(taskID);
                break;
            case 5:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}
