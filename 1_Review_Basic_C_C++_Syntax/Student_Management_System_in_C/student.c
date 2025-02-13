#include "student.h"

// Load students from a file
int loadStudents(Student students[]) {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        return 0;
    }

    int count = 0;
    while (fread(&students[count], sizeof(Student), 1, file) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

// Save students to a file
void saveStudents(Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&students[i], sizeof(Student), 1, file);
    }

    fclose(file);
}

// Add a new student
void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    Student newStudent;
    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter student name: ");
    scanf("%49s", newStudent.name);
    printf("Enter student grade: ");
    scanf("%f", &newStudent.grade);

    students[*count] = newStudent;
    (*count)++;
}

// View all students
void viewStudents(Student students[], int count) {
    printf("ID\tName\tGrade\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].grade);
    }
}

// Update a student's information
void updateStudent(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Enter new student name: ");
            scanf("%49s", students[i].name);
            printf("Enter new student grade: ");
            scanf("%f", &students[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Delete a student
void deleteStudent(Student students[], int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}
