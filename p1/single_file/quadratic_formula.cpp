#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

void oneSolution(double a, double b, double c)
{
    double x;
    x = -b / (2 * a);
    std::cout << "There is 1 solution." << std::endl;
    std::cout << "The solution is: " << x << std::endl;

    return;
}

void twoSolutions(double a, double b, double c)
{
    double x1 = (-b + sqrt(b * b - (4 * a * c))) / (2 * a);
    double x2 = (-b - sqrt(b * b - (4 * a * c))) / (2 * a);
    std::cout << "There are 2 solutions." << std::endl;
    std::cout << "The solutions are: " << x1 << " and " << x2 << std::endl;

    return;
}

void quadraticFormula(double a, double b, double c)
{

    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
    {
        std::cout << "There is no solution." << std::endl;
        return;
    }
    else if (discriminant == 0)
    {
        oneSolution(a, b, c);
    }
    else
    {
        twoSolutions(a, b, c);
    }

    return;
}
double readDouble () {
    double x;
    if (!(std::cin >> x)) {
        throw std::runtime_error("Malformed user input");
    }
    return x;
}

int main()
{
    try {

        std::cout << "Please enter the values of a, b, and c: ";
        double a = readDouble();
        double b = readDouble();
        double c = readDouble();

        if (a == 0)
        {
            throw std::runtime_error("a must not be zero");
        }

        quadraticFormula(a, b, c);
    }
    catch (std::runtime_error &err) {
        std::cout << "An error occurred: " << err.what() << std::endl;
        return 1;
    }

    return 0;
}