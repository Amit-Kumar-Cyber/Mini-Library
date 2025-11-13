# 📚 Mini Library Management System

**C++ · Object-Oriented Programming · File Handling · Console Application**

---

## 📖 Project Overview

The **Mini Library Management System** is a console-based application developed using C++ (OOP) and file handling. It demonstrates clean modular programming, class-based design, persistent storage using text files, and reliable CLI interaction.

This system helps manage **Books**, **Members**, and **Issue/Return Records**, along with search functions and summary reporting.

### It is ideal for:

🔹 College mini-projects  
🔹 BCA / B.Tech OOP submissions  
🔹 Learning structured C++ development

---

## 🚀 Features

### 📘 Book Module

- Add new books
- Track total & available copies
- Search by title or author
- Auto-generated Book IDs

### 👤 Member Module

- Register new members
- Auto-generated Member IDs
- View a member's complete book-borrowing history

### 📦 Issue & Return Flow

- Issue books with validation:
  - Book exists
  - Member exists
  - Copies available
  - Prevent double issue to same member
- Return books & auto-update availability
- Store issue & return dates (YYYY-MM-DD format)

### 📊 Reports

- List all books
- List all issued books
- Member transaction history
- Summary report:
  - Total copies
  - Issued books count
  - Most frequently issued book

### 💾 File-Based Storage

Data is stored in simple `.txt` files using the pipe (`|`) separator.

| File Name | Description |
|-----------|-------------|
| `books.txt` | Stores book data |
| `members.txt` | Stores member data |
| `issues.txt` | Stores issue-return transactions |

**Example format:**
```
1|Clean Code|Robert C. Martin|3|2
```

---

## 🧱 Project Structure

```
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
```

---

## 🛠️ Technologies Used

- **C++17 Standard**
- **STL**: vectors, strings, file streams
- **fstream** for persistent storage
- **chrono** for date handling
- Clean OOP design with header/source separation

---

## ⚙️ Installation & Setup

### 🔧 Clone the Repository

```bash
git clone https://github.com/your-username/library-system.git
cd library-system
```

### 🏗️ Build the Project

```bash
g++ -std=c++17 -o mini_library main.cpp Book.cpp Member.cpp Issue.cpp Library.cpp utils.cpp
```

### ▶️ Run

```bash
./mini_library
```

**On Windows:**
```bash
.\mini_library.exe
```

---

## 🧪 Running Unit Tests

Tests provided for:

- 📘 Models
- 🧰 Utilities
- 🏛️ Library core logic

### Build Tests

```bash
g++ -std=c++17 -o test_models test_models.cpp Book.cpp Member.cpp Issue.cpp utils.cpp
g++ -std=c++17 -o test_utils test_utils.cpp utils.cpp
g++ -std=c++17 -o test_library test_library.cpp Book.cpp Member.cpp Issue.cpp Library.cpp utils.cpp
```

### Run Tests

```bash
./test_models
./test_utils
./test_library
```

---

## 📸 Screenshots (Optional)

You can add screenshots here later. For now, placeholders:

- **Main Menu**
- **Add Book**
- **Issuing a Book**

---

## 🔐 Known Limitations

- `|` cannot appear in title/inputs (no escaping implemented)
- Not suitable for multi-user or concurrent access
- Console-only UI
- Full database not implemented (text files only)

---

## 🌱 Future Enhancements

- JSON or SQLite storage
- Admin login & user roles
- Due dates and fine system
- Qt GUI or full web frontend
- File-locking or atomic writes for safety

---

## 👨‍💻 Contributors

| Role | Person |
|------|--------|
| Person A | Data Models & File I/O |
| Person B | Utilities & Input Validation |
| Person C | Core Logic & Rule Engine |
| Person D | UI, Integration, Packaging, Documentation |

---

## 📝 License

This project is under the **MIT License**.

You may use, modify, and distribute it freely.

---

## ⭐ Support the Project

If this project helped you, please give it a **Star ⭐** on GitHub!

It means a lot and encourages further work.

---

## 📚 Usage Guide

### Adding a Book

1. Select option `1` from the main menu
2. Enter book title (non-empty)
3. Enter author name
4. Enter number of copies (≥ 1)
5. Confirm the details
6. Book is saved with auto-generated ID

### Issuing a Book

1. Select option `8` from the main menu
2. Enter Book ID
3. Enter Member ID
4. Confirm the issue
5. System validates and creates issue record

### Returning a Book

1. Select option `9` from the main menu
2. Choose return method:
   - By Issue ID
   - By Book ID + Member ID
3. Confirm the return
4. System updates availability automatically

### Searching Books

- **By Title**: Option `4` - Case-insensitive substring search
- **By Author**: Option `5` - Case-insensitive substring search
- **By ID**: Option `6` - Direct ID lookup

### Viewing Reports

- **All Books**: Option `3` - Complete book catalog
- **Issued Books**: Option `10` - Currently issued books with member details
- **Member History**: Option `11` - Complete transaction history for a member
- **Summary**: Option `12` - Library statistics and most issued book

---

## 🐛 Troubleshooting

### Compilation Errors

If you encounter compilation errors:

1. Ensure you're using a C++17 compatible compiler
2. Check that all source files are in the same directory
3. Verify all header files are present

### File Not Found Errors

- Ensure `books.txt`, `members.txt`, and `issues.txt` exist (they will be created automatically on first run)
- Check file permissions in the project directory

### Date Function Errors

The date function is cross-platform compatible:
- Windows (MSVC): Uses `localtime_s`
- Windows (MinGW): Uses `std::localtime`
- Linux/macOS: Uses `localtime_r`

---

## 📞 Contact & Support

For issues, questions, or contributions, please open an issue on GitHub or contact the project maintainers.

---

**Happy Coding! 🎉**

