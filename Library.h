// Library manager class declaration: orchestrates books, members and issues (simple English).
// Provides load/save and operations: add/search/issue/return and report helpers (technical).

#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"
#include "Member.h"
#include "Issue.h"
#include <string>

class Library {
public:
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<IssueRecord> issues;

    std::string books_file;
    std::string members_file;
    std::string issues_file;

    Library(const std::string &bfile, const std::string &mfile, const std::string &ifile);

    void load_all();
    void save_all();

    int next_book_id() const;
    int next_member_id() const;
    int next_issue_id() const;

    void add_book(const Book &b);
    void add_member(const Member &m);

    Book* find_book_by_id(int id);
    Member* find_member_by_id(int id);

    std::vector<Book*> search_books_by_title(const std::string &q); // case-insensitive
    std::vector<Book*> search_books_by_author(const std::string &q); // case-insensitive

    bool issue_book(int book_id, int member_id, std::string &msg);
    bool return_book(int issue_id, std::string &msg);

    // reporting helpers
    void list_all_books() const;
    void list_issued_books() const; // now shows member names too
    void list_member_history(int member_id) const;

    bool check_availability_by_id(int book_id, std::string &msg) const;
    bool check_availability_by_title(const std::string &title_q, std::string &msg) const;

    void small_summary() const; // prints total books, currently issued count, most issued book
};

#endif // LIBRARY_H
