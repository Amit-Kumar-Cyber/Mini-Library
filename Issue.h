// IssueRecord class declaration: tracks book issues and returns (simple English).
// Fields: id, book_id, member_id, issue_date, return_date (empty if not returned) (technical).

#ifndef ISSUE_H
#define ISSUE_H

#include <string>

class IssueRecord {
public:
    int id; // unique issue id
    int book_id;
    int member_id;
    std::string issue_date;  // YYYY-MM-DD
    std::string return_date; // empty if not returned

    IssueRecord();
    IssueRecord(int _id, int _book, int _member, const std::string &_issue_date);

    std::string to_csv() const;
    static IssueRecord from_csv(const std::string &line);
    bool is_returned() const;
};

#endif // ISSUE_H
