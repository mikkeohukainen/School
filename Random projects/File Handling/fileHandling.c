#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[30];
    int age;
}
studentInfo;

studentInfo students[5];

_Bool saveInfo();
_Bool createFile();
_Bool searchData();

int main()
{
    saveInfo();
    createFile();
    searchData();

return 0;
}

_Bool saveInfo()
{
    printf("\nThis program can save the info of 5 students and create a file.\n\n");

    
    for(int i = 0; i < 5; i ++)
    {
        printf("\nGive the name of the %d. student: ", i+1);
        scanf("%s", students[i].name);
        printf("Give the id of the %d. student: ", i+1);
        scanf("%d", &students[i].id);
        printf("Give the age of the %d. student: ", i+1);
        scanf("%d", &students[i].age);
    }

    for (int x = 0; x < 5; x ++)
    {
        printf("\nStudent number: %d, name: %s, id: %d and age: %d\n", x+1, students[x].name, students[x].id, students[x].age, x+1);
    }
}

_Bool createFile()
{
    int choise;
    printf("\n\nDo you want to save this data to a file?");
    printf("\nYes = 1 / No = 2: ");
    scanf("%d", &choise);

    if (choise == 2)
    {
        printf("Thank you for using this program.\n");
    }
    else if (choise == 1)
    {
        FILE *filePointer;
        filePointer = fopen("C:/qt/tehtavat/students_data.txt", "w");
        if (filePointer == NULL)
        {
            printf("Error when opening the file for writing.\n");
        }
        else
        {
            printf("\n*File succesfully opened.*\n");
        }
        for (int i = 0; i < 5; i ++)
        {
            fprintf(filePointer, "%d, %s, %d\n", students[i].id, students[i].name, students[i].age);
        }
        fclose(filePointer);
        printf("*File succesfully saved.*\n\n");
    }
    else
    {
        printf("Choise not available.\n");
    }
}

_Bool searchData()
{
    int givenID, idFromFile;
    char currentChar;
    char data[50];

    printf("Search for data of a specific student.\n\n");

    while(1)
    {
        printf("Give id (0 stops): ");
        scanf("%d", &givenID);

        if(givenID == 0)
        {
            printf("Thank you for using this program.\n");
            break;
        }

        else
        {
            FILE *filePointer;
            FILE *filePointer2;
            filePointer = fopen("C:/qt/tehtavat/students_data.txt", "r");
            filePointer2 = fopen("C:/qt/tehtavat/students_data.txt", "r");

            while((currentChar = fgetc(filePointer2)) != EOF)
            {
                fscanf(filePointer, "%d", &idFromFile);
                fgets(data, 50, filePointer);

                if (idFromFile == givenID)
                {
                    printf("ID: %d, DATA: %s\n\n", idFromFile, data);
                    break;
                }

                else if(feof(filePointer))
                {
                    printf("ID not found.\n");
                    break;
                }
            }

            fclose(filePointer);
            fclose(filePointer2);
        }
    }
}

