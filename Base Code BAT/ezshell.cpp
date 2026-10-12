#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <cwchar>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include "reading_input.cpp"

using namespace std;
namespace fs = std::filesystem;

WCHAR username[256];
string current_directory;
string home_directory;

// Display the available commands
void helpf() {
    cout << endl << "- - - - - - - - Commands - - - - - - - -" << endl;
    cout << "Delete - rm <filedirectory>" << endl;
    cout << "Copy and Paste - cp <filedirectory> <pastingdirectory>" << endl;
    cout << "Create File - cf <filename.extension>" << endl;
    cout << "Open File - op <filedirectory>" << endl;
    cout << "Display all files in the directory - list" << endl;
    cout << "Go to a directory - goto <directory>" << endl;
    cout << "Go to Desktop directory - DESKTOP" << endl;
    cout << "Go to Download directory - DOWNLOAD" << endl;
    cout << "Go to Document directory - DOCUMENT" << endl;
    cout << "Go to Picture directory - PICTURE" << endl;
    cout << "Go to Video directory - VIDEO" << endl;
    cout << "To exit program - EXIT" << endl;
    cout << endl << "- - - - - - - - - - - - - - - - - - - - -" << endl;
}

// Display the startup banner
void startingterminal() {
    DWORD username_len = 256;

    if (!GetUserNameW(username, &username_len)) {
        wcscpy_s(username, L"user");
    }

    cout << "Loading File Explorer CLI";
    for (int i = 0; i < 3; i++) {
        // Sleep(1000);
        cout << ".";
    }

    const char* profile = std::getenv("USERPROFILE");

    if (profile != nullptr) {
        fs::path homeDirectory(profile);
        home_directory = homeDirectory.string();
        current_directory = home_directory;
    } else {
        cerr << "Could not determine the home directory." << endl;
    }

    cout << endl
         << "Copyright (C) EzShell Terminal (EZT). All rights reserved."
         << endl;
    cout << endl << "A File Explorer CLI Project by ByteMe-Dot" << endl;
    wcout << endl << L"Welcome " << username << L" !" << endl;
}

// One terminal loop for all users.
// File operations are subject to normal Windows filesystem permissions.
void runTerminal() {
    cout << "Type help for commands" << endl;
    boolean running = true;
    while (running) {
    
        cout << fs::current_path() << ">";
        vector<string> words = read_input();
        for(int i=0;i<words.size();i++){      
            if (words[i] == "help") {
                helpf();
            } else if (words[i] == "EXIT") {
                running = false;
                break;
            } else if (words[i] == "remove") {
                fs::remove(words[i + 1]);
                i++; // Skip the next word as it's the file/directory to remove
                cout<<"File/Folder removed successfully."<<endl;  
            } else if (words[i] == "removeAll") {
                fs::remove_all(words[i + 1]);
                i++; // Skip the next word as it's the file/directory to remove
                cout<<"File/Folder removed successfully."<<endl;  
            } else if (words[i] == "whereami") {
                cout << fs::current_path() << endl;
            } else if (words[i] == "copy") {
                // TODO: Copy-and-paste function
            } else if (words[i] == "rename") {
                // TODO: Rename function
            } else if (words[i] == "open"){
                // TODO: Open function
            } else if (words[i] == "createDir") {
                fs::create_directory(words[i + 1]);
                cout<<"Directory created successfully."<<endl;
                i++; // Skip the next word as it's the directory to create
            } else if (words[i] == "list") {
                // TODO: Display all files in the current directory
            } else if (words[i] == "goto") {
                fs::current_path(words[i + 1]);
                i++; // Skip the next word as it's the directory to go to
            } else if (words[i] == "DESKTOP") {
                // TODO: Navigate to the Desktop directory
            } else if (words[i] == "DOWNLOAD") {
                // TODO: Navigate to the Downloads directory
            } else if (words[i] == "DOCUMENT") {
                // TODO: Navigate to the Documents directory
            } else if (words[i] == "PICTURE") {
                // TODO: Navigate to the Pictures directory
            } else if (words[i] == "VIDEO") {
                // TODO: Navigate to the Videos directory
            } else {
                cout << "'" << words[i]
                     << "' is not recognized as an internal or external command."
                     << endl;
            }
        }
    }
}

int main() {

    startingterminal();
    runTerminal();
    return 0;
}