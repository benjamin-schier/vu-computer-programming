#include <iostream>
#include <vector>

#include "partialsums.h"

//
// This file shows how your function secondSmallest() should use the two classes for DIY exceptions.
//
// You can modify this file for your own testing purposes.
//
// Modifications to this file only have effect when you Run your code.
// Upon Hand-in, the original version of this file will be used.
//

int main()
{
    std::vector<int> inputNumbers;
    std::cout << "Please enter some numbers (q to quit)\n";
    do{
        int nextNumber;
        std::cin >> nextNumber;
        if ( std::cin.good() ){
            inputNumbers.push_back(nextNumber);
        }
    } while ( std::cin.good() );

    std::vector<int> partials = partialSums(inputNumbers);
    printVector(partials);
    try{
        int secondSmallestValue = secondSmallest(partials);
        std::cout << "The second smallest partial sum is " << secondSmallestValue << std::endl;
    }catch ( TooFewNumbers& exception ){
        std::cout << "No second smallest partial sum exists, number of sums is " << exception.size() << std::endl;
    }catch ( AllTheSameValue& exception ){
        std::cout << "No second smallest partial sum exists, the single value is " << exception.value() << std::endl;
    }

    return 0;
}