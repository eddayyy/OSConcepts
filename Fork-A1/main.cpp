// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

// Necessary headers for the functions used in this file
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "collatz.hpp" // Including Collatz algorithm file

int main(int argc, char* argv[]){
    // Convert the number to an int
    int startingNum = atoi(argv[1]);
    
    // Check for valid input
    if(startingNum <= 1){
        std::cout << "Please enter a number greater than 1!\n";
        return 1;
    }

    // Fork the following processes - Creating the Child Process 
    pid_t pid = fork();

    // Ensure the child process was successfully created
    if ( pid == -1 ){
        std::cerr << "Error creating the child process." << std::endl;
        return 1;
    } 

    // Run the algorithm on the child process
    else if( pid == 0 ){
        collatzConjecture(startingNum);
    }

    // Invoke wait() on the Parent Process 
    else{
        wait(NULL);
    }

    // Exit Program
    return 0;
}
