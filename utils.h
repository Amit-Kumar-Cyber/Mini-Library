// Simple helper functions and small utilities used across the project (simple English).
// Provides string trimming, splitting, date helpers and validated console input helpers (technical).

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::string trim(const std::string &s);
std::vector<std::string> split(const std::string &s, char delim);
std::string today_date(); // returns YYYY-MM-DD
int to_int_safe(const std::string &s); // safe string->int
std::string to_lower(const std::string &s); // lowercase copy of string
bool contains_ci(const std::string &hay, const std::string &needle); // case-insensitive substring check

// Console input helpers
int read_int(const std::string &prompt); // loop until user enters an integer
int read_int_range(const std::string &prompt, int minv, int maxv); // integer in range
std::string read_line_nonempty(const std::string &prompt); // loop until non-empty trimmed line
bool confirm_yes_no(const std::string &prompt); // ask Y/N, returns true for yes
void press_enter_to_continue(); // waits for Enter key
#endif // UTILS_H
