#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<windows.h>
#include<math.h>
#include<conio.h>

typedef struct students
{
    char name[100];
    char fname[100];
    char dept[50];
    int id;
    float cgpa;
} STUDENT;

void add(FILE *fp);
void display(FILE *fp);
void modify(FILE *fp);
void delete(FILE *fp);

int main(int argc, char const *argv[])
{
    system("color 9f");
    system("clear || cls");
    loadingScreen();

    SetConsoleTitle("Student Portal | UIU");

    FILE *fp;

    while (1)
    {

        title();


        int option;

        printf("\n\n\n");

        printf("\t\t\t\t\t\t1. Add Students\n");
        printf("\t\t\t\t\t\t2. Display Database\n");
        printf("\t\t\t\t\t\t3. Modify Student's information\n");
        printf("\t\t\t\t\t\t4. Remove Student's Information\n");
        printf("\t\t\t\t\t\t5. Exit\n\n");
        printf("\t\t\t\t\t\tChoose your option::==>  ");
        scanf("%d", &option);

        switch (option)
        {

        case 1:
        system("cls");
            fp = fopen("database.txt", "a");
            if (fp == NULL)
            {
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile Doesn't exist.\n");
                break;
            }
            add(fp);
            fclose(fp);
            break;

        case 2:
        system("cls");
            fp = fopen("database.txt", "r");
            if (fp == NULL)
            {
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile Doesn't exist.\n");;
                break;
            }
            display(fp);
            fclose(fp);
            break;

        case 3:
        system("cls");
            fp = fopen("database.txt", "r+");
            if (fp == NULL)
            {
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile not found.\n");
                break;
            }
            modify(fp);
            fclose(fp);
            break;

        case 4:
        system("cls");
            fp = fopen("database.txt", "r+");
            if (fp == NULL)
            {
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile not found.\n");
                break;
            }
            delete(fp);
            fclose(fp);
            break;

        case 5:
        system("cls");
            printf("\n\n\n\n\n\n\t\t\t\t\t\t   Exiting...");
            printf("\n\n\n");

            printf("\n\t\t\t\tThis portal is created by:--");
            printf("\n");
            printf("\n\t\t\t\t\t\t  Shahriar Ahmed Riaz");
            printf("\n\t\t\t\t\t\t  Akash Mondal");
            printf("\n\t\t\t\t\t\t  Tasnimul Alam");
            usleep(900000);
            printf("\n\n\n\t\t\t\t\t\t   Thanks for using...\n\n\n");
            return 0;

        default:
            printf("You've chosen the wrong option.\n");
            break;
        }
    }

    return 0;
}

void add(FILE *fp)
{
    system("cls");

    title();


    char answer = 'y';
    STUDENT stu;

    printf("\n\n\t\t\t\t\t<<<<<  Adding a student to database  >>>>>\n\n\n");

    while (answer == 'y' || answer == 'Y')
    {
        printf("\n\n\t\t\t\t\t");
        printf("Enter student name: ");
        getchar();
        fgets(stu.name, sizeof(stu.name), stdin);
        stu.name[strcspn(stu.name, "\n")] = '\0';

        printf("\t\t\t\t\t");
        printf("Enter father's name: ");
        fgets(stu.fname, sizeof(stu.fname), stdin);
        stu.fname[strcspn(stu.fname, "\n")] = '\0';

        printf("\t\t\t\t\t");
        printf("Enter Department: ");
        fgets(stu.dept, sizeof(stu.dept), stdin);
        stu.dept[strcspn(stu.dept, "\n")] = '\0';

        printf("\t\t\t\t\t");
        printf("Enter Student ID: ");
        scanf("%d", &stu.id);

        printf("\t\t\t\t\t");
        printf("Enter CGPA: ");
        scanf("%f", &stu.cgpa);

        fprintf(fp, "%s,%s,%s,%d,%.2f\n", stu.name, stu.fname, stu.dept, stu.id, stu.cgpa);

        printf("\t\t\t\t\t");
        printf("Do you want to add more students? (Y/N): ");
        getchar();
        answer = getchar();
    }

    printf("Information added successfully...");
    system("cls");
}

void display(FILE *fp)
{
    system("cls");


    STUDENT stu;

    rewind(fp);

    title();

    printf("\n\n\t\t\t<<<<<  Displaying students information from database  >>>>>\n\n\n");

    while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%f\n", stu.name, stu.fname, stu.dept, &stu.id, &stu.cgpa) == 5)
    {
        printf("\n\n\t\t\t\t\t");
        printf("Name: %s\n", stu.name);

        printf("\t\t\t\t\t");
        printf("Father's Name: %s\n", stu.fname);

        printf("\t\t\t\t\t");
        printf("Department: %s\n", stu.dept);

        printf("\t\t\t\t\t");
        printf("ID: %d\n", stu.id);

        printf("\t\t\t\t\t");
        printf("CGPA: %.2f\n\n", stu.cgpa);
    }

    printf("\t\t\t\t\t");
    printf("Information displayed successfully...");
}


void modify(FILE *fp)
{
    system("cls");
    title();
    printf("\n\n\t\t\t\t\t<<<<<  Modifying students' data from database  >>>>>\n\n\n");

    STUDENT stu;
    int id, found = 0;
    char modify_more = 'y';
    FILE *temp;

    while (modify_more == 'y' || modify_more == 'Y')
    {
        temp = fopen("temp.txt", "w");
        if (temp == NULL)
        {
            printf("\n\n\t\t\t\t\t");
            printf("Temporary file couldn't be created.\n");
            return;
        }

        printf("\t\t\t\t\t");
        printf("Enter the Student ID to modify: ");
        scanf("%d", &id);

        rewind(fp);
        found = 0;

        while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%f\n", stu.name, stu.fname, stu.dept, &stu.id, &stu.cgpa) == 5)
        {
            if (stu.id == id)
            {
                found = 1;
                printf("\n\n\t\t\t\t\t");
                printf("Enter new name: ");
                getchar();
                fgets(stu.name, sizeof(stu.name), stdin);
                stu.name[strcspn(stu.name, "\n")] = '\0';

                printf("\t\t\t\t\t");
                printf("Enter new father's name: ");
                fgets(stu.fname, sizeof(stu.fname), stdin);
                stu.fname[strcspn(stu.fname, "\n")] = '\0';

                printf("\t\t\t\t\t");
                printf("Enter new department: ");
                fgets(stu.dept, sizeof(stu.dept), stdin);
                stu.dept[strcspn(stu.dept, "\n")] = '\0';

                printf("\t\t\t\t\t");
                printf("Enter new CGPA: ");
                scanf("%f", &stu.cgpa);

                printf("\t\t\t\t\t");
                printf("Student information updated successfully.\n");
            }
            fprintf(temp, "%s,%s,%s,%d,%.2f\n", stu.name, stu.fname, stu.dept, stu.id, stu.cgpa);
        }

        fclose(fp);
        fclose(temp);

        remove("database.txt");
        rename("temp.txt", "database.txt");

        if (!found)
        {
            printf("\n\n\t\t\t\t\t");
            printf("Student ID not found.\n");
        }

        printf("\t\t\t\t\t");
        printf("Do you want to modify another student's information? (Y/N): ");
        getchar();
        modify_more = getchar();

        if (modify_more == 'y' || modify_more == 'Y')
        {
            fp = fopen("database.txt", "r+");
            if (fp == NULL)
            {
                system("cls");
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile not found.\n");
                return;
            }
        }
    }
    printf("\n\n\n\t\t\t");
    printf("Modified successfully...\n");

    system("cls");
}



void delete(FILE *fp)
{
    system("cls");
    title();

    printf("\n\n\t\t\t\t\t<<<<<  Deleting a student from database  >>>>>\n\n\n");

    STUDENT stu;
    int id, found = 0;
    char delete_more = 'y';
    FILE *temp;

    while (delete_more == 'y' || delete_more == 'Y')
    {
        temp = fopen("temp.txt", "w");
        if (temp == NULL)
        {
            printf("\n\n\t\t\t\t\t");
            printf("Temporary file couldn't be created.\n");
            return;
        }

        printf("\n\n\t\t\t\t\t");
        printf("Enter the Student ID to delete: ");
        scanf("%d", &id);

        rewind(fp);
        found = 0;

        while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%f\n", stu.name, stu.fname, stu.dept, &stu.id, &stu.cgpa) == 5)
        {
            if (stu.id == id)
            {
                found = 1;
                printf("\t\t\t\t\t");
                printf("Student with ID %d deleted successfully.\n", id);
                continue;
            }
            fprintf(temp, "%s,%s,%s,%d,%.2f\n", stu.name, stu.fname, stu.dept, stu.id, stu.cgpa);
        }

        fclose(fp);
        fclose(temp);

        remove("database.txt");
        rename("temp.txt", "database.txt");

        if (!found)
            printf("\n\n\t\t\t\t\t");
            printf("Student ID not found.\n");

        printf("\t\t\t\t\t");
        printf("Do you want to delete another student's information? (Y/N): ");
        getchar();
        delete_more = getchar();

        if (delete_more == 'y' || delete_more == 'Y')
        {
            fp = fopen("database.txt", "r+");
            if (fp == NULL)
            {
                system("cls");
                printf("\n\n\n\n\n\n\t\t\t\t\t\tFile not found.\n");
                return;
            }
        }
    }
    printf("\n\n\n\t\t\t");
    printf("Student deleted successfully.\n");

    usleep("300000");

    system("cls");
}

//Displaying Section
void title()
{
    system("COLOR 9f");
    printf("\n\n\t\t\t");
    printf("===================");
    printf(" UIU Student Portal ");
    printf("===================");
    printf("\n");
}

void printLine(char ch, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", ch);
    }
    printf("\n");
}


void loadingScreen()
{
    SetConsoleTitle("Student Portal | UIU");
    printf("\n\n\t\t\t");
    printf("=====================");
    printf("   UIU Student Portal   ");
    printf("=====================");
    printf("\n\n");

    printf(" \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *       Welcome      *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();

    system("cls");

    SetConsoleTitle("Student Portal | UIU");
    printf("\n\n\t\t\t");
    printf("=====================");
    printf("   UIU Student Portal   ");
    printf("=====================");
    printf("\n\n");

    printf("\n\n\n\n\n\n\n\t\t\t");
    printf("====================");
    printf("   -:Developed by:-   ");
    printf("====================");
    printf("\n\n\t\t\t");
    printf("*******   Quantum Encoders   *******");
    printf("\n\n\n\n\n\n\t\t\t\t\t   Press any key to Enter");
    getch();

    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\t");
    printf("====================");
    printf("   -:Loading, Please Wait:-   ");
    printf("====================");
    printf("\n\n\t\t\t");

    printf("\n\n\n");


    for (int i = 0; i < 5; i++) {
        printf("\r\t\t\t\t\t\t  [");
        for (int j = 0; j <= i; j++) {
            printf("#");
        }
        for (int j = i + 1; j < 5; j++) {
            printf(" ");
        }
        printf("] %d%%", (i + 1) * 20);
        fflush(stdout);
        usleep(300000);
    }
    printf("\n\n");
    system("cls");
}
