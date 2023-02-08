// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

#include <pthread.h>
#include <iostream>

#include "sum.h"

int main(int argc, char* argv[]){
    // Confirming there was an argument 
    if( argc == 1 ){
        std::cerr << "Please enter an argument!\n";
        return 1;
    }

    // Converting the first argument to an integer type
    int startingNum = atoi(argv[1]);

    // Beginning use of threads
    pthread_t thread_id; // Thread ID
    pthread_attr_t attr; // Thread attributes 
    int stat = pthread_create( &thread_id, NULL, sum, &startingNum );
    if( stat != 0 ){
        std::cout << "Error: Failed to create a thread!" << std::endl;
        exit(EXIT_FAILURE);
    }
    pthread_join(thread_id, NULL);
    return 0;
}