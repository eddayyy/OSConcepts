// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu

#include <iostream>
#include <pthread.h>
#include <mutex>

int sum = 0;
std::mutex mtx;

void *runner(void *a) {
    mtx.lock();
    int startingNum = *(int*)a;
    int localSum = 0;
    localSum = 100 / 2 * (startingNum * 2 + 99);
    std::cout << "Thread " << pthread_self() << " calculated sum " << localSum << std::endl;
    sum += localSum;
    pthread_exit(0);
}

int main() {
    // Initialize default thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Create first thread
    pthread_t tid1;
    int startingNum1 = 0;
    pthread_create(&tid1, &attr, runner, &startingNum1);

    // Initialize default thread attributes for thread 2
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);

    // Create second thread
    pthread_t tid2;
    int startingNum2 = 1;
    pthread_create(&tid2, &attr2, runner, &startingNum2);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Print the result
    mtx.unlock();
    if(sum != 5050){
        std::cout << "The sum is: " << sum << std::endl;
    }
    return 0;
}
