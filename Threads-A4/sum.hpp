// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

#include <iostream>
#include <pthread.h>

void *sum(void *a){
    int startingNum = *(int*)a;
    int sum = 0;
    sum = 100 / 2 * (startingNum * 2 + 99);
    std::cout << "The sum is: " << sum << std::endl;
    pthread_exit(0);
}