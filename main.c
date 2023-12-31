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
    if (*head == NULL) {
        // If the list is empty, make the new student the head
        *head = newStudent;
        newStudent->next = *head;
    } else {
        struct Student* current = *head;

        // Traverse to the desired position
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }

        // Insert the new student at the specified position
        newStudent->next = current->next;
        current->next = newStudent;
    }
}

// Function to delete a student record from the front of the circular linked list
void deleteFront(struct Student** head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
    } else {
        struct Student* temp = *head;

        if (temp->next == *head) {
            // Only one element in the list
            *head = NULL;
        } else {
            // More than one element in the list
            struct Student* last = *head;

            // Traverse to the last node
            while (last->next != *head) {
                last = last->next;
            }

            *head = temp->next;
            last->next = *head;
        }

        free(temp);
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

// Function to search for a student record by roll number
struct Student* searchByKey(struct Student* head, int rollNumber) {
    struct Student* current = head;

    do {
        if (current->rollNumber == rollNumber) {
            return current;
        }
        current = current->next;
    } while (current != head);

    return NULL; // Student not found
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
        printf("2. Delete Student record from front\n");
        printf("3. Show Student record at front\n");
        printf("4. Search Student record by roll number\n");
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
                deleteFront(&head);
                printf("Student record deleted from front.\n");
                break;

            case 3:
                showFront(head);
                break;

            case 4:
                printf("Enter roll number to search: ");
                scanf("%d", &rollNumber);

                foundStudent = searchByKey(head, rollNumber);

                if (foundStudent != NULL) {
                    printf("Student record found:\n");
                    printf("Roll Number: %d\n", foundStudent->rollNumber);
                    printf("Name: %s\n", foundStudent->name);
                    printf("Course: %s\n", foundStudent->course);
                    printf("Marks: %.2f\n", foundStudent->marks);
                } else {
                    printf("Student record not found.\n");
                }
                break;

            case 5:
                printf("Enter roll number to update: ");
                scanf("%d", &rollNumber);

                foundStudent = searchByKey(head, rollNumber);

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
                    printf("Student record not found.\n");
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

