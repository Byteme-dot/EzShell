# EzShell

### A lightweight, custom command-line file explorer for Windows.

EzShell is a C++ project that provides a custom command interface for navigating directories and managing files on Windows. Instead of relying entirely on traditional shell commands, EzShell introduces its own simple commands for common file-system operations.

Built using **C++**, **Windows API**, and **`std::filesystem`**, EzShell is a personal project focused on learning systems programming, command parsing, and Windows file-system operations.

---

## Features

- **Custom Command Parser** — Parses user input into commands and arguments.
- **Directory Navigation** — Move between directories using simple, custom commands.
- **Quick Folder Access** — Jump directly to common Windows folders such as Desktop, Documents, Downloads, Pictures, and Videos.
- **File Management** — Copy files and directories, rename items, and open files using their default Windows applications.
- **Directory Listing** — View files, folders, and file sizes in the current directory.
- **User Information** — Display the current Windows username and working directory.
- **Error Handling** — Handles filesystem errors in several operations.
- **Windows Integration** — Uses Windows APIs to retrieve user information and locate known folders.

## Commands

| Command | Description |
|---|---|
| `help` | Display available commands |
| `EXIT` | Exit EzShell |
| `whoami` | Display the Windows username |
| `whereami` | Display the current working directory |
| `goto <directory>` | Navigate to a specified directory |
| `goback` | Navigate to the parent directory |
| `HOME` | Return to the user's home directory |
| `DESKTOP` | Navigate to Desktop |
| `DOCUMENT` | Navigate to Documents |
| `DOWNLOAD` | Navigate to Downloads |
| `PICTURE` | Navigate to Pictures |
| `VIDEO` | Navigate to Videos |
| `list` | List files and directories |
| `copyto <source> <destination>` | Copy a file or directory |
| `rename <old> <new>` | Rename a file or directory |
| `open <path>` | Open a file with its default application |

> **Note:** The current parser does not yet fully support quoted paths containing spaces. Some filesystem operations and navigation commands may also require further error-handling improvements.

## Tech Stack

- **Language:** C++
- **Filesystem Operations:** C++ `std::filesystem`
- **Platform Integration:** Windows API
- **Build Toolchain:** GCC / MinGW-w64
- **Development Environment:** Visual Studio Code

## Getting Started

### Prerequisites

- Windows
- GCC / MinGW-w64 with C++17 support
- Visual Studio Code or another C++ development environment

### Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/EzShell.git
cd EzShell
```

Replace `YOUR_USERNAME` with your GitHub username.

### Compile the project

If you're using MinGW-w64, compile the main source file with the required Windows libraries:

```bash
g++ ezshell.cpp -o ezshell.exe -lshell32 -lole32 -luuid
```

Run the executable:

```powershell
.\ezshell.exe
```

**Build note:** The current source includes `reading_input.cpp` directly. If you later separate it into a header and source file, update the compilation command to compile both `.cpp` files and remove the direct `.cpp` include.

## Project Structure

The project currently contains the terminal implementation and a separate input-parsing implementation.

```text
EzShell/
├── .metadata/
├── .vscode/
├── Base Code BAT/       # Original project code
├── ezshell.cpp          # Main application and command dispatcher
├── ezshell.exe          # Compiled Windows executable
├── reading_input.cpp    # Command input and parsing
├── reading_input.h      # Input parser declarations
└── README.md            # Project documentation
```

*The directory layout above is illustrative; adjust it to match the actual repository structure.*

## Roadmap

Planned improvements include:

- [ ] Support quoted paths and arguments containing spaces.
- [ ] Improve filesystem error handling across all commands.
- [ ] Refine file and directory creation and deletion commands.
- [ ] Improve directory-listing output and readability.
- [ ] Separate input parsing into a header and source file.
- [ ] Improve command consistency and usability.

## Why EzShell?

EzShell started as a file-explorer utility and evolved into a project for exploring how command-line interfaces work. By combining a custom parser with C++ filesystem operations and Windows APIs, the project provides a practical way to learn about command dispatching, path handling, error management, and operating-system integration.

## Contributing

Suggestions, bug reports, and improvements are welcome. Feel free to explore the code, report issues, or propose enhancements.

## License

A license has not yet been specified. Add a license file before distributing the project under an open-source license.

---

**EzShell** — Simple commands. Direct navigation. Your files, your way.
