#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoManager
{
public:
    struct Info
    {
        int age;
        string name;
        float weight;
    };

    int numOfPersons;

private:
    vector<Info> persons;   // Vector for dynamically handling the Info -struct

    /* This is a private function used in saveInfo() and addPersons() methods to avoid rewriting the same for() loop.*/

    void getInfo(int value)
    {
        for (int i = value; i < numOfPersons; i++)
        {
            cout << "\nGive the info of the " << i + 1 << ". person: \n";

            cout << "Name: ";
            getline(cin, persons[i].name);
            
            cout << "Age: ";
            while(!(cin >> persons[i].age))         //Input validation
            {
                cout << "Invalid age. Please enter a valid age: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Weight: ";
            while(!(cin >> persons[i].weight))      //Input validation
            {
                cout << "Invalid weight. Please enter a valid weight: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();
            cout << endl;
        }
    }

public:

    /*Method for gathering the initial data.*/

    void saveInfo()
    {
        cout << "This program can save the info of 'n' persons.\n\n";
        cout << "Give the desired number of persons: ";
        cin >> numOfPersons;
        cin.ignore();

        persons.resize(numOfPersons);

        getInfo(0);

        cout << "\nInfo saved\n\n";

    }

    /*Method for displaying the gathered data.*/

    void displayInfo()
    {
        while(true)
        {
            int number;
            cout << "\nGive the number of a person to display info (0 -> MainMenu): ";
            cin >> number;

            if (cin.fail())         //Input validation
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n*Invalid input, try again.*\n\n";
                continue;
            }
            cin.ignore();

            if (number >= 1 && number <= numOfPersons)
            {
                cout << "Name: " << persons[number - 1].name << endl;
                cout << "Age: " << persons[number - 1].age << endl;
                cout << "Weight: " << persons[number - 1].weight << "\n\n";

            }
            else if (number == 0)
            {
                cout << "Moving to main menu.\n\n";
                break;
            }
            else
            {
                cout << "\n*Not available, try again*\n\n";
            }
        }
    }

    /*Method for adding more persons to the list*/

    void addPersons()
    {
        int newNumOfPersons;
        int oldNumOfPersons = persons.size();                       // Save the current amount
        cout << "\nCurrent amount: " << persons.size() << "\n";
        cout << "Give the new number of persons: ";
        cin >> newNumOfPersons;
        cin.ignore();

        if (newNumOfPersons < oldNumOfPersons)
        {
            cout << "\n*Lowering the amount will result in lost data*\n";
            char confirm;
            cout << "Are you sure you want to continue? (y/n): ";
            cin >> confirm;
            if (confirm == 'n' || confirm == 'N')
            {
                return;
            }
        }

        persons.resize(newNumOfPersons);
        numOfPersons = newNumOfPersons;

        cout << "You can now add more persons.\n\n";

        getInfo(oldNumOfPersons);                                  /*Old amount is passed to the function
                                                                    to start the loop from the last filled index*/
        cout << "\n*New info saved*\n\n";
    }

    /*Method for deleting a specific person*/

    void deletePerson()
    {
        int indexToDelete;
        cout << "\nGive the number of the person to delete: ";
        cin >> indexToDelete;

        if (indexToDelete >= 1 && indexToDelete <= numOfPersons)
        {
            persons.erase(persons.begin() + indexToDelete -1);
            numOfPersons--;
            cout << "\n*Person deleted succesfully*\n\n";
        }
        else
        {
            cout << "\nInvalid person number.\n";
        }
    }

    /*Method for editing the info of a specific person*/

    void editPerson()
    {
        int indexToEdit;
        int choice;

        cout << "Enter the number of a person to edit: ";
        cin >> indexToEdit;
        cin.ignore();

        if (indexToEdit >= 1 && indexToEdit <= numOfPersons)
        {
            cout << "\nEditing info of " << persons[indexToEdit -1].name << ":\n";
            cout << "1. Name\n2. Age\n3. Weight\n\n";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
                case 1:
                    cout << "Enter new name: ";
                    getline(cin, persons[indexToEdit - 1].name);
                    break;
                case 2:
                    cout << "Enter new age: ";
                    while(!(cin >> persons[indexToEdit - 1].age))       //Input validation
                    {
                        cout << "Invalid age. Please enter a valid age: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cin.ignore();
                    break;
                case 3:
                    cout << "Enter new weight: ";
                    while(!(cin >> persons[indexToEdit - 1].weight))    //Input validation
                    {
                        cout << "Invalid weight. Please enter a valid weight: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cin.ignore();
                    break;
                default:
                    cout << "Invalid choice.\n";
                    return;
            }
            cout << "\nInfo updated succesfully.\n\n";
        }
        else
        {
            cout << "\n*Invalid person number.*\n\n";
        }
    }

    /*Method for navigating the program functions*/

    void mainMenu()
    {
        int mode;
        bool done = false;

        while(!done)
        {
            cout << "Select mode: \n0 = quit\n1 = display info \n2 = add more persons \n3 = delete a person \n4 = Edit persons info \n";
            cout << "Mode: ";
            cin >> mode;

            switch (mode)
            {
                case 0:
                    done = true;
                    cout << "\nThank you for using this program.\n\n";
                    break;
                case 1:
                    displayInfo();
                    break;
                case 2:
                    addPersons();
                    break;
                case 3:
                    deletePerson();
                    break;
                case 4:
                    editPerson();
                    break;
                default:
                    cout << "Not available.\n\n";

            }
        }
    }

};


int main()
{
    InfoManager manager1;

    manager1.saveInfo();        // Save the initial data
    
    manager1.mainMenu();        // Allow the user to give commands

    return 0;
}
