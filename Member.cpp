// Member class implementation and CSV helpers (simple English).
// Implements ctor, to_csv and parser for persisting members (technical).

#include "Member.h"
#include "utils.h"
#include <sstream>

Member::Member() : id(0), name(""), contact("") {
    // Default member constructor (simple English).
    // Initialize id,name,contact with defaults (technical).
}

Member::Member(int _id, const std::string &_name, const std::string &_contact)
    : id(_id), name(_name), contact(_contact) {
    // Construct member from provided values (simple English).
    // Assign id,name,contact (technical).
}

std::string Member::to_csv() const {
    // Convert member to pipe-separated line id|name|contact (simple English).
    // No escaping implemented for simplicity (technical).
    std::ostringstream oss;
    oss << id << '|' << name << '|' << contact;
    return oss.str();
}

Member Member::from_csv(const std::string &line) {
    // Parse member CSV line into Member object (simple English).
    // Expects id|name|contact and trims entries (technical).
    auto parts = split(line, '|');
    Member m;
    if (parts.size() >= 1) m.id = to_int_safe(parts[0]);
    if (parts.size() >= 2) m.name = parts[1];
    if (parts.size() >= 3) m.contact = parts[2];
    return m;
}
