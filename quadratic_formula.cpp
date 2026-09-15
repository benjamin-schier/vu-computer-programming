#include <iostream>
#include <vector> 
#include <cmath>

std::vector<double> oneSolution (double a, double b, double c) {
    std::vector<double> solutions (1);

    solutions.at(0) = -b / (2 * a);

    return solutions;
}

std::vector<double> twoSolutions (double a, double b, double c) {
    std::vector<double> solutions (2);

    solutions.at(0) = (-b + sqrt(b * b - (4 * a * c))) / (2 * a); 
    solutions.at(1) = (-b - sqrt(b * b - (4 * a * c))) / (2 * a);

    return solutions;
}

std::vector<double> quadraticFormula (double a, double b, double c) {
    
    double discriminant = (b * b) - (4 * a * c);
    std::vector<double> solutions;
    if (discriminant < 0) {
        return solutions;
    }
    else if (discriminant == 0) {
        solutions = oneSolution(a, b, c);
    }
    else {
        solutions = twoSolutions(a, b, c);
    }
    return solutions;

}

int main(){

    double a;
    double b;
    double c;
    std::vector<double> solutions;
    int numSolutions; 

    std::cout << "Please enter the values of a, b, and c: ";
    std::cin >> a >> b >> c;
    std::cout << std::endl;

    solutions = quadraticFormula(a, b, c);
    numSolutions = solutions.size();

    switch (numSolutions) {
        case 0:
            std::cout << "There is no solution." << std::endl;
            break;
        case 1:
            std::cout << "There is " << numSolutions << "solution." << std::endl;
            std::cout << "The solution is: " << solutions.at(0) << std::endl;
            break;
        case 2:
            std::cout << "There is " << numSolutions << " solutions." << std::endl;
            std::cout << "The solutions are: " << solutions.at(0) << " and " << solutions.at(1) << std::endl;
            break;
        default:
            std::cout << "-- ERROR --" << std::endl;
            break;
    }

    
    return 0;
}