#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

sem_t sem;
int numThreads = 3;

void runMeFirst() 
{
    cout << "Run me first" << endl;
    sem_post(&sem);
}

void runMeSecond() 
{
    sem_wait(&sem);
    cout << "I run second" << endl;
    sem_post(&sem);
}

void runMeThird() 
{
    sem_wait(&sem);
    cout << "I run third" << endl;
}

int main() 
{
    sem_init(&sem, 0, numThreads);

    thread t1(runMeFirst);
    thread t2(runMeSecond);
    thread t3(runMeThird);

    t1.join();
    t2.join();
    t3.join();

    sem_destroy(&sem);

    return 0;
}
