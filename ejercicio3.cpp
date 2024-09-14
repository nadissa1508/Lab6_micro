/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3086 - Programacion de Microprocesadores
 * Ver.: 1.1 2024/21/08
 * Mod.: Jorge Luis Felipe Aguilar Portillo
 * Mod.: Angie Nadissa Vela López
 * Carnet: 23764
 *
 * References:
 * Rauber, T., & Rünger, G. (2023). Parallel programming: 
 * For multicore and cluster systems (3a ed.). Springer International Publishing.
 * 
 * https://www.geeksforgeeks.org/c-fibonacci-series/
 * --------------------------------------------------
 * -------------------------------------------------------------
 * programa que determina los números de la serie Fibonacci utilizando Phtreads POSIX
 * Versión que utiliza long long funciona bien hasta F92
 * -------------------------------------------------------------
 */

#include <iostream>
#include <pthread.h>
#include <cmath>

using namespace std;


// Estructura para contener los argumentos del hilo
struct ThreadArgs {
    int n; // Valor de n para calcular el término de la serie 
    double *result; // Puntero al resultado del término 
};

void *calculateTerm(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    int n = threadArgs->n;
    double *result = threadArgs->result;

    *result = pow(-1, n + 1) / n; // Calcula el término n-ésimo de la serie 

    pthread_exit(NULL); // Termina el hilo 
}

int main() {
    int n;
    cout << "Ingrese el valor máximo de n: "; // Pide al usuario que ingrese un valor máximo para n 
    cin >> n;

    double sum = 0.0; // Inicializa la suma de la serie
    pthread_t threads[n]; // Arreglo de hilos 
    ThreadArgs threadArgs[n]; //Arreglo de estructuras ThreadArgs para contener los argumentos del hilo 

    for (int i = 0; i < n; i++) {
        threadArgs[i].n = i + 1; // Inicializa los argumentos del hilo 
        threadArgs[i].result = new double; // Crea una memoria dinámicamente para el resultado 
        pthread_create(&threads[i], NULL, calculateTerm, (void *)&threadArgs[i]); // Crea un nuevo hilo 
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL); // Espera a que cada hilo termine 
        sum += *threadArgs[i].result; // Suma el resultado del hilo a la suma acumulada 
        delete threadArgs[i].result; // Elimina la memoria dinámica 
    }

    cout << "La suma de la serie es: " << sum << endl; // Imprime la suma de la serie

    return 0;
}