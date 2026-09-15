#include <iostream>

int main(){
    const int numRows = 2;
    const int numCollumns = 3;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCollums; j++) {
            std::cout << "(" << j << "," << i << ") ";
        }
        std::cout << endl;
    }
    
    return 0;
}