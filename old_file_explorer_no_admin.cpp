#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <cwchar>

using namespace std;
namespace fs = std::filesystem;

WCHAR username[256];

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
        Sleep(1000);
        cout << ".";
    }

    cout << endl
         << "Copyright (C) ByteArch Terminal (BAT). All rights reserved."
         << endl;
    cout << endl << "A File Explorer CLI Project by ByteArch!" << endl;
    wcout << endl << L"Welcome " << username << L" !" << endl;
}

// One terminal loop for all users.
// File operations are subject to normal Windows filesystem permissions.
void runTerminal() {
    string input;

    cout << "Type !help for commands" << endl;

    while (true) {
        wcout << L"BAT C:/Users/" << username << L">> ";

        if (!getline(cin, input)) {
            break; // Handle end-of-input cleanly.
        }

        if (input == "!help") {
            helpf();
        } else if (input == "EXIT") {
            break;
        } else if (input == "rm") {
            // TODO: Delete function
        } else if (input == "cp") {
            // TODO: Copy-and-paste function
        } else if (input == "op") {
            // TODO: Open function
        } else if (input == "cf") {
            // TODO: Create-file function
        } else if (input == "list") {
            // TODO: Display all files in the current directory
        } else if (input == "goto") {
            // TODO: Change to a directory (goto <directory>)
        } else if (input == "DESKTOP") {
            // TODO: Navigate to the Desktop directory
        } else if (input == "DOWNLOAD") {
            // TODO: Navigate to the Downloads directory
        } else if (input == "DOCUMENT") {
            // TODO: Navigate to the Documents directory
        } else if (input == "PICTURE") {
            // TODO: Navigate to the Pictures directory
        } else if (input == "VIDEO") {
            // TODO: Navigate to the Videos directory
        } else {
            cout << "'" << input
                 << "' is not recognized as an internal or external command."
                 << endl;
        }
    }
}

int main() {
    startingterminal();
    runTerminal();
    return 0;
}
