#include <iostream>
#include <fstream> 
#include <string> 
#include <vector>
#include <cctype>
#include <ios>

bool isVowel (char c) {
    c = std::tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void printMostFrequentLetter (const std::vector<int> numLetters) {
    int largest = numLetters.at(0);
    char mostFrequent = 'a';
    for (int i = 0; i < numLetters.size(); i++) {
        if (largest < numLetters.at(i)) {
            largest = numLetters.at(i);
            mostFrequent = i + 'a';
        }
    }
    std::cout << "Most frequent letter, overall: " << mostFrequent << "(" << largest << " times)" << std::endl;
}
void printMostFrequentVowel (const std::vector<int> numLetters) {
    int largest = numLetters.at(0);
    char mostFrequent = 'a';
    for (int i = 0; i < numLetters.size(); i++) {
        if (isVowel(i + 'a') && largest < numLetters.at(i)) {
            largest = numLetters.at(i);
            mostFrequent = i + 'a';
        }
    }
    std::cout << "Most frequent vowel: " << mostFrequent << "(" << largest << " times)" << std::endl;
    
}
void printMostFrequentConsonant (const std::vector<int> numLetters) {
    int largest = numLetters.at(1);
    char mostFrequent = 'b';
    for (int i = 0; i < numLetters.size(); i++) {
        if (!isVowel(i + 'a') && largest < numLetters.at(i)) {
            largest = numLetters.at(i);
            mostFrequent = i + 'a';
        }

    }
    std::cout << "Most frequent consonant: " << mostFrequent << "(" << largest << " times)" << std::endl;
    
}

void processInput (std::istream& input) {
    std::vector<int> numLetters (26, 0);
    char c;

    //inupt is either "cin" or "file", depending on parameter
    // runs to end of input (strg + D -OR- eof) 
    while (input >> c) {
        if (std::islower(c) || std::isupper(c)) {
            c = std::tolower(c);
            numLetters.at(c - 'a')++; //if c = 'a' -> 'a'-'a' = 0 -> smallest index -- 'z'-'a' = 25 -> largest index
        }
    }
    printMostFrequentVowel(numLetters);
    printMostFrequentConsonant(numLetters);
    printMostFrequentLetter(numLetters);
} 

int main (int argc, char* argv[]) {

    // first arg is filename
    if (argc > 2) {
        std::cout << "cannot handle parameter list" << std::endl;
        return 1;
    }
    else if (argc == 2) {
        std::ifstream File;
        File.open(argv[1]);
        
        if (!File.is_open()) {
            std::cout << "cannot open input file " << argv[1] << std::endl;
            return 1;
        }

        processInput(File);
    }
    else {
        processInput(std::cin);
    }
    return 0;
}