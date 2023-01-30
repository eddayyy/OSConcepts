// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

#include <iostream>

void collatzConjecture( int num ){
    // Run the algorithm until we reach 1
    while( num > 1 ){
        std::cout << num << ", ";
        // Even numbers
        if( num % 2 == 0 ){
            num /= 2;
        } 
        
        // Odd Numbers
        else{
            num = ( 3 * num ) + 1;
        }
    }
    
    // Will always print out 1 
    std::cout << num << std::endl;
}

