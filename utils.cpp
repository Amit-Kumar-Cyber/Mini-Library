// Implementations of utility functions (simple English).
// Uses only std libs, lightweight string helpers, date and console input helpers (technical).

#include "utils.h"
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cctype>

std::string trim(const std::string &s) {
    // Remove leading/trailing spaces (simple English).
    // Implementation: find first/last non-space and substr (technical).
    size_t start = 0;
    while (start < s.size() && isspace((unsigned char)s[start])) start++;
    if (start == s.size()) return "";
    size_t end = s.size() - 1;
    while (end > start && isspace((unsigned char)s[end])) end--;
    return s.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string &s, char delim) {
    // Split a string by delimiter and return parts (simple English).
    // Implementation: stringstream parse, push trimmed parts (technical).
    std::vector<std::string> parts;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        parts.push_back(trim(item));
    }
    return parts;
}

std::string today_date() {
    // Return today's date as YYYY-MM-DD (simple English).
    // Implementation: use chrono::system_clock and std::put_time (technical).
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);
    std::tm* tm_ptr;
#if defined(_WIN32) && defined(_MSC_VER)
    // MSVC compiler on Windows
    std::tm tm;
    localtime_s(&tm, &t);
    tm_ptr = &tm;
#elif defined(_WIN32)
    // MinGW or other compilers on Windows - use standard localtime
    tm_ptr = std::localtime(&t);
#elif defined(_POSIX_C_SOURCE) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    // POSIX systems (Linux, macOS, etc.)
    std::tm tm;
    localtime_r(&t, &tm);
    tm_ptr = &tm;
#else
    // Fallback to standard localtime
    tm_ptr = std::localtime(&t);
#endif
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d");
    return oss.str();
}

int to_int_safe(const std::string &s) {
    // Convert string to int safely (simple English).
    // Implementation: stoi with try/catch; returns 0 on failure (technical).
    try {
        return std::stoi(s);
    } catch (...) {
        return 0;
    }
}

std::string to_lower(const std::string &s) {
    // Return a lowercase version of the input (simple English).
    // Implementation: transform with tolower on unsigned char (technical).
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) out.push_back(std::tolower(c));
    return out;
}

bool contains_ci(const std::string &hay, const std::string &needle) {
    // Case-insensitive substring check (simple English).
    // Implementation: lower both strings and use find (technical).
    return to_lower(hay).find(to_lower(needle)) != std::string::npos;
}

// Console input helpers implementation

int read_int(const std::string &prompt) {
    // Read an integer from stdin, retrying until valid (simple English).
    // Loops until std::cin can parse an int; clears bad state and discards rest of line on failure (technical).
    while (true) {
        std::cout << prompt;
        int v;
        if (std::cin >> v) {
            std::cin.ignore(10000, '\n');
            return v;
        } else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a valid integer.\n";
        }
    }
}

int read_int_range(const std::string &prompt, int minv, int maxv) {
    // Read integer and ensure it's within [minv, maxv] (simple English).
    // Uses read_int then checks bounds and repeats on failure (technical).
    while (true) {
        int v = read_int(prompt);
        if (v < minv || v > maxv) {
            std::cout << "Please enter a number between " << minv << " and " << maxv << ".\n";
        } else return v;
    }
}

std::string read_line_nonempty(const std::string &prompt) {
    // Read a non-empty trimmed line from stdin (simple English).
    // Trims input and repeats prompt until non-empty result (technical).
    while (true) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);
        s = trim(s);
        if (!s.empty()) return s;
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

bool confirm_yes_no(const std::string &prompt) {
    // Ask a yes/no question; returns true for yes (simple English).
    // Accepts y/Y as yes, n/N as no; loops until valid response (technical).
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::string s;
        std::getline(std::cin, s);
        if (s.empty()) continue;
        char c = std::tolower((unsigned char)s[0]);
        if (c == 'y') return true;
        if (c == 'n') return false;
        std::cout << "Please answer y or n.\n";
    }
}

void press_enter_to_continue() {
    // Pause and wait for user to press Enter (simple English).
    // Uses getline to wait for the newline (technical).
    std::cout << "\nPress Enter to continue...";
    std::string tmp;
    std::getline(std::cin, tmp);
}
