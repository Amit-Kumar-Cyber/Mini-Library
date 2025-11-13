// Main program with an improved console menu for Phase 5 + Phase 6 (simple English).
// Uses validated input helpers, clearer prompts, confirmations and pauses (technical).

#include <iostream>
#include <string>
#include "Library.h"
#include "utils.h"

int main() {
    // Initialize library with filenames and load data (simple English).
    // Files must be in same folder; will create files on first save (technical).
    Library lib("books.txt", "members.txt", "issues.txt");
    lib.load_all();

    while (true) {
        // Show main menu with numbered options (simple English).
        // Menu covers all features and maps cleanly to functions (technical).
        std::cout << "\n=== Mini Library System ===\n";
        std::cout << "1) Add Book\n";
        std::cout << "2) Add Member\n";
        std::cout << "3) List All Books\n";
        std::cout << "4) Search Book by Title\n";
        std::cout << "5) Search Book by Author\n";
        std::cout << "6) Search Book by ID\n";
        std::cout << "7) Check Availability (by ID or Title)\n";
        std::cout << "8) Issue Book\n";
        std::cout << "9) Return Book\n";
        std::cout << "10) List Issued Books (with member names)\n";
        std::cout << "11) Member History\n";
        std::cout << "12) Summary Report\n";
        std::cout << "13) Exit\n";

        int opt = read_int_range("Choose option (1-13): ", 1, 13);

        if (opt == 1) {
            // Add book flow with non-empty validation for title/author and positive copies (simple English).
            // Generates next id automatically and persists data immediately (technical).
            std::cin.ignore(0); // ensure clean state
            std::string title = read_line_nonempty("Enter Title: ");
            std::string author = read_line_nonempty("Enter Author: ");
            int copies = read_int_range("Enter number of copies (>=1): ", 1, 1000000);
            std::cout << "You entered:\n  Title: " << title << "\n  Author: " << author << "\n  Copies: " << copies << '\n';
            if (confirm_yes_no("Confirm add book")) {
                int id = lib.next_book_id();
                Book b(id, title, author, copies);
                lib.add_book(b);
                std::cout << "Book added successfully with ID " << id << '\n';
            } else {
                std::cout << "Add book cancelled.\n";
            }
            press_enter_to_continue();
        } else if (opt == 2) {
            // Add member flow; non-empty name required (simple English).
            // Assigns a new member id and persists (technical).
            std::cin.ignore(0);
            std::string name = read_line_nonempty("Enter member name: ");
            std::string contact;
            std::cout << "Enter contact (optional, press Enter to skip): ";
            std::getline(std::cin, contact);
            if (confirm_yes_no("Confirm add member")) {
                int id = lib.next_member_id();
                Member m(id, name, contact);
                lib.add_member(m);
                std::cout << "Member added successfully with ID " << id << '\n';
            } else {
                std::cout << "Add member cancelled.\n";
            }
            press_enter_to_continue();
        } else if (opt == 3) {
            lib.list_all_books();
            press_enter_to_continue();
        } else if (opt == 4) {
            std::cin.ignore(0);
            std::string q = read_line_nonempty("Enter title substring to search (case-insensitive): ");
            auto res = lib.search_books_by_title(q);
            if (res.empty()) {
                std::cout << "No books matched your query.\n";
            } else {
                std::cout << "Matches:\n";
                for (auto p : res) {
                    std::cout << p->id << " | " << p->title << " | " << p->author << " | Avl: " << p->available_copies << '\n';
                }
            }
            press_enter_to_continue();
        } else if (opt == 5) {
            std::cin.ignore(0);
            std::string q = read_line_nonempty("Enter author substring to search (case-insensitive): ");
            auto res = lib.search_books_by_author(q);
            if (res.empty()) {
                std::cout << "No books matched your query.\n";
            } else {
                std::cout << "Matches:\n";
                for (auto p : res) {
                    std::cout << p->id << " | " << p->title << " | " << p->author << " | Avl: " << p->available_copies << '\n';
                }
            }
            press_enter_to_continue();
        } else if (opt == 6) {
            int id = read_int("Enter Book ID: ");
            Book* b = lib.find_book_by_id(id);
            if (!b) std::cout << "Book not found.\n";
            else std::cout << b->id << " | " << b->title << " | " << b->author << " | Total: " << b->total_copies << " | Avl: " << b->available_copies << '\n';
            press_enter_to_continue();
        } else if (opt == 7) {
            std::cin.ignore(0);
            std::cout << "1) Check by ID\n2) Check by Title\n";
            int c = read_int_range("Choose (1-2): ", 1, 2);
            std::cin.ignore(0);
            std::string msg;
            if (c == 1) {
                int id = read_int("Enter Book ID: ");
                if (lib.check_availability_by_id(id, msg)) std::cout << "Available: " << msg << '\n';
                else std::cout << "Info: " << msg << '\n';
            } else {
                std::string q = read_line_nonempty("Enter title substring: ");
                if (lib.check_availability_by_title(q, msg)) std::cout << "Info: " << msg << '\n';
                else std::cout << "Info: " << msg << '\n';
            }
            press_enter_to_continue();
        } else if (opt == 8) {
            int bid = read_int("Book ID: ");
            int mid = read_int("Member ID: ");
            // confirm action
            std::cout << "You are about to issue Book ID " << bid << " to Member ID " << mid << ".\n";
            if (!confirm_yes_no("Proceed with issue")) {
                std::cout << "Issue cancelled.\n";
                press_enter_to_continue();
                continue;
            }
            std::string msg;
            if (lib.issue_book(bid, mid, msg)) std::cout << "Success: " << msg << '\n';
            else {
                std::cout << "Error: " << msg << '\n';
                // helpful hint: show book/member quick lists if not found
                if (msg == "Book not found") {
                    if (confirm_yes_no("Show book list?")) lib.list_all_books();
                } else if (msg == "Member not found") {
                    if (confirm_yes_no("Show member list?")) {
                        std::cout << "ID | Name | Contact\n";
                        std::cout << "-------------------\n";
                        for (const auto &m : lib.members) std::cout << m.id << " | " << m.name << " | " << m.contact << '\n';
                    }
                }
            }
            press_enter_to_continue();
        } else if (opt == 9) {
            std::cin.ignore(0);
            std::cout << "1) Return by Issue ID\n2) Return by BookID+MemberID\n";
            int c = read_int_range("Choose (1-2): ", 1, 2);
            if (c == 1) {
                int iid = read_int("Issue ID: ");
                if (!confirm_yes_no("Confirm return for Issue ID " + std::to_string(iid) + "?")) {
                    std::cout << "Return cancelled.\n"; press_enter_to_continue(); continue;
                }
                std::string msg;
                if (lib.return_book(iid, msg)) std::cout << "Success: " << msg << '\n';
                else std::cout << "Error: " << msg << '\n';
            } else {
                int bid = read_int("Book ID: ");
                int mid = read_int("Member ID: ");
                // find active issue for this pair
                int found = 0;
                for (const auto &ir : lib.issues) {
                    if (ir.book_id == bid && ir.member_id == mid && !ir.is_returned()) { found = ir.id; break; }
                }
                if (found == 0) {
                    std::cout << "No active issue found for this Book+Member.\n";
                } else {
                    if (!confirm_yes_no("Confirm return of Issue ID " + std::to_string(found) + "?")) {
                        std::cout << "Return cancelled.\n";
                    } else {
                        std::string msg;
                        if (lib.return_book(found, msg)) std::cout << "Success: " << msg << '\n';
                        else std::cout << "Error: " << msg << '\n';
                    }
                }
            }
            press_enter_to_continue();
        } else if (opt == 10) {
            lib.list_issued_books();
            press_enter_to_continue();
        } else if (opt == 11) {
            int mid = read_int("Member ID: ");
            Member* m = lib.find_member_by_id(mid);
            if (!m) std::cout << "Member not found.\n";
            else lib.list_member_history(mid);
            press_enter_to_continue();
        } else if (opt == 12) {
            lib.small_summary();
            press_enter_to_continue();
        } else if (opt == 13) {
            if (confirm_yes_no("Are you sure you want to exit the program")) {
                std::cout << "Goodbye.\n";
                break;
            }
        }
    }

    return 0;
}
