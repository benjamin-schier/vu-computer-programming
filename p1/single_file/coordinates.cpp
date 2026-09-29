#include <iostream>

int main(){
    const int numRows = 2;
    const int numColumns = 3;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            std::cout << "(" << j << "," << i << ") ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}