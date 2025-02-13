#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100 // Corrected definition

// define the Student structure
typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

// function declaration
int loadStudents(Student students[]);
void saveStudents(Student students[], int count);
void addStudent(Student students[], int *count);
void viewStudents(Student students[], int count);
void updateStudent(Student students[], int count, int id);
void deleteStudent(Student students[], int *count, int id);

#endif // STUDENT_H
