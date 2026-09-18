// Assignment 1: Ticket Price Calculator
//
// See midterm_mock_exam.md, Part 2, for the full assignment description.
//
// Suggested time: 25 minutes.

#include <iostream>

int main()
{
    int input;
    double totalRevenue = 0.0;
    unsigned int ticketCount = 0;
    const double child = 6.0;
    const double teen = 9.0;
    const double adult = 12.0;
    const double senior = 8.0;

    std::cout << "Enter age (-1 to stop): ";
    std::cin >> input;
    while (input > -1) {
        if (input < 12) {
            std::cout << "Age " << input << " -> child ticket: 6.00 euro" << std::endl;
            totalRevenue = totalRevenue + child;
            ticketCount++;
        }
        else if (input < 18) {
            std::cout << "Age " << input << " -> teen ticket: 9.00 euro" << std::endl;
            totalRevenue = totalRevenue + teen;
            ticketCount++;
        }
        else if (input < 65) {
            std::cout << "Age " << input << " -> adult ticket: 12.00 euro" << std::endl;
            totalRevenue = totalRevenue + adult;
            ticketCount++;
        }
        else {
            std::cout << "Age " << input << " -> senior ticket: 8.00 euro" << std::endl;
            totalRevenue = totalRevenue + senior;
            ticketCount++;
        }

        std::cout << "Enter age (-1 to stop): ";
        std::cin >> input;
    }
    std::cout << "Tickets sold: " << ticketCount << ", total revenue: " << totalRevenue << " euro" << std::endl;
    


    return 0;
}
