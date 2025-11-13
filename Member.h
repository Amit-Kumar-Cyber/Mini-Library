// Member class declaration: represents a library member/student (simple English).
// Fields: id, name, optional contact; CSV I/O helpers included (technical).

#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
    int id;
    std::string name;
    std::string contact;

    Member();
    Member(int _id, const std::string &_name, const std::string &_contact);

    std::string to_csv() const;
    static Member from_csv(const std::string &line);
};

#endif // MEMBER_H
