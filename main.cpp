#include <iostream>
#include <string>
#include <filesystem>  // Requires C++17

namespace fs = std::filesystem;
using namespace std;

// Function declarations
void mainMenu();
void listFiles();
void listAllFiles();
void listFilesByExtension();
void listFilesByPattern();
void createDirectory();
void changeDirectory();

// Entry point
int main() {
    mainMenu();
    return 0;
}

// Main menu loop
void mainMenu() {
    int choice;

    do {
        cout << "\n=== Directory Management System ===\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input

        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Submenu for listing files
void listFiles() {
    int option;
    cout << "\n--- List Files ---\n";
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension (e.g., .txt)\n";
    cout << "[3] List Files by Pattern (e.g., moha)\n";
    cout << "Enter option: ";
    cin >> option;
    cin.ignore();

    switch (option) {
        case 1: listAllFiles(); break;
        case 2: listFilesByExtension(); break;
        case 3: listFilesByPattern(); break;
        default: cout << "Invalid option.\n";
    }
}

// List all files in the current directory
void listAllFiles() {
    cout << "\nFiles in current directory:\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_regular_file(entry.status()))
            cout << " - " << entry.path().filename() << '\n';
    }
}

// List files with specific extension
void listFilesByExtension() {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    getline(cin, ext);

    cout << "\nFiles with extension " << ext << ":\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_regular_file(entry.status()) && entry.path().extension() == ext)
            cout << " - " << entry.path().filename() << '\n';
    }
}

// List files that match a pattern
void listFilesByPattern() {
    string pattern;
    cout << "Enter starting pattern (e.g., moha): ";
    getline(cin, pattern);

    cout << "\nFiles starting with \"" << pattern << "\":\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        string filename = entry.path().filename().string();
        if (fs::is_regular_file(entry.status()) && filename.rfind(pattern, 0) == 0)
            cout << " - " << filename << '\n';
    }
}

// Create a new directory if it doesn't exist
void createDirectory() {
    string dirName;
    cout << "Enter directory name to create: ";
    getline(cin, dirName);

    if (fs::exists(dirName)) {
        cout << "Error: Directory already exists.\n";
    } else {
        if (fs::create_directory(dirName))
            cout << "Directory \"" << dirName << "\" created successfully.\n";
        else
            cout << "Error creating directory.\n";
    }
}

// Change working directory
void changeDirectory() {
    string newPath;
    cout << "Enter new directory path: ";
    getline(cin, newPath);

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        fs::current_path(newPath);
        cout << "Successfully changed directory to: " << fs::current_path() << '\n';
    } else {
        cout << "Error: Directory does not exist.\n";
    }
}
