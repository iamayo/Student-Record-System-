#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define FILENAME "student_records.txt"
#define PASSING_THRESHOLD 40

typedef struct {
    char name[MAX_NAME_LENGTH];
    int rollNumber;
    float marks;
} Student;

void displayWelcomeMessage();
void displayMenu();
void addStudent(Student **students, int *count, int *capacity);
void displayAllStudents(Student *students, int count);
void modifyStudent(Student *students, int count);
void deleteStudent(Student *students, int *count);
void searchStudent(Student *students, int count);
void calculateAverageMarks(Student *students, int count);
void sortStudents(Student *students, int count, bool ascending);
void saveToFile(Student *students, int count);
void loadFromFile(Student **students, int *count, int *capacity);
void freeMemory(Student *students);

int main() {
    displayWelcomeMessage();
    
    int capacity = 5;
    int count = 0;
    Student *students = (Student *)malloc(capacity * sizeof(Student));
    
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent(&students, &count, &capacity);
                break;
            case 2:
                displayAllStudents(students, count);
                break;
            case 3:
                modifyStudent(students, count);
                break;
            case 4:
                deleteStudent(students, &count);
                break;
            case 5:
                searchStudent(students, count);
                break;
            case 6:
                calculateAverageMarks(students, count);
                break;
            case 7:
                sortStudents(students, count, true); // ascending
                break;
            case 8:
                sortStudents(students, count, false); // descending
                break;
            case 9:
                saveToFile(students, count);
                break;
            case 10:
                loadFromFile(&students, &count, &capacity);
                break;
            case 0:
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    freeMemory(students);
    printf("Thank you for using the Student Record System. Goodbye!\n");
    return 0;
}

void displayWelcomeMessage() {
    char name[50];
    printf("Welcome to the Student Record System!\n");
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character
    
    // If fgets didn't read anything (buffer was empty)
    if (strlen(name) == 0) {
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
    }
    
    printf("Hello, %s! Let's get started.\n\n", name);
}

void displayMenu() {
    printf("\nStudent Record System Menu:\n");
    printf("1. Add a new student\n");
    printf("2. Display all students\n");
    printf("3. Modify a student record\n");
    printf("4. Delete a student record\n");
    printf("5. Search for a student by roll number\n");
    printf("6. Calculate average marks\n");
    printf("7. Sort students by marks (ascending)\n");
    printf("8. Sort students by marks (descending)\n");
    printf("9. Save records to file\n");
    printf("10. Load records from file\n");
    printf("0. Exit\n");
}

void addStudent(Student **students, int *count, int *capacity) {
    if (*count >= *capacity) {
        *capacity *= 2;
        *students = (Student *)realloc(*students, *capacity * sizeof(Student));
        if (*students == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
    }
    
    Student newStudent;
    
    printf("Enter student name: ");
    getchar(); // Consume the newline character left by previous scanf
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // Remove newline
    
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    
    // Check if roll number already exists
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].rollNumber == newStudent.rollNumber) {
            printf("Error: A student with this roll number already exists.\n");
            return;
        }
    }
    
    printf("Enter marks: ");
    scanf("%f", &newStudent.marks);
    
    (*students)[*count] = newStudent;
    (*count)++;
    
    printf("Student added successfully!\n");
}

void displayAllStudents(Student *students, int count) {
    if (count == 0) {
        printf("No student records available.\n");
        return;
    }
    
    printf("\n%-20s %-15s %-10s %s\n", "Name", "Roll Number", "Marks", "Status");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-20s %-15d %-10.2f %s\n", 
               students[i].name, 
               students[i].rollNumber, 
               students[i].marks,
               students[i].marks >= PASSING_THRESHOLD ? "Pass" : "Fail");
    }
}

void modifyStudent(Student *students, int count) {
    if (count == 0) {
        printf("No student records available to modify.\n");
        return;
    }
    
    int rollNumber;
    printf("Enter the roll number of the student to modify: ");
    scanf("%d", &rollNumber);
    
    int foundIndex = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }
    
    printf("Current details for student %d:\n", rollNumber);
    printf("Name: %s\n", students[foundIndex].name);
    printf("Marks: %.2f\n", students[foundIndex].marks);
    
    printf("Enter new name (or press enter to keep current): ");
    getchar(); // Consume the newline character
    char newName[MAX_NAME_LENGTH];
    fgets(newName, MAX_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = '\0'; // Remove newline
    
    if (strlen(newName) > 0) {
        strcpy(students[foundIndex].name, newName);
    }
    
    printf("Enter new marks (or -1 to keep current): ");
    float newMarks;
    scanf("%f", &newMarks);
    
    if (newMarks >= 0) {
        students[foundIndex].marks = newMarks;
    }
    
    printf("Student record updated successfully!\n");
}

void deleteStudent(Student *students, int *count) {
    if (*count == 0) {
        printf("No student records available to delete.\n");
        return;
    }
    
    int rollNumber;
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);
    
    int foundIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNumber) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex == -1) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }
    
    // Shift all elements after the found index one position left
    for (int i = foundIndex; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    
    (*count)--;
    printf("Student record deleted successfully!\n");
}

void searchStudent(Student *students, int count) {
    if (count == 0) {
        printf("No student records available to search.\n");
        return;
    }
    
    int rollNumber;
    printf("Enter the roll number to search: ");
    scanf("%d", &rollNumber);
    
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("\nStudent Found:\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Marks: %.2f\n", students[i].marks);
            printf("Status: %s\n", students[i].marks >= PASSING_THRESHOLD ? "Pass" : "Fail");
            return;
        }
    }
    
    printf("Student with roll number %d not found.\n", rollNumber);
}

void calculateAverageMarks(Student *students, int count) {
    if (count == 0) {
        printf("No student records available to calculate average.\n");
        return;
    }
    
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += students[i].marks;
    }
    
    float average = sum / count;
    printf("Average marks of all students: %.2f\n", average);
}

void sortStudents(Student *students, int count, bool ascending) {
    if (count == 0) {
        printf("No student records available to sort.\n");
        return;
    }
    
    // Simple bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((ascending && students[j].marks > students[j + 1].marks) ||
                (!ascending && students[j].marks < students[j + 1].marks)) {
                // Swap
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    printf("Students sorted by marks in %s order:\n", ascending ? "ascending" : "descending");
    displayAllStudents(students, count);
}

void saveToFile(Student *students, int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%.2f\n", students[i].name, students[i].rollNumber, students[i].marks);
    }
    
    fclose(file);
    printf("Successfully saved %d student records to %s\n", count, FILENAME);
}

void loadFromFile(Student **students, int *count, int *capacity) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading or file doesn't exist.\n");
        return;
    }
    
    *count = 0;
    char line[100];
    
    while (fgets(line, sizeof(line), file)) {
        if (*count >= *capacity) {
            *capacity *= 2;
            *students = (Student *)realloc(*students, *capacity * sizeof(Student));
            if (*students == NULL) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
        }
        
        char *token;
        token = strtok(line, ",");
        if (token) strcpy((*students)[*count].name, token);
        
        token = strtok(NULL, ",");
        if (token) (*students)[*count].rollNumber = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) (*students)[*count].marks = atof(token);
        
        (*count)++;
    }
    
    fclose(file);
    printf("Successfully loaded %d student records from %s\n", *count, FILENAME);
}

void freeMemory(Student *students) {
    free(students);
}
