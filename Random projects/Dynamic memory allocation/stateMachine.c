#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mallocAndSaveInfo();
void mainMenu();
void displayInfo();
void reAllocate();

typedef struct Info
{
    int age;
    char name[30];
    float weight;
}
Info;

Info* persons;

_Bool continueInfo = 1;
int mode;
int numOfPersons;
int newNumOfPersons;

int main()
{
    mallocAndSaveInfo();
    mainMenu();
    free(persons);
    return 0;
}

void mallocAndSaveInfo()
{
    printf("This program can save and display the info of *n* persons.\n");
    printf("Give the number of persons: \n");
    scanf("%d", &numOfPersons);

    persons = (Info*)malloc(numOfPersons * sizeof(Info));

    if(persons == NULL)
    {
        printf("Allocation failed.\n");
    }
    else
    {
        printf("Memory allocation succesfull.\n\n");
    }



    for(int i = 0; i < numOfPersons; i++)
    {
        printf("Give the name of the %d. person: \n", i+1);
        scanf("%s", persons[i].name);

        printf("Give the age of the %d. person: \n", i+1);
           scanf("%d", &persons[i].age);

        printf("Give the weight of the %d. person: \n", i+1);
           scanf("%f", &persons[i].weight);
    }

    printf("\n*Info saved*\n\n");
}

void displayInfo()
{
    while(continueInfo)
    {
        int number;
        printf("\nGive the number of a person to display info (0 -> main menu):\n");
        /*for(int i = 0; i < numOfPersons; i++)
        {
            printf("%d. %s\n", i + 1, persons[i].name);
        }*/
        scanf("%d", &number);

        if(number >= 1 && number <= numOfPersons)
        {
            printf("Name: %s, Age: %d, Weight: %.2f\n", persons[number - 1].name, persons[number - 1].age, persons[number - 1].weight);
        }
        else if(number == 0)
        {
            printf("Moving to main menu.\n\n");
            continueInfo = 0;
        }
        else
        {
            printf("Not available, try again.\n");
        }
    }
}

void mainMenu()
{
    while(1)
    {
        printf("Select mode: \n1 = display info \n2 = add more persons(reallocate) \n0 = quit\n");
        scanf("%d", &mode);

        if(mode == 1)
        {
            displayInfo();
            continueInfo = 1;
        }
        else if(mode == 2)
        {
            reAllocate();
        }
        else if(mode == 0)
        {
            printf("Thank you for using this program.\n");
            break;
        }
    }
}

void reAllocate()
{
    printf("\n*Lowering the amount of persons will result in lost data*\nCurrent amount: %d\n", numOfPersons);
    printf("Give the new number of persons: \n");
    scanf("%d", &newNumOfPersons);

    Info* newListPointer = (Info*)realloc(persons, newNumOfPersons * sizeof(Info));

    if(newListPointer == NULL)
    {
        printf("Memory reallocation failed.\n");
    }
    else
    {
        persons = newListPointer;
        printf("Memory reallocation succesfull. \nYou can now add more info.\n\n");

        for(int i = numOfPersons; i < newNumOfPersons; i++)
        {
            printf("Give the name of the %d. person: \n", i+1);
            scanf("%s", persons[i].name);

            printf("Give the age of the %d. person: \n", i+1);
               scanf("%d", &persons[i].age);

            printf("Give the weight of the %d. person: \n", i+1);
               scanf("%f", &persons[i].weight);
        }
        printf("\n*New info saved*\n\n");
        numOfPersons = newNumOfPersons;
    }
}
