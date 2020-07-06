#if !defined(kmeans)
#define kmeans

    // se incluyen las librerias a utilizar
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <time.h>

    // se crea el tipo de dato p2D, el cual contiene dos variables tipo double representando las coordenadas de un punto en 2D
    typedef 
    struct punto2D
        {
            double x;
            double y;
        }
    p2D;
    // se crea el tipo de dato obs, el cual contiene un p2D y un entero. Se emplea para representar las observaciones
    typedef
    struct observacion
        {
            p2D coord;
            int etiq;
        }
    obs;
    // se crea el tipo de dato cent, el cual contiene un p2D y un entero. Se emplea para representar los centroides y los clusters
    typedef
    struct centroide
        {
            p2D coord;
            int etiq;
        }
    cent;

    // se incluyen las firmas de todas las funciones utilizadas
    // el cuerpo de las funciones esta en el archivo kmeans.c
    obs* importData(char* ruta, int* cant);
    cent* getInitialCentroids(int K, obs* observ, int cant);
    void kMeans(cent* centr, obs* observ, int cant, int K);
    void exportClusters(cent* centr, obs* observ, int cant, int K, char* ruta);
    double dist(obs ob, cent cn);
    double promediar(obs* observ, cent cluster, char coo, int cant);
    void escribirCent(FILE* archivo, cent centr);
    void escribirObs(FILE* archivo, obs observ);

#endif