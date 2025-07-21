# **Student Record System**  

## **1. Overview**  
This **Student Record System** is a C program that allows users to manage student records, including:  
- Adding, modifying, and deleting student entries.  
- Searching for students by roll number.  
- Calculating average marks.  
- Sorting records by marks (ascending/descending).  
- Saving and loading records from a file (`student_records.txt`).  

---

## **2. Data Structures & Variables**  

### **`Student` Structure**  
Stores student details:  
```c
typedef struct {
    char name[MAX_NAME_LENGTH]; // Student name (max 50 chars)
    int rollNumber;             // Unique identifier
    float marks;                // Marks (float for decimal precision)
} Student;
```

### **Global Constants**  
| Constant | Value | Purpose |
|----------|-------|---------|
| `MAX_NAME_LENGTH` | `50` | Max length for student names |
| `FILENAME` | `"student_records.txt"` | File for saving/loading data |
| `PASSING_THRESHOLD` | `40` | Minimum marks to pass |

---

## **3. Core Functions**  

### **1. `void displayWelcomeMessage()`**  
- Displays a welcome message and prompts the user for their name.  

### **2. `void displayMenu()`**  
- Prints the main menu with available operations.  

### **3. `void addStudent(Student **students, int *count, int *capacity)`**  
- Adds a new student to the dynamic array.  
- Automatically expands memory if full (`realloc`).  
- Checks for duplicate roll numbers.  

### **4. `void displayAllStudents(Student *students, int count)`**  
- Lists all students in a formatted table.  
- Shows **Pass/Fail** status based on marks.  

### **5. `void modifyStudent(Student *students, int count)`**  
- Edits a student's name or marks by roll number.  

### **6. `void deleteStudent(Student *students, int *count)`**  
- Removes a student by shifting array elements.  

### **7. `void searchStudent(Student *students, int count)`**  
- Finds a student by roll number and displays details.  

### **8. `void calculateAverageMarks(Student *students, int count)`**  
- Computes and prints the average marks of all students.  

### **9. `void sortStudents(Student *students, int count, bool ascending)`**  
- Sorts students by marks (ascending or descending).  

### **10. `void saveToFile(Student *students, int count)`**  
- Saves records to `student_records.txt` in CSV format.  

### **11. `void loadFromFile(Student **students, int *count, int *capacity)`**  
- Loads records from the file (`FILENAME`).  

### **12. `void freeMemory(Student *students)`**  
- Frees dynamically allocated memory.  

---

## **4. File Format**  
Records are stored in `student_records.txt` as:  
```
John Doe,101,85.50
Jane Smith,102,35.00
```
- **Format**: `Name,RollNumber,Marks`  

---

## **5. How It Works**  
1. **Dynamic Memory Allocation**  
   - Uses `malloc` and `realloc` to manage student records.  
   - Doubles capacity when full.  

2. **Menu-Driven Interface**  
   - Users select options (1-10) to perform actions.  

3. **Error Handling**  
   - Checks for duplicate roll numbers.  
   - Handles file I/O errors.  

---

## **6. Example Usage**  
### **Adding a Student**  
1. Select **Option 1** (Add student).  
2. Enter:  
   - Name: `Alice Johnson`  
   - Roll Number: `103`  
   - Marks: `78.5`  

### **Searching a Student**  
1. Select **Option 5** (Search).  
2. Enter roll number (`103`).  
3. Output:  
   ```
   Student Found:
   Name: Alice Johnson
   Roll Number: 103
   Marks: 78.50
   Status: Pass
   ```

### **Saving Records**  
1. Select **Option 9** (Save to file).  
2. Records are stored in `student_records.txt`.  

---

## **7. Compilation & Execution**  
### **Compile (Terminal)**  
```sh
gcc student_record_system.c -o student_record_system
```

### **Run (Terminal)**  
- **Windows**:  
  ```sh
  .\student_record_system.exe
  ```
- **Mac/Linux**:  
  ```sh
  ./student_record_system
  ```

---

## **8. Future Improvements**  
- Add **more fields** (e.g., age, subjects).  
- Implement **password protection**.  
- Use **binary files** for efficient storage.  

---

This documentation covers all major aspects of the **Student Record System**. Let me know if you need further clarifications! 🚀
