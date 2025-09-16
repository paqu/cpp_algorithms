#include <algorithms/sorting/quick_sort.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Person {
    std::string name;
    int age;
    double salary;

    // For easy printing
    friend std::ostream &operator<<(std::ostream &os, const Person &p) {
        return os << "{" << p.name << ", " << p.age << ", $" << p.salary << "}";
    }
};

int main() {
    std::cout << "=== Quick Sort with Custom Comparators ===\n\n";

    std::vector<Person> people = {{"Alice", 30, 70000.0},
                                  {"Bob", 25, 50000.0},
                                  {"Charlie", 35, 80000.0},
                                  {"Diana", 28, 60000.0},
                                  {"Eve", 32, 75000.0}};

    std::cout << "Original people:\n";
    for (const auto &person : people) {
        std::cout << "  " << person << "\n";
    }
    std::cout << "\n";

    // Sort by age
    auto sorted_by_age = algorithms::sorting::quick_sort(
        people, [](const Person &a, const Person &b) { return a.age < b.age; });

    std::cout << "Sorted by age:\n";
    for (const auto &person : sorted_by_age) {
        std::cout << "  " << person << "\n";
    }
    std::cout << "\n";

    // Sort by salary (descending)
    auto sorted_by_salary = algorithms::sorting::quick_sort(
        people, [](const Person &a, const Person &b) {
            return a.salary > b.salary; // Note: > for descending
        });

    std::cout << "Sorted by salary (highest first):\n";
    for (const auto &person : sorted_by_salary) {
        std::cout << "  " << person << "\n";
    }
    std::cout << "\n";

    // Sort by name length, then alphabetically
    auto sorted_complex = algorithms::sorting::quick_sort(
        people, [](const Person &a, const Person &b) {
            if (a.name.length() != b.name.length()) {
                return a.name.length() < b.name.length();
            }
            return a.name < b.name; // Alphabetical if same length
        });

    std::cout << "Sorted by name length, then alphabetically:\n";
    for (const auto &person : sorted_complex) {
        std::cout << "  " << person << "\n";
    }

    return 0;
}
