#include <iostream>
#include <pthread.h>
#include <cmath>

using namespace std;

struct ThreadArgs {
    int n;
    double *result;
};

void *calculateTerm(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    int n = threadArgs->n;
    double *result = threadArgs->result;

    *result = pow(-1, n + 1) / n;

    pthread_exit(NULL);
}

int main() {
    int n;
    cout << "Ingrese el valor máximo de n: ";
    cin >> n;

    double sum = 0.0;
    pthread_t threads[n];
    ThreadArgs threadArgs[n];

    for (int i = 0; i < n; i++) {
        threadArgs[i].n = i + 1;
        threadArgs[i].result = new double;
        pthread_create(&threads[i], NULL, calculateTerm, (void *)&threadArgs[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
        sum += *threadArgs[i].result;
        delete threadArgs[i].result;
    }

    cout << "La suma de la serie es: " << sum << endl;

    return 0;
}