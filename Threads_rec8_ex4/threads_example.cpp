//
// Created by avshalom on 12/18/17.
//
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cmath>
using namespace std;
#define THREADS_NUM 5
int globalCounter = 0;
pthread_mutex_t count_mutex;
struct ThreadArgs {
    int min;
    int max;
};

bool isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

void *countPrimes(void *tArgs) {
    struct ThreadArgs *args = (struct ThreadArgs *)tArgs;
    for (int i = args->min; i <= args->max; i++) {
        if (isPrime(i)) {
            pthread_mutex_lock(&count_mutex);
            globalCounter++;
            pthread_mutex_unlock(&count_mutex);
        }
    }
}

int main() {
    int min, max;
    cout << "Enter a range to search for primes (e.g., 1 10000): ";
    cin >> min >> max;
    // Divide the range between the threads
    pthread_t threads[THREADS_NUM];
    ThreadArgs args[THREADS_NUM];
    int size = max - min + 1;
    for (int i = 0; i < THREADS_NUM; i++) {
        args[i].min = min + i * size / THREADS_NUM;
        if (i == THREADS_NUM - 1)
            args[i].max = max;
        else
            args[i].max = min + (i + 1) * size / THREADS_NUM - 1;
        int rc = pthread_create(&threads[i], NULL, countPrimes, &args[i]);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
    }
    //pthread_exit(NULL);
    void *status;
    for (int i = 0; i < THREADS_NUM; i++) {
        pthread_join(threads[i], &status);
    }
    cout << "The number of primes in the range [" << min <<
         "," << max << "]" << " is: " << globalCounter << endl;
}

/*int main() {
    int min, max;
    cout << "Enter a range to search for primes (e.g., 1 10000): ";
    cin >> min >> max;
    // Divide the range between the threads
    pthread_t threads[THREADS_NUM];
    ThreadArgs args[THREADS_NUM];
    int size = max - min + 1;
    for (int i = 0; i < THREADS_NUM; i++) {
        args[i].min = min + i * size / THREADS_NUM;
        if (i == THREADS_NUM - 1)
            args[i].max = max;
        else
            args[i].max = min + (i + 1) * size / THREADS_NUM - 1;
        int rc = pthread_create(&threads[i], NULL, countPrimes, &args[i]);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}*/

