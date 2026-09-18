// Assignment 2: Exam Score Statistics
//
// See midterm_mock_exam.md, Part 3, for the full assignment description.
//
// Suggested time: 40 minutes.

#include <iostream>
#include <vector>

double calculateAverage (const std::vector<double>& v) {
    double sum = 0.0;
    for (int i = 0; i < v.size(); i++) {
        sum = sum + v.at(i);
    }
    return sum / v.size();
}
double findMaximum (const std::vector<double>& v) {
    double max = v.at(0);
    for (int i = 0; i < v.size(); i++) {
        if (max < v.at(i)) {
            max = v.at(i);  
        }
    }
    return max;
}
int scoresPassing (const std::vector<double>& v) {
    int passing = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i) >= 5.5) {
            passing ++;
        }
    }
    return passing;
}

int main()
{
    int n;

    std::cout << "How many scores? ";
    std::cin >> n;
    std::vector<double> scores;
    std::cout << "Scores: ";
    for (int i = 0; i < n; i++) {
        double input;
        std::cin >> input;
        scores.push_back(input);
    }
    for (int i = 0; i < scores.size(); i++) {
        std::cout << scores.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Average: " << calculateAverage(scores) << std::endl;
    std::cout << "Maximum: " << findMaximum(scores) << std::endl;
    std::cout << "Passing (>=5.5): " << scoresPassing(scores) << " out of " << n << std::endl;

    return 0;
}

// Define your functions here.
