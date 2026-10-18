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
#include <shlobj.h>

using namespace std;
namespace fs = std::filesystem;

WCHAR username[256];
string current_directory;
string home_directory;

// Display the available commands
void helpf() {
    cout << endl << "- - - - - - - - Commands - - - - - - - -" << endl;
    cout <<"Navigation:" << endl;
    cout<<"\tgoto <directory>             Navigate to a directory" << endl;
    cout<<"\tgoback                       Go to the parent directory" << endl;
    cout<<"\twhereami                     Show the current directory" << endl;
    cout<<"\tDESKTOP                      Navigate to Desktop" << endl;
    cout<<"\tDOCUMENT                     Navigate to Documents" << endl;
    cout<<"\tDOWNLOAD                     Navigate to Downloads" << endl;
    cout<<"\tPICTURE                      Navigate to Pictures" << endl;
    cout<<"\tVIDEO                        Navigate to Videos" << endl;

    cout<<"File operations:" << endl;
    cout<<"\tcopyto <source> <destination> Copy a file or directory" << endl;
    cout<<"\trename <old> <new>            Rename a file or directory" << endl;
    cout<<"\topen <path>                   Open a file" << endl;
    cout<<"\tremove <path>                 Remove a file or empty directory" << endl;
    cout<<"\tremoveAll <path>              Remove a directory recursively" << endl;
    cout<<"\tcreateDir <name>              Create a directory" << endl;

    cout<<"Other:" << endl;
    cout<<"\twhoami                        Show the Windows username" << endl;
    cout<<"\thelp                          Show commands" << endl;
    cout<<"\tEXIT                          Exit EzShell" << endl;
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


bool goToKnownFolder(REFKNOWNFOLDERID folderId) {
    PWSTR rawPath = nullptr;

    HRESULT result = SHGetKnownFolderPath(
        folderId, 0, nullptr, &rawPath
    );

    if (FAILED(result)) {
        cout << "Could not locate the folder.\n";
        return false;
    }

    fs::path folderPath(rawPath);
    CoTaskMemFree(rawPath);

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        cout << "Folder does not exist: "
             << folderPath.string() << '\n';
        return false;
    }

    try {
        fs::current_path(folderPath);
        cout << "Moved to: " << fs::current_path().string() << '\n';
        return true;
    } catch (const fs::filesystem_error& e) {
        cout << "Navigation failed: " << e.what() << '\n';
        return false;
    }
}


// One terminal loop for all users.
// File operations are subject to normal Windows filesystem permissions.
void runTerminal() {
    cout << "Type help for commands\n";
    bool running = true;

    while (running) {
        cout << fs::current_path().string() << "> ";

        vector<string> words = read_input();

        if (words.empty()) {
            continue;
        }

        const string& command = words[0];

        if (command == "help") {
            helpf();
        }
        else if (command == "EXIT") {
            running = false;
        }
        else if (command == "whoami") {
            wcout << L"User: " << username << L'\n';
        }
        else if (command == "whereami") {
            cout << fs::current_path().string() << '\n';
        }
        else if (command == "goback") {
            fs::path current = fs::current_path();
            fs::path parent = current.parent_path();

            if (parent.empty() || parent == current) {
                cout << "Already at the root directory.\n";
            } else {
                fs::current_path(parent);
                cout << "Moved to: " << fs::current_path().string() << '\n';
            }
        }
        else if (command == "copyto") {
            if (words.size() < 3) {
                cout << "Usage: copyto <source> <destination>\n";
            } else {
                fs::path source = words[1];
                fs::path destination = words[2];

                try {
                     if (!fs::exists(source)) {
                        cout << "Source does not exist.\n";
                    } else if (!fs::is_directory(destination)) {
                        cout << "Destination must be an existing directory.\n";
                    } else {
                        fs::path target = destination / source.filename();

                        fs::copy(
                            source,
                            target,
                            fs::copy_options::recursive |
                            fs::copy_options::overwrite_existing
                        );

                        cout << "Copied successfully to: "
                            << target.string() << '\n';
                    }
                } catch (const fs::filesystem_error& e) {
                    cout << "Copy failed: " << e.what() << '\n';
                }
            }
        }
        else if (command == "rename") {
            if (words.size() < 3) {
                cout << "Usage: rename <old_path> <new_name>\n";
            } else {
                fs::path oldPath = words[1];
                fs::path newPath = oldPath.parent_path() / words[2];

                try {
                    if (!fs::exists(oldPath)) {
                        cout << "The source does not exist.\n";
                    } else if (fs::exists(newPath)) {
                        cout << "A file or directory with that name already exists.\n";
                    } else {
                        fs::rename(oldPath, newPath);
                        cout << "Renamed successfully.\n";
                    }
                } catch (const fs::filesystem_error& e) {
                    cout << "Rename failed: " << e.what() << '\n';
                }
            }
        }
        else if (command == "open") {
            if (words.size() < 2) {
                cout << "Usage: open <file_path>\n";
            } else {
                fs::path filePath = words[1];

                if (!fs::exists(filePath)) {
                    cout << "File does not exist.\n";
                } else {
                    HINSTANCE result = ShellExecuteA(
                        nullptr,
                        "open",
                        filePath.string().c_str(),
                        nullptr,
                        nullptr,
                        SW_SHOWNORMAL
                    );

                    if (reinterpret_cast<INT_PTR>(result) <= 32) {
                        cout << "Could not open the file.\n";
                    }
                }
            }
        }
        else if (command == "goto") {
            if (words.size() < 2) {
                cout << "Usage: goto <directory>\n";
            } else {
                try {
                    fs::current_path(words[1]);
                } catch (const fs::filesystem_error& e) {
                    cout << "Navigation failed: "
                         << e.what() << '\n';
                }
            }
        }
        else if (command == "DESKTOP") {
            goToKnownFolder(FOLDERID_Desktop);
        }
        else if (command == "DOWNLOAD") {
            goToKnownFolder(FOLDERID_Downloads);
        }
        else if (command == "DOCUMENT") {
            goToKnownFolder(FOLDERID_Documents);
        }
        else if (command == "PICTURE") {
            goToKnownFolder(FOLDERID_Pictures);
        }
        else if (command == "VIDEO") {
            goToKnownFolder(FOLDERID_Videos);
        }
        else {
            cout << "'" << command
                 << "' is not recognized as a command.\n";
        }
    }
}

int main() {

    startingterminal();
    runTerminal();
    return 0;
}