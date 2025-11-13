// Library manager implementation: file load/save and core operations plus reports (simple English).
// Loads CSV files at start, saves after modifications, performs validations and case-insensitive search (technical).

#include "Library.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

// Constructor sets filenames (simple English).
// Stores file paths for persistent storage actions (technical).
Library::Library(const std::string &bfile, const std::string &mfile, const std::string &ifile)
    : books_file(bfile), members_file(mfile), issues_file(ifile) {}

// Load books, members and issues from disk into memory (simple English).
// Each file is parsed line-by-line to corresponding objects; missing files are ignored (technical).
void Library::load_all() {
    books.clear();
    members.clear();
    issues.clear();

    std::ifstream bf(books_file);
    if (bf) {
        std::string line;
        while (std::getline(bf, line)) {
            if (trim(line).empty()) continue;
            books.push_back(Book::from_csv(line));
        }
    }
    std::ifstream mf(members_file);
    if (mf) {
        std::string line;
        while (std::getline(mf, line)) {
            if (trim(line).empty()) continue;
            members.push_back(Member::from_csv(line));
        }
    }
    std::ifstream inf(issues_file);
    if (inf) {
        std::string line;
        while (std::getline(inf, line)) {
            if (trim(line).empty()) continue;
            issues.push_back(IssueRecord::from_csv(line));
        }
    }
}

// Save all vectors to their files (simple English).
// Overwrites files; for small projects this is acceptable (technical).
void Library::save_all() {
    std::ofstream bf(books_file, std::ios::trunc);
    for (const auto &b : books) bf << b.to_csv() << '\n';

    std::ofstream mf(members_file, std::ios::trunc);
    for (const auto &m : members) mf << m.to_csv() << '\n';

    std::ofstream inf(issues_file, std::ios::trunc);
    for (const auto &ir : issues) inf << ir.to_csv() << '\n';
}

// ID helpers compute next ID based on existing vector contents (simple English).
// Returns 1+max(existing ids) or 1 when none exist; O(n) scans (technical).
int Library::next_book_id() const {
    int mx = 0;
    for (const auto &b : books) if (b.id > mx) mx = b.id;
    return mx + 1;
}
int Library::next_member_id() const {
    int mx = 0;
    for (const auto &m : members) if (m.id > mx) mx = m.id;
    return mx + 1;
}
int Library::next_issue_id() const {
    int mx = 0;
    for (const auto &i : issues) if (i.id > mx) mx = i.id;
    return mx + 1;
}

// Add a book in-memory and persist immediately (simple English).
// Pushes into books vector and calls save_all (technical).
void Library::add_book(const Book &b) {
    books.push_back(b);
    save_all();
}

// Add a member in-memory and persist immediately (simple English).
// Similar to add_book, pushes into members and persists (technical).
void Library::add_member(const Member &m) {
    members.push_back(m);
    save_all();
}

// Find book pointer by id or return nullptr (simple English).
// Linear search across books vector (technical).
Book* Library::find_book_by_id(int id) {
    for (auto &b : books) if (b.id == id) return &b;
    return nullptr;
}

// Find member pointer by id or return nullptr (simple English).
// Linear search across members vector (technical).
Member* Library::find_member_by_id(int id) {
    for (auto &m : members) if (m.id == id) return &m;
    return nullptr;
}

// Case-insensitive search books by title substring (simple English).
// Uses helper contains_ci for lowercase find and returns pointers to matches (technical).
std::vector<Book*> Library::search_books_by_title(const std::string &q) {
    std::vector<Book*> res;
    for (auto &b : books) {
        if (contains_ci(b.title, q)) res.push_back(&b);
    }
    return res;
}

// Case-insensitive search books by author substring (simple English).
// Uses contains_ci helper (technical).
std::vector<Book*> Library::search_books_by_author(const std::string &q) {
    std::vector<Book*> res;
    for (auto &b : books) {
        if (contains_ci(b.author, q)) res.push_back(&b);
    }
    return res;
}

// Issue a book: enhanced checks to prevent duplicate outstanding issue by same member for same book (simple English).
// Validates existence of book and member, availability, and then records issue with current date (technical).
bool Library::issue_book(int book_id, int member_id, std::string &msg) {
    Book* b = find_book_by_id(book_id);
    if (!b) {
        msg = "Book not found";
        return false;
    }
    Member* m = find_member_by_id(member_id);
    if (!m) {
        msg = "Member not found";
        return false;
    }
    // Prevent same member from issuing same book twice without returning
    for (const auto &ir : issues) {
        if (ir.book_id == book_id && ir.member_id == member_id && !ir.is_returned()) {
            msg = "Member already has this book issued (Issue ID: " + std::to_string(ir.id) + ")";
            return false;
        }
    }
    if (b->available_copies <= 0) {
        msg = "No copies available";
        return false;
    }
    int nid = next_issue_id();
    IssueRecord ir(nid, book_id, member_id, today_date());
    issues.push_back(ir);
    b->available_copies -= 1;
    save_all();
    msg = "Book issued successfully, Issue ID: " + std::to_string(nid);
    return true;
}

// Return a book: mark issue's return_date and increment available copies (simple English).
// Finds issue by id, checks not already returned, sets return_date and updates book copies, persists (technical).
bool Library::return_book(int issue_id, std::string &msg) {
    for (auto &ir : issues) {
        if (ir.id == issue_id) {
            if (ir.is_returned()) {
                msg = "This issue is already returned";
                return false;
            }
            Book* b = find_book_by_id(ir.book_id);
            if (!b) {
                msg = "Associated book record missing";
                return false;
            }
            ir.return_date = today_date();
            b->available_copies += 1;
            save_all();
            msg = "Book returned successfully";
            return true;
        }
    }
    msg = "Issue record not found";
    return false;
}

// Print all books in a readable table to stdout (simple English).
// Outputs id, title, author, total and available copies (technical).
void Library::list_all_books() const {
    std::cout << "ID | Title | Author | Total | Available\n";
    std::cout << "---------------------------------------\n";
    for (const auto &b : books) {
        std::cout << b.id << " | " << b.title << " | " << b.author << " | "
                  << b.total_copies << " | " << b.available_copies << '\n';
    }
}

// Print currently issued books with member names and dates (simple English).
// Iterates issues where return_date empty and prints joined info (technical).
void Library::list_issued_books() const {
    std::cout << "IssueID | BookID | BookTitle | MemberID | MemberName | IssueDate\n";
    std::cout << "---------------------------------------------------------------\n";
    for (const auto &ir : issues) {
        if (!ir.is_returned()) {
            const Book* b = nullptr;
            const Member* m = nullptr;
            for (const auto &bb : books) if (bb.id == ir.book_id) { b = &bb; break; }
            for (const auto &mm : members) if (mm.id == ir.member_id) { m = &mm; break; }
            std::string btitle = b ? b->title : "(missing)";
            std::string mname = m ? m->name : "(missing)";
            std::cout << ir.id << " | " << ir.book_id << " | " << btitle << " | "
                      << ir.member_id << " | " << mname << " | " << ir.issue_date << '\n';
        }
    }
}

// List all issues for a given member (simple English).
// Prints both returned and not-returned records for the member (technical).
void Library::list_member_history(int member_id) const {
    std::cout << "IssueID | BookID | BookTitle | IssueDate | ReturnDate\n";
    std::cout << "----------------------------------------------------\n";
    for (const auto &ir : issues) {
        if (ir.member_id == member_id) {
            const Book* b = nullptr;
            for (const auto &bb : books) if (bb.id == ir.book_id) { b = &bb; break; }
            std::string btitle = b ? b->title : "(missing)";
            std::cout << ir.id << " | " << ir.book_id << " | " << btitle << " | "
                      << ir.issue_date << " | " << (ir.return_date.empty() ? "-" : ir.return_date) << '\n';
        }
    }
}

// Check availability by book id (simple English).
// Returns true if available and sets msg to readable status (technical).
bool Library::check_availability_by_id(int book_id, std::string &msg) const {
    for (const auto &b : books) {
        if (b.id == book_id) {
            if (b.available_copies > 0) {
                msg = "Available copies: " + std::to_string(b.available_copies);
                return true;
            } else {
                msg = "No copies available";
                return false;
            }
        }
    }
    msg = "Book not found";
    return false;
}

// Check availability by title substring (simple English).
// Finds first match and reports availability (technical).
bool Library::check_availability_by_title(const std::string &title_q, std::string &msg) const {
    for (const auto &b : books) {
        if (contains_ci(b.title, title_q)) {
            if (b.available_copies > 0) {
                msg = "Found '" + b.title + "' (ID: " + std::to_string(b.id) + "), Available: " + std::to_string(b.available_copies);
                return true;
            } else {
                msg = "Found '" + b.title + "' (ID: " + std::to_string(b.id) + "), No copies available";
                return false;
            }
        }
    }
    msg = "No matching title found";
    return false;
}

// Small summary: total books, currently issued count, most issued book historically (simple English).
// Computes issued counts and prints a small report; most-issued uses historical issue occurrence count (technical).
void Library::small_summary() const {
    int total_books = 0;
    int currently_issued = 0;
    for (const auto &b : books) {
        total_books += b.total_copies;
        currently_issued += (b.total_copies - b.available_copies);
    }

    // historical counts
    std::map<int,int> count;
    for (const auto &ir : issues) count[ir.book_id]++;

    int most_id = 0;
    int most_count = 0;
    for (const auto &p : count) {
        if (p.second > most_count) { most_count = p.second; most_id = p.first; }
    }

    std::string most_title = "(none)";
    if (most_id != 0) {
        for (const auto &b : books) if (b.id == most_id) { most_title = b.title; break; }
    }

    std::cout << "--- Summary ---\n";
    std::cout << "Total copies in library: " << total_books << '\n';
    std::cout << "Currently issued copies: " << currently_issued << '\n';
    std::cout << "Most issued (historical): " << most_title << " (Book ID: " << most_id << ", Issued times: " << most_count << ")\n";
}
