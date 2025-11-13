// IssueRecord implementation: constructors and CSV helpers (simple English).
// Also provides is_returned check for convenience (technical).

#include "Issue.h"
#include "utils.h"
#include <sstream>

IssueRecord::IssueRecord() : id(0), book_id(0), member_id(0), issue_date(""), return_date("") {
    // Default ctor initializes fields to empty/zero (simple English).
    // Sets id/book_id/member_id to 0 and date strings empty (technical).
}

IssueRecord::IssueRecord(int _id, int _book, int _member, const std::string &_issue_date)
    : id(_id), book_id(_book), member_id(_member), issue_date(_issue_date), return_date("") {
    // Construct issue record with issue date, no return date (simple English).
    // Sets return_date empty to indicate not-returned (technical).
}

std::string IssueRecord::to_csv() const {
    // Convert issue record to CSV id|book_id|member_id|issue_date|return_date (simple English).
    // return_date may be empty when not returned (technical).
    std::ostringstream oss;
    oss << id << '|' << book_id << '|' << member_id << '|' << issue_date << '|' << return_date;
    return oss.str();
}

IssueRecord IssueRecord::from_csv(const std::string &line) {
    // Parse CSV into IssueRecord object (simple English).
    // Expects 5 fields; missing return_date considered empty (technical).
    auto parts = split(line, '|');
    IssueRecord ir;
    if (parts.size() >= 1) ir.id = to_int_safe(parts[0]);
    if (parts.size() >= 2) ir.book_id = to_int_safe(parts[1]);
    if (parts.size() >= 3) ir.member_id = to_int_safe(parts[2]);
    if (parts.size() >= 4) ir.issue_date = parts[3];
    if (parts.size() >= 5) ir.return_date = parts[4];
    return ir;
}

bool IssueRecord::is_returned() const {
    // True if return_date is non-empty (simple English).
    // Checks if return_date string length > 0 (technical).
    return !return_date.empty();
}
