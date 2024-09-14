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
 * -------------------------------------------------------------
 * programa que crea diferentes hilos utilizando Phtreads 
 * y utiliza la funcion phtread_join en un mismo for (ejecución secuencial)
 * -------------------------------------------------------------
 */

 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>

//cantidad de hilos a crear
 #define NUM_THREADS 10

 void *PrintHello(void *paramID){
    int id;
    //conversion del puntero a void a entero
    id = *((int *)paramID);
    printf("Hello world thread No.%d \n", id);//indicamos el no. hilo actual
    pthread_exit(NULL);
    return(NULL);
 }
 int main(int argc, char *argv[]){
    //nombre del hilo
    pthread_t threadsID[NUM_THREADS];
    //creamos paramentros del hilo
    int rc, t, param[NUM_THREADS];
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_JOINABLE);
    for(t = 0; t < NUM_THREADS; t++){
        printf("En rutina principal: creando el thread #%d \n", t);
        param[t] = t;
        //creamos hilo
        rc = pthread_create(&threadsID[t], &attr, PrintHello, (void *) &param[t]);
        if(rc != 0){
            printf("ERROR: codigo de retorno de desde pthread_create %d \n", rc);
            exit(-1);
        }
        //realizamos el join
        pthread_join(threadsID[t], NULL);
    }
    pthread_attr_destroy (&attr);
    //borramos atributos
    pthread_exit(NULL);
 }