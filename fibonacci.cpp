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

 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>

 //estructura de cada hilo
 struct threadParameters{
    int id;
    long long result; //acá se guarda el calculo del fibonacci
 };

 void *fibonacci(void *arg){
    int id;
    threadParameters *ps;
    ps=(threadParameters *)arg;
    id = ps->id; 

    //caso base -> fibonacci 0 o 1 es el mismo numero
    if(id == 0 || id == 1){
        ps->result = id;
    }else{//si n >= 2 enfoque fibonacci iterativo
        long long a = 0, b = 1, temp;
        for (int i = 2; i <= id; i++) {
            //calcular el siguiente numero en la secuencia
            temp = a + b;
            //actualizar a
            a = b;
            //actualizar b
            b = temp;
        }
        //guardamos el calculo del fibonacci
        ps->result = b;
    }
    //salida del hilo
    pthread_exit(NULL);
    return(NULL);
 }


 int main(int argc, char *argv[]){
    int n = 0;
    
    printf("FIBONACCI\nIngrese un número entre 0 y 100:");
    scanf("%d", &n); 

    if(n >= 0 && n <= 100){
        //realizamos el fibonacci

        pthread_t threadsID[n+1]; //arreglo de ids
        int rc, t;
        struct threadParameters params[n+1]; //arreglo de parametros para cada hilo
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_JOINABLE);

        for(t = 0; t <= n; t++){
            //asignar id al hilo
            params[t].id = t;
            //creamos hilo
            rc = pthread_create(&threadsID[t], &attr, fibonacci, (void *) &params[t]);
            
            if(rc != 0){
                printf("ERROR: codigo de retorno de desde pthread_create %d \n", rc);
                exit(-1);
            }     
        }
        for (int i = 0; i <= n; i++) {
            pthread_join(threadsID[i], NULL);

            //resultado del fibonacci
            if (i == 0 || i == 1) { //caso base
               printf("F%d = %lld\n", params[i].id, params[i].result);
            } else {//caso c >= 2
                printf("F%d = F%d + F%d = %lld + %lld = %lld\n", i, i-1, i-2, params[i-1].result, params[i-2].result, params[i].result);
            }
            
        }

        pthread_attr_destroy (&attr);
        pthread_exit(NULL);	
    }else{
        printf("ERROR: número incorrecto, escriba un número entre 0 y 100\n");
        exit(-1);
    }
    return 0;
 }