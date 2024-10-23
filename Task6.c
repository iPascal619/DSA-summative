nclude <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 200

// Structure for a task node
struct Task {
    int id;
    char description[MAX_DESC];
    int completed;
    struct Task* next;
};

struct Task* head = NULL;
int nextId = 1;

// Function to create a new task
struct Task* createTask(char* description) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    newTask->id = nextId++;
    strcpy(newTask->description, description);
    newTask->completed = 0;
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the list
void addTask(char* description) {
    struct Task* newTask = createTask(description);
    
    if (head == NULL) {
        head = newTask;
        return;
    }
    
    struct Task* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newTask;
}

// Function to remove a task by ID
void removeTask(int id) {
    struct Task* current = head;
    struct Task* prev = NULL;
    
    // If head node itself holds the task to be deleted
    if (current != NULL && current->id == id) {
        head = current->next;
        free(current);
        printf("Task %d removed successfully!\n", id);
        return;
    }
    
    // Search for the task to be deleted
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    // If task was not found
    if (current == NULL) {
        printf("Task %d not found!\n", id);
        return;
    }
    
    // Unlink the node from linked list
    prev->next = current->next;
    free(current);
    printf("Task %d removed successfully!\n", id);
}

// Function to mark a task as completed and remove it
void markCompleted(int id) {
    struct Task* current = head;
    
    while (current != NULL) {
        if (current->id == id) {
            current->completed = 1;
            printf("Task %d marked as completed!\n", id);
            removeTask(id);  // Automatically remove completed task
            return;
        }
        current = current->next;
    }
    
    printf("Task %d not found!\n", id);
}

// Function to display all tasks
void displayTasks() {
    struct Task* current = head;
    
    if (current == NULL) {
        printf("No tasks in the list!\n");
        return;
    }
    
    printf("\nCurrent Tasks:\n");
    printf("ID\tStatus\t\tDescription\n");
    printf("----------------------------------------\n");
    
    while (current != NULL) {
        printf("%d\t%s\t%s\n", 
               current->id, 
               current->completed ? "Completed" : "Pending",
               current->description);
        current = current->next;
    }
}

int main() {
    int choice, id;
    char description[MAX_DESC];
    
    do {
        printf("\nTo-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Completed\n");
        printf("3. Remove Task\n");
        printf("4. Display Tasks\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  
        
        switch(choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, MAX_DESC, stdin);
                description[strcspn(description, "\n")] = 0;
                addTask(description);
                printf("Task added successfully!\n");
                break;
                
            case 2:
                printf("Enter task ID to mark as completed: ");
                scanf("%d", &id);
                markCompleted(id);
                break;
                
            case 3:
                printf("Enter task ID to remove: ");
                scanf("%d", &id);
                removeTask(id);
                break;
                
            case 4:
                displayTasks();
                break;
                
            case 5:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    
    // Free memory before exiting
    struct Task* current = head;
    while (current != NULL) {
        struct Task* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
