#include <string>
#include <direct.h>    
#include <windows.h>    // For listing files in Windows

using namespace std;

// Function declarations
void mainMenu();
void listFiles();
void createDirectory();
void changeDirectory();

int main() {
    mainMenu();
    return 0;
}

// Displays the main menu and routes user input
void mainMenu() {
    int choice;
    do {
        cout << "\n=== DIRECTORY MANAGEMENT SYSTEM ===\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear newline

        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Lists files in current directory based on user criteria
void listFiles() {
    int option;
    string pattern;

    cout << "\n[1] List All Files\n";
    cout << "[2] List Files by Extension (e.g. .txt)\n";
    cout << "[3] List Files by Pattern (e.g. data*.*)\n";
    cout << "Choose option: ";
    cin >> option;
    cin.ignore();

    WIN32_FIND_DATA file;
    HANDLE hSearch;
    string searchPattern;

    switch (option) {
        case 1:
            searchPattern = "*.*";
            break;
        case 2:
            cout << "Enter extension: ";
            getline(cin, pattern);
            searchPattern = "*" + pattern;
            break;
        case 3:
            cout << "Enter pattern: ";
            getline(cin, pattern);
            searchPattern = pattern;
            break;
        default:
            cout << "Invalid option.\n";
            return;
    }

    hSearch = FindFirstFile(searchPattern.c_str(), &file);
    if (hSearch != INVALID_HANDLE_VALUE) {
        do {
            cout << file.cFileName << endl;
        } while (FindNextFile(hSearch, &file));
        FindClose(hSearch);
    } else {
        cout << "No matching files found.\n";
    }
}

// Prompts user to create a new directory
void createDirectory() {
    string dirName;
    cout << "Enter directory name: ";
    getline(cin, dirName);

    if (_mkdir(dirName.c_str()) == 0) {
        cout << "Directory created.\n";
    } else {
        cout << "Error: Directory may already exist.\n";
    }
}

// Changes current working directory
void changeDirectory() {
    string path;
    cout << "Enter path to switch to: ";
    getline(cin, path);

    if (_chdir(path.c_str()) == 0) {
        char buffer[FILENAME_MAX];
        _getcwd(buffer, FILENAME_MAX);
        cout << "Directory changed to: " << buffer << "\n";
    } else {
        cout << "Failed to change directory. Check the path.\n";
    }
}