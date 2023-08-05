#include <iostream>
#include <fstream>
#include <string>
#include <vector>
const int RESET = 7;
const int RED = 12;
const int GREEN = 10;
const int YELLOW = 14;
const int BLUE = 9;
const int MAGENTA = 13;
const int CYAN = 11;
using namespace std;

// Platform-specific color handling for Windows
#ifdef _WIN32
#include <windows.h>
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#endif

/* Prototypes */
void ParseFile(string, vector<bool> &, vector<string> &, vector<string> &);
void ShowList(vector<bool>, vector<string>, vector<string>);
void ShowMenu();
void AddTask(vector<bool> &, vector<string> &, vector<string> &);
void ToggleTask(vector<bool> &);
void RemoveTask(vector<bool> &, vector<string> &, vector<string> &);
void SaveFile(string, vector<bool> &, vector<string> &, vector<string> &);

/* Global Variables */
ifstream fileReader;
ofstream fileWriter;

/* Start of Program */
int main()
{
    // Declare 3 vectors to hold our data.
    vector<bool> myChecks;
    vector<string> myTasks;
    vector<string> myDates;

    // Open the to do file and store the data to the vector.
    ParseFile("todo.txt", myChecks, myTasks, myDates);

    // Run the program until the user chooses to exit.
    while (true)
    {
        // Clear the console/terminal screen.
        if (system("CLS"))
            system("clear");

        // Set console color for header
        setConsoleColor(YELLOW);

        // Show list and menu.
        ShowList(myChecks, myTasks, myDates);
        ShowMenu();

        // Reset console color after header
        setConsoleColor(7);

        // Get user's choice.
        cout << "Choix : ";
        int choice;
        cin >> choice;

        // Check if the input was valid.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Veuillez saisir un chiffre valide.\n\n";
            continue;
        }
        cin.ignore(1000, '\n');
        cout << endl
             << endl;

        // Do things based on the user's choice.
        switch (choice)
        {
        case 1: // Ajouter une tâche.
            AddTask(myChecks, myTasks, myDates);
            break;
        case 2: // Cocher/décocher une tâche.
            ToggleTask(myChecks);
            break;
        case 3: // Supprimer une tâche.
            RemoveTask(myChecks, myTasks, myDates);
            break;
        case 4: // Quitter.
            return 0;
        default:
            cout << "Choix invalide. Veuillez choisir une option valide.\n";
        }

        // Save to file after we're done with the user's action.
        SaveFile("todo.txt", myChecks, myTasks, myDates);
    }
}

void ParseFile(string fileName,
               vector<bool> &checks,
               vector<string> &tasks,
               vector<string> &dates)
{
    // Open the file.
    fileReader.open(fileName);

    // If the file does not exist, create a new one.
    if (!fileReader)
    {
        ofstream newFile(fileName);
        if (!newFile)
        {
            cout << "Erreur lors de la création du fichier " << fileName << endl;
            exit(1);
        }
        newFile.close();
    }
    else
    {
        // Iterate through each line from the file.
        string line;
        while (getline(fileReader, line))
        {
            // Declare 3 variables to hold our data.
            string check = line.substr(0, 1);
            string task = line.substr(4, line.length());
            string date = task.substr(task.find("| ") + 2, task.length());
            task = task.substr(0, task.find("|"));

            // Add the data to the vectors.
            if (check == "0")
            {
                checks.push_back(false);
            }
            else
            {
                checks.push_back(true);
            }
            tasks.push_back(task);
            dates.push_back(date);
        }
    }

    // Close the file.
    fileReader.close();
}

void ShowList(vector<bool> checks,
              vector<string> tasks,
              vector<string> dates)
{
    for (int i = 0; i < checks.size(); i++)
    {
        // Output number so the user can easily select tasks.
        cout << i + 1 << ". ";

        // Output the check mark with colors.
        if (checks[i] == false)
        {
            setConsoleColor(RED);
            cout << "[ ] ";
        }
        else
        {
            setConsoleColor(GREEN);
            cout << "[x] ";
        }

        // Output the task description in blue.
        setConsoleColor(BLUE);
        cout << tasks[i] << RESET << endl;

        // Output the task date in magenta.
        setConsoleColor(MAGENTA);
        cout << "       " << dates[i] << RESET << endl
             << endl;
    }
}

void ShowMenu()
{
    cout << "Menu:" << endl
         << "1. Ajouter une tache" << endl
         << "2. Cocher/decocher une tache" << endl
         << "3. Supprimer une tache" << endl
         << "4. Quitter" << endl;
}

void AddTask(vector<bool> &checks,
             vector<string> &tasks,
             vector<string> &dates)
{
    // Print a header.
    cout << "Ajouter une tache" << endl
         << "=================" << endl;

    // Set console color for user input
    setConsoleColor(CYAN);

    // Get task description from the user.
    cout << "Description : ";
    string task;
    getline(cin, task);

    // Get task date from the user.
    cout << "Date : ";
    string date;
    getline(cin, date);

    // Reset console color after user input
    setConsoleColor(7);

    // Store data to our vectors.
    checks.push_back(false); // By default, a new task is unchecked.
    tasks.push_back(task);
    dates.push_back(date);
}

void ToggleTask(vector<bool> &checks)
{
    // Print a header.
    cout << "Cocher/Decocher une tache" << endl
         << "=========================" << endl;

    // Get the task number.
    cout << "Numero : ";
    int num;
    cin >> num;

    // Check if the input was valid.
    if (cin.fail() || num <= 0 || num > checks.size())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Numero de tache invalide.\n";
        return;
    }
    cin.ignore(1000, '\n');

    // Flip the boolean of the check status.
    checks[num - 1] = !checks[num - 1];
}

void RemoveTask(vector<bool> &checks,
                vector<string> &tasks,
                vector<string> &dates)
{
    // Print a header.
    cout << "Supprimer une tache" << endl
         << "===================" << endl;

    // Get the task number.
    cout << "Numero : ";
    int num;
    cin >> num;

    // Check if the input was valid.
    if (cin.fail() || num <= 0 || num > checks.size())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Numero de tache invalide.\n";
        return;
    }
    cin.ignore(1000, '\n');

    // Remove the task from the vectors.
    checks.erase(checks.begin() + num - 1);
    tasks.erase(tasks.begin() + num - 1);
    dates.erase(dates.begin() + num - 1);
}

void SaveFile(string fileName,
              vector<bool> &checks,
              vector<string> &tasks,
              vector<string> &dates)
{
    // Open the file.
    fileWriter.open(fileName);

    // Write the vectors to the file.
    for (int i = 0; i < checks.size(); i++)
    {
        fileWriter << (checks[i] ? "1" : "0") << " | " << tasks[i] << " | " << dates[i] << endl;
    }

    // Close the file.
    fileWriter.close();
}
