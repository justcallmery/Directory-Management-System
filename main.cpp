#include <iostream>
#include <string>
#include <filesystem> // C++17 library for cross-platform file system operations
namespace fs = std::filesystem; // Namespace alias for easier usage

using namespace std;

// Function declarations (modular approach)
void mainMenu();
void listFiles();
void listAllFiles();
void listFilesByExtension();
void listFilesByPattern();
void createDirectory();
void changeDirectory();

int main() {
    // Entry point of the program
    mainMenu(); // Call main menu to start the application
    return 0;
}

// Displays the main menu and handles user navigation
void mainMenu() {
    int choice;
    do {
        cout << "\n=== Directory Management System ===\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer after reading integer

        // Handle user selection
        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4); // Loop until user selects Exit
}

// Presents submenu to list files by different criteria
void listFiles() {
    int choice;
    cout << "\n-- List Files --\n";
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension\n";
    cout << "[3] List Files by Pattern\n";
    cout << "Select an option: ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    switch (choice) {
        case 1: listAllFiles(); break;
        case 2: listFilesByExtension(); break;
        case 3: listFilesByPattern(); break;
        default: cout << "Invalid option.\n";
    }
}

// Lists all regular files in the current directory
void listAllFiles() {
    cout << "\nFiles in current directory:\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_regular_file(entry.status()))
            cout << "  " << entry.path().filename() << '\n';
    }
}

// Lists files with a specific file extension (e.g., ".txt")
void listFilesByExtension() {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    getline(cin, ext);

    cout << "\nFiles with extension " << ext << ":\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_regular_file(entry) && entry.path().extension() == ext)
            cout << "  " << entry.path().filename() << '\n';
    }
}

// Lists files that match a starting pattern (e.g., "file" matches "file1.txt")
void listFilesByPattern() {
    string pattern;
    cout << "Enter filename pattern (e.g., moha): ";
    getline(cin, pattern);

    cout << "\nFiles matching pattern '" << pattern << "*':\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_regular_file(entry)) {
            string filename = entry.path().filename().string();
            if (filename.find(pattern) == 0) // Check if filename starts with pattern
                cout << "  " << filename << '\n';
        }
    }
}

// Creates a new directory in the current path
void createDirectory() {
    string dirName;
    cout << "Enter new directory name: ";
    getline(cin, dirName);

    fs::path newDir = fs::current_path() / dirName; // Combine current path with new folder name

    if (fs::exists(newDir)) {
        cout << "Error: Directory already exists.\n";
    } else {
        if (fs::create_directory(newDir)) {
            cout << "Directory '" << dirName << "' created successfully.\n";
        } else {
            cout << "Error: Failed to create directory.\n";
        }
    }
}

// Changes the working directory to a new location
void changeDirectory() {
    string path;
    cout << "Enter path to change directory: ";
    getline(cin, path);

    fs::path newPath = fs::path(path); // Convert string to path object

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        fs::current_path(newPath); // Change current working directory
        cout << "Changed current directory to: " << fs::current_path() << '\n';
    } else {
        cout << "Error: Directory does not exist.\n";
    }
}
