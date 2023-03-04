// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu
//
// ---------------------------------------------------------------
//
// Steps: 
// 1) Read in the message store it into a variable
// 2) Reverse the string
// 3) Write the new string to a new pipe and send it to the parent
//
// --------------------------------------------------------------- 
// BEGIN CODING AREA

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


int main(){
    // Message for pipe 1
    char write_msg[BUFFER_SIZE] = "Hi There";
    // Message to be modified for pipe 2 
    char write_msg2[sizeof(write_msg)];
    strcpy(write_msg2, write_msg);

    char read_msg[BUFFER_SIZE]; 
    int fd1[2], fd2[2];
    pid_t pid; 

    // Create the pipes and check if they fail
    if(pipe(fd1) == -1){
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    
    if(pipe(fd2) == -1){
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Create the child process and check if it fails
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork failed");
        return 1;
    }

    // Parent proces
    if(pid > 0){ 
        // Close the read end of the pipe, Write to the pipe, and close the write end of the pipe
        write(fd1[WRITE_END], write_msg, strlen(write_msg)+1);
        close(fd1[WRITE_END]);

        // Read in pipe 2 - the modified pipe
        read(fd2[READ_END], read_msg, BUFFER_SIZE);
        std::cout << "Now reading pipe 2, the reversed string\n\'" << read_msg << "\'\n";
    }
    // Child process
    else{ 
        // Read in and print out pipe 1
        close(fd1[WRITE_END]);
        read(fd1[READ_END], read_msg, BUFFER_SIZE);     
        close(fd1[READ_END]);
        std::cout << "Now reading pipe 1:\n\'" << read_msg << "\'\n";

        // Modify the message to be used for pipe 2 -> REVERSE CASES OF THE STRING
        for(int i = 0; i < strlen(read_msg); i++){
            if(islower(read_msg[i])){
                write_msg2[i] = toupper(read_msg[i]);
            }
            else if(isupper(read_msg[i])){
                write_msg2[i] = tolower(read_msg[i]);
            }   
        } 
        write(fd2[WRITE_END], write_msg2, strlen(write_msg2)+1);
        close(fd2[WRITE_END]);
    }
    return 0; // Return 0 to indicate successful execution
}
