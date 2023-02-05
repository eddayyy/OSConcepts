// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu


// Include necessary header files for functions used in this program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>       
#include <sys/wait.h>

#include <iostream>

int main(){
    // Preparing the shared-memory object
    const int SIZE = 4096;   // Byte size of shared-memory 
    const char* name = "SharingIsCaring"; // Name of the shared-memory segment
    int fd;                  // File Descriptor
    char *ptr;               // Pointer to shm object
    const char* message_0 = "Hello from the child process!\n"; // Data to be written to the shared-memory object

    // Create shared-memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);     // Give the 4096 bytes of size to the file 
    
    // Make the shared-memory object accessible
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    // Call Fork() to create a child process
    pid_t pid = fork();

    if(pid == -1){
        std::cout << "Child process was not created" << std::endl;
        return 1;
    } 

    // Entering the child process 
    else if (pid == 0){
        std::cout << "[Child process has begun writing to the shared memory object]\n";
        sprintf(ptr, "%s", message_0);  // Write to the shared-memory object
        ptr += strlen(message_0);       // Update the memory address of the shared-memory object
        std::cout << "[Child process has completed writing to the shared-memory]\n\n";
    }
    
    // Entering the parent process 
    else {
        wait(NULL);          // Allow the child process to execute before parent process
        std::cout << "[Entering parent process]\n";
        fd = shm_open(name, O_RDONLY, 0666);  // Open the shared-memory object
        printf("%s", (char*)ptr);             // Print the shared-memory object's contents
    }
    shm_unlink(name);                         // Removing the shared-memory object
    return 0;
}