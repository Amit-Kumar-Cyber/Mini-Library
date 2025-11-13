#📚 Mini Library Management System
C++ · Object-Oriented Programming · File Handling · Console Application








📖 Project Overview

The Mini Library Management System is a lightweight, console-based application built using C++ (OOP principles) and text-based file storage.
It provides essential library operations such as:

Adding and managing Books

Registering Members

Issuing and Returning books

Searching for books

Generating reports

Data persistence using .txt files

Fully modular architecture with unit tests

This project is ideal for college mini-projects, BCA/B.Tech submissions, OOP practice, and learning structured C++ application development.

🧩 Features
📘 Book Management

Add new books

Track total & available copies

Search by title or author

Auto-generated Book IDs

👤 Member Management

Add new members

Auto-generated Member IDs

View individual borrowing history

📦 Issue & Return Module

Issue books with validation:

Book exists

Member exists

Copies available

Prevent duplicate outstanding issue

Return books and auto-update availability

Store issue/return dates (YYYY-MM-DD)

📊 Reports

List all books

List issued books

Member transaction history

Summary report:

Total copies

Currently issued

Most issued book

💾 Persistent Storage

The system uses three text files:

File	Data Stored
books.txt	Book records
members.txt	Member records
issues.txt	Issue/return history

Format: pipe-separated (|) fields
Example:

1|Clean Code|Robert C. Martin|3|2

🧱 Project Structure
📁 LibrarySystem/
│
├── src/
│   ├── Book.h
│   ├── Book.cpp
│   ├── Member.h
│   ├── Member.cpp
│   ├── Issue.h
│   ├── Issue.cpp
│   ├── Library.h
│   ├── Library.cpp
│   ├── utils.h
│   ├── utils.cpp
│   └── main.cpp
│
├── data/
│   ├── books.txt
│   ├── members.txt
│   └── issues.txt
│
├── tests/
│   ├── test_models.cpp
│   ├── test_utils.cpp
│   └── test_library.cpp
│
├── build.sh
├── run_tests.sh
├── package.sh
└── README.md

🛠️ Technologies Used

C++17

STL: vector, string, fstream, chrono

Modular OOP design

File handling (fstream)

Custom input handling utilities

⚙️ Installation & Setup
🔧 1. Clone the Repository
git clone https://github.com/your-username/library-system.git
cd library-system

🏗️ 2. Build the Project
g++ -std=c++17 -o mini_library main.cpp Book.cpp Member.cpp Issue.cpp Library.cpp utils.cpp

▶️ 3. Run the Application
./mini_library

🧪 Running Unit Tests

Unit tests exist for:

🧩 Models

🧰 Utilities

📦 Library core logic

Build Tests
g++ -std=c++17 -o test_models test_models.cpp Book.cpp Member.cpp Issue.cpp utils.cpp
g++ -std=c++17 -o test_utils test_utils.cpp utils.cpp
g++ -std=c++17 -o test_library test_library.cpp Book.cpp Member.cpp Issue.cpp Library.cpp utils.cpp

Run Tests
./test_models
./test_utils
./test_library

📸 Screenshots (Optional – add later)

(You may replace these with real screenshots)

📜 Main Menu

📘 Add Book

📦 Issue Book

🔐 Limitations

No escaping for | character in user input

Not meant for multi-user or concurrent use

CLI-based only (no GUI)

Not optimized for large datasets

🚀 Future Enhancements

Switch to JSON or SQLite database

Add Due Dates & Fine Calculation

Add Admin Login & Roles

Create a GUI using Qt or a Web App using Python Flask/FastAPI

Add unit tests for console I/O

👨‍💻 Contributors
Role	Member
Person A	Data Models & I/O
Person B	Utilities & Input Validation
Person C	Core Logic & Library Manager
Person D	UI, Integration, Packaging & Documentation
📝 License

This project is licensed under the MIT License — feel free to use, modify, and distribute.

⭐ Show Your Support

If you like this project, consider giving it a star ⭐ on GitHub — it motivates us to build more!
