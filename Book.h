// Book class declaration: represents a book record (simple English).
// Contains ID, title, author, total and available copies plus CSV I/O helpers (technical).

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    int total_copies;
    int available_copies;

    Book();
    Book(int _id, const std::string &_title, const std::string &_author, int total);

    std::string to_csv() const; // convert book to CSV line
    static Book from_csv(const std::string &line); // parse CSV to Book
};

#endif // BOOK_H
