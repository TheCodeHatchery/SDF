#include <iostream>
#include "csv/csv.h"

int main(int argc, const char* argv[])
{
    auto csv = sdf::read_csv_from_cstr(R"(1, 2, 3
4, 5, 6
7, 8, 9
)");
    std::cout << "Test!\n";
    std::cout << csv.get_row(0).get_entry(0) << "\n";
    std::cout << csv.get_row(0).get_entry(1) << "\n";
    std::cout << csv.get_row(0).get_entry(2) << "\n";
    std::cout << csv.get_row(1).get_entry(0) << "\n";
    std::cout << csv.get_row(1).get_entry(1) << "\n";
    std::cout << csv.get_row(1).get_entry(2) << "\n";
    std::cout << csv.get_row(2).get_entry(0) << "\n";
    std::cout << csv.get_row(2).get_entry(1) << "\n";
    std::cout << csv.get_row(2).get_entry(2) << "\n";
}
