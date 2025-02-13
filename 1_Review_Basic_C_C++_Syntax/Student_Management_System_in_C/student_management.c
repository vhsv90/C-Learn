#include "student.h"

void showMenu() {
    printf("===== Student Management System =====\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Student students[MAX_STUDENTS];
    int count = loadStudents(students);

    while (1) {
        showMenu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                saveStudents(students, count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3: {
                int id;
                printf("Enter student ID to update: ");
                scanf("%d", &id);
                updateStudent(students, count, id);
                saveStudents(students, count);
                break;
            }
            case 4: {
                int id;
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(students, &count, id);
                saveStudents(students, count);
                break;
            }
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
