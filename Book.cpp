// Book class implementation and CSV helpers (simple English).
// Implements constructor, parser and serializer used for persistent storage (technical).

#include "Book.h"
#include "utils.h"
#include <sstream>

Book::Book() : id(0), title(""), author(""), total_copies(0), available_copies(0) {
    // Default ctor (simple English).
    // Default initialize all fields (technical).
}

Book::Book(int _id, const std::string &_title, const std::string &_author, int total)
    : id(_id), title(_title), author(_author), total_copies(total), available_copies(total) {
    // Construct book with same total and available copies initially (simple English).
    // Sets id, title, author, total_copies and available_copies = total (technical).
}

std::string Book::to_csv() const {
    // Return a pipe-separated CSV line for this book (simple English).
    // Fields: id|title|author|total|available - escaping not implemented for simplicity (technical).
    std::ostringstream oss;
    oss << id << '|' << title << '|' << author << '|' << total_copies << '|' << available_copies;
    return oss.str();
}

Book Book::from_csv(const std::string &line) {
    // Parse CSV book line to Book object (simple English).
    // Expects format id|title|author|total|available, trims fields and handles missing values (technical).
    auto parts = split(line, '|');
    Book b;
    if (parts.size() >= 5) {
        b.id = to_int_safe(parts[0]);
        b.title = parts[1];
        b.author = parts[2];
        b.total_copies = to_int_safe(parts[3]);
        b.available_copies = to_int_safe(parts[4]);
    } else if (parts.size() >= 4) {
        b.id = to_int_safe(parts[0]);
        b.title = parts[1];
        b.author = parts[2];
        b.total_copies = to_int_safe(parts[3]);
        b.available_copies = b.total_copies;
    }
    return b;
}
