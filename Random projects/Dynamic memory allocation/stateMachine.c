#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void mallocAndSaveInfo();
void mainMenu();
void displayInfo();
void reAllocate();
void editPerson();
void deletePerson();

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
        getchar();
        fgets(persons[i].name, sizeof(persons[i].name), stdin);
        persons[i].name[strcspn(persons[i].name, "\n")] = '\0';

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
        int validNum = scanf("%d", &number);

        while (getchar() != '\n'){}

        if(validNum == 1 && number >= 1 && number <= numOfPersons)
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
        printf("Select mode: \n1 = display info \n2 = add more persons(reallocate) \n3 = delete a person \n4 = Edit persons info \n0 = quit\n");
        int valid = scanf("%d", &mode);
        while (getchar() != '\n'){}

        if (valid == 1)
        {
            if(mode == 1)
            {
                displayInfo();
                continueInfo = 1;
            }
            else if(mode == 2)
            {
                reAllocate();
            }
            else if (mode == 3)
            {
                deletePerson();
            }
            else if (mode == 4)
            {
                editPerson();
            }
            else if(mode == 0)
            {
                printf("Thank you for using this program.\n");
                break;
            }
        }
        else
        {
            printf("Not available, try again\n");
        }    
    }
}

void reAllocate()
{
    printf("Current amount: %d\n", numOfPersons);
    printf("Give the new number of persons: \n");
    scanf("%d", &newNumOfPersons);

    if (newNumOfPersons < numOfPersons) 
    {
        printf("\n*Lowering the amount of persons will result in lost data*\n");
        char confirm;
        printf("Are you sure you want to proceed? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm == 'n' || confirm == 'N') 
        {
            return; // Exit the function without reallocating
        }
    }

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
            while(getchar() != '\n'){};
            fgets(persons[i].name, sizeof(persons[i].name), stdin);
            persons[i].name[strcspn(persons[i].name, "\n")] = '\0';
            
            
            //scanf("%s", persons[i].name);

            printf("Give the age of the %d. person: \n", i+1);
               scanf("%d", &persons[i].age);

            printf("Give the weight of the %d. person: \n", i+1);
               scanf("%f", &persons[i].weight);
        }
        printf("\n*New info saved*\n\n");
        numOfPersons = newNumOfPersons;
    }
}

void deletePerson()
{
    int indexToDelete;
    printf("Give the number of the person to delete: ");
    scanf("%d", &indexToDelete);

    if(indexToDelete >= 1 && indexToDelete <= numOfPersons)
    {
        for(int i = indexToDelete - 1; i < numOfPersons; i++)
        {
            persons[i] = persons[i + 1];
        }

        Info* temporaryPointer = (Info*)realloc(persons, (--numOfPersons) * sizeof(Info));

        if(temporaryPointer != NULL)
        {
            persons = temporaryPointer;
            printf("\nPerson deleted succesfully.\n\n");
        }
        else
        {
            printf("\n*Failed to reallocate. Possible data loss occured.*\n");
            numOfPersons++;
        }
    }
    else
    {
        printf("\nInvalid person number.\n");
    }
}

void editPerson()
{
    int indexToEdit;
    int choise;

    printf("\nEnter the number of the person to edit: ");
    scanf("%d", &indexToEdit);

    if(indexToEdit >= 1 && indexToEdit <= numOfPersons)
    {
        printf("Editing info of %s:\n", persons[indexToEdit -1].name);
        printf("1. Name\n2. Age\n3. Weight\n");
        printf("Enter choise (1/2/3): ");
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                printf("Enter new name: ");
                while(getchar() != '\n'){};
                fgets(persons[indexToEdit - 1].name, sizeof(persons[indexToEdit - 1].name), stdin);
                persons[indexToEdit - 1].name[strcspn(persons[indexToEdit - 1].name, "\n")] = '\0';
                break;
            case 2:
                printf("Enter new age: ");
                scanf("%d", &persons[indexToEdit - 1].age);
                break;
            case 3:
                printf("Enter new weight: ");
                scanf("%f", &persons[indexToEdit - 1].weight);
                break;
            default:
                printf("Invalid choise.\n");
                return;
        }
        printf("\nInfo updated succesfully.\n\n");
    }
    else
    {
        printf("\n*Invalid person number.*\n");
    }
}

