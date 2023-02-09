// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

#include <iostream>
#include <pthread.h>

#include "sum.hpp"

int main(int argc, char* argv[]){
    // Confirming there was an argument 
    if( argc != 2 ){
        std::cerr << "Please enter 1 argument!\n";
        return 1;
    }

    // Converting the first argument to an integer type
    int startingNum = atoi(argv[1]);

    // Beginning use of threads
    pthread_t tid; // Thread ID
    pthread_attr_t attr; // Default attributes 
    pthread_attr_init(&attr);
    pthread_create( &tid, &attr, sum, &startingNum );
    pthread_join( tid, NULL );
    return 0;
}
