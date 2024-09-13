/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3086 - Programacion de Microprocesadores
 * Ver.: 1.1 2024/21/08
 * Mod.: Jorge Luis Felipe Aguilar Portillo
 * Mod.: Angie Nadissa Vela López
 * Carnet: 23764
 *
 * References:
 * Chandra, . R. et al. Parallel Programming
 * in OpenMP
 * -------------------------------------------------------------
 * programa que crea diferentes hilos utilizando phtread POSIX
 * y utiliza la funcion phtread_join en diferentes for (ejecución paralela)
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
        rc = pthread_create(&threadsID[t], NULL, PrintHello, (void *) &param[t]);
        if(rc != 0){
            printf("ERROR: codigo de retorno de desde pthread_create %d \n", rc);
            exit(-1);
        }
    }
    for (int i = 1; i < NUM_THREADS; i++) {
        //realizamos el join
        pthread_join(threadsID[t], NULL);
    }
    //borramos atributos
    pthread_exit(NULL);
 }