#include "kmeans.h"

int main(int argc, char const *argv[])
{
    // se inicializa la semilla de los números aleatorios
    srand(time(NULL));
    //se captura el numero de clusters ingresado por el usuario
    int K= atoi(argv[1]);
    // se crea la variable para guardar el numero de observaciones importadas
    int cant=0;
    // se crean las variables con los nombres de los archivos a utilizar
    char* rutaOrigen= "data.txt";
    char* rutaDestino= "clusters.txt";

    // se importan las observaciones en un bloque de momeria, cuya direccion inicial está en observ
    obs* observ= importData(rutaOrigen, &cant);
    // se cren los clusters iniciales en base a lo que el usuario desea y se guardan en un bloque de memoria
    // la direccion inicial del bloque se encuentra en centr
    cent* centr= getInitialCentroids(K, observ, cant);

    // se ejecuta el algoritmo K-Means
    kMeans(centr, observ, cant, K);

    // se escriben las observaciones en un archivo, incluyendo las etiquetas y los clusters
    exportClusters(centr, observ, cant, K, rutaDestino);

    // se libera el espacio en memoria de los dos bloque creados
    free(observ);
    free(centr);

    return 0;
}

