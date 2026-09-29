#include <iostream>
#include <fstream>
#include <string>

// write the program such that it opens its own source code file (diy-print.cpp)
// and reads its contents, echoeing them to std::cout
//
// for reading you can use the >> operator
// if you want to preserve white space, read instead with:
//    std::getline("input stream", "string");
//
int main()
{
    std::ifstream inputFile;
    inputFile.open("diy-print.cpp");
    if (!inputFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return 1;
    }
    int lineNr = 1;
    std::string line;
    while (getline(inputFile, line)) {
        std::cout << lineNr << ": " << line << std::endl; 
        lineNr++;
    }
    
    return 0;
}
