#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a student record
struct Student {
    int rollNumber;
    char name[50];
    char course[50];
    float marks;
    struct Student* next;
};
int nodeCount = 0;
// Function to create a new student record
struct Student* createStudent(int rollNumber, char name[], char course[], float marks) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->name, name);
    strcpy(newStudent->course, course);
    newStudent->marks = marks;
    newStudent->next = NULL;

    return newStudent;
}

// Function to insert a student record at a given position in the circular linked list
void insertAtPosition(struct Student** head, int position, struct Student* newStudent) {
    if (nodeCount == 10) {
        printf("Max limit reached\n");
        return;
    }
    if (*head == NULL) {
        // If the list is empty, make the new student the head
        *head = newStudent;
        newStudent->next = *head;
        nodeCount++;
    } else {
        if (position == 1) {
            // Insert at the front
            newStudent->next = *head;
            *head = newStudent;
            nodeCount++;
        } else {
            struct Student* current = *head;
            int currentPosition = 1;

            // Traverse to the end or the specified position
            while (current->next != *head && currentPosition < position - 1) {
                current = current->next;
                currentPosition++;
            }

            // Insert the new student at the specified position
            newStudent->next = current->next;
            current->next = newStudent;
            nodeCount++;
        }
    }
}

// Function to delete a student record from the last position of the circular linked list
void deleteLast(struct Student** head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
    } else {
        struct Student* current = *head;
        struct Student* prev = NULL;

        // Traverse to the last node
        while (current->next != *head) {
            prev = current;
            current = current->next;
        }

        // If only one element in the list
        if (prev == NULL) {
            free(current);
            *head = NULL;
        } else {
            prev->next = *head;
            free(current);
        }
    }
}

// Function to display the student record at the front of the circular linked list
void showFront(struct Student* head) {
    if (head == NULL) {
        printf("List is empty.\n");
    } else {
        printf("Roll Number: %d\n", head->rollNumber);
        printf("Name: %s\n", head->name);
        printf("Course: %s\n", head->course);
        printf("Marks: %.2f\n", head->marks);
    }
}

// Function to search for a student record by position
struct Student* searchByPosition(struct Student* head, int position) {
    if (head == NULL || position < 1 || position > nodeCount) {
        return NULL; // List is empty or invalid position
    }

    struct Student* current = head;
    int currentPosition = 1;

    do {
        if (currentPosition == position) {
            return current; // Student found at the specified position
        }

        current = current->next;
        currentPosition++;
    } while (current != head);

    return NULL; // Position not found
}

// Function to update a student record
void updateRecord(struct Student* student, char name[], char course[], float marks) {
    strcpy(student->name, name);
    strcpy(student->course, course);
    student->marks = marks;
}

// Function to display all student records in the circular linked list
void display(struct Student* head) {
    if (head == NULL) {
        printf("List is empty.\n");
    } else {
        struct Student* current = head;

        do {
            printf("Roll Number: %d\n", current->rollNumber);
            printf("Name: %s\n", current->name);
            printf("Course: %s\n", current->course);
            printf("Marks: %.2f\n", current->marks);
            printf("\n");

            current = current->next;
        } while (current != head);
    }
}

// Function to free the memory allocated for the circular linked list
void freeList(struct Student** head) {
    if (*head == NULL) {
        return;
    }

    struct Student* current = *head;
    struct Student* temp;

    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != *head);

    *head = NULL;
}

int main() {
    struct Student* head = NULL;
    struct Student* foundStudent;
    int choice, rollNumber, position;
    char name[50], course[50];
    float marks;

    do {
        printf("\n***** Student Record Management System *****\n");
        printf("1. Insert Student record at position\n");
        printf("2. Delete Student record from last\n");
        printf("3. Show Student record at front\n");
        printf("4. Search Student record by position\n");
        printf("5. Update Student record\n");
        printf("6. Display all Student records\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &rollNumber);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter course: ");
                scanf("%s", course);
                printf("Enter marks: ");
                scanf("%f", &marks);
                printf("Enter position to insert: ");
                scanf("%d", &position);

                insertAtPosition(&head, position, createStudent(rollNumber, name, course, marks));
                break;

            case 2:
                deleteLast(&head);
                printf("Student record deleted from last.\n");
                break;

            case 3:
                showFront(head);
                break;

            case 4:
                printf("Enter position to search: ");
                scanf("%d", &position);

                foundStudent = searchByPosition(head, position);

                if (foundStudent != NULL) {
                    printf("Student record found:\n");
                    printf("Roll Number: %d\n", foundStudent->rollNumber);
                    printf("Name: %s\n", foundStudent->name);
                    printf("Course: %s\n", foundStudent->course);
                    printf("Marks: %.2f\n", foundStudent->marks);
                } else {
                    printf("Student record not found at the specified position.\n");
                }
                break;

            case 5:
                printf("Enter position to update: ");
                scanf("%d", &position);

                foundStudent = searchByPosition(head, position);

                if (foundStudent != NULL) {
                    printf("Enter new name: ");
                    scanf("%s", name);
                    printf("Enter new course: ");
                    scanf("%s", course);
                    printf("Enter new marks: ");
                    scanf("%f", &marks);

                    updateRecord(foundStudent, name, course, marks);
                    printf("Student record updated.\n");
                } else {
                    printf("Student record not found at the specified position.\n");
                }
                break;
            case 6:
                display(head);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free the memory before exiting
    freeList(&head);

    return 0;
}


           
