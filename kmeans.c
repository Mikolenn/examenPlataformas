#include "kmeans.h"

// funcion para importar los datos
obs* importData(char* ruta, int* cant)
{
    FILE* archivo;              // se crea una variable para manerar el archivo a leer
    archivo= fopen(ruta, "r");  // se abre el archivo en modo lectura

    // se definen las varibles necesarias para importar las componentes de las observaciones
    double cooX= 0.0;
    double cooY= 0.0;
    int i=0;

    // se determina el numero de lineas del archivo, el cual representa el numero de observaciones a importar
    while ( fscanf(archivo, "%lf %lf\n", &cooX, &cooY) != -1 )
    {
        i++;    //contador de las líneas del archivo
    }
    rewind(archivo);    // se regresa el cursor de lectura al inicio del archivo

    *cant= i;

    obs* datos= malloc(i*sizeof(obs));

    i=0;
    while ( fscanf(archivo, "%lf %lf\n", &cooX, &cooY) != -1 )
    {
        (*(datos +i)).coord.x= cooX;
        (*(datos +i)).coord.y= cooY;
        (*(datos +i)).etiq= 0;
        
        i++;
    }
    fclose(archivo);
    return datos; 
}

cent* getInitialCentroids(int K, obs* observ, int cant)
{

    cent* centroides= malloc(K*sizeof(cent));

    for (int i = 0; i < K; i++)
    {
        int random=rand()%cant;

        (*(centroides+i)).coord.x=(*(observ + random)).coord.x;
        (*(centroides+i)).coord.y=(*(observ + random)).coord.y;
        (*(centroides+i)).etiq=i + 1;
    }
    
    return centroides;
}

void kMeans(cent* centr, obs* observ, int cant, int K)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < cant; j++)
        {
            cent cmin= *centr;
            obs ob= *(observ+j);
            
            double Dr= dist(ob, cmin);

            for (int k = 0; k < K; k++)
            {
                cent cn= *(centr+k);
                
                double D= dist(ob, cn);

                if(D < Dr)
                {
                    cmin=cn;
                }
            }
            
            (*(observ+j)).etiq = cmin.etiq;
        }
        
        for (int j = 0; j < K; j++)
        {
            cent cluster= *(centr+j);

            double promX=promediar(observ, cluster, 'x', cant);
            double promY=promediar(observ, cluster, 'y', cant);

            (*(centr+j)).coord.x= promX;
            (*(centr+j)).coord.y= promY;
        } 
    }  
}

void exportClusters(cent* centr, obs* observ, int cant, int K, char* ruta)
{
    FILE* archivo;
    archivo= fopen(ruta, "w");

    for (int i = 0; i < K; i++)
    {
        cent cn= *(centr+i);
        escribirCent(archivo, cn);
    }

    fprintf(archivo, " \n");

    for (int i = 0; i < cant; i++)
    {
        obs ob= *(observ+i);
        escribirObs(archivo, ob);
    }
    fclose(archivo);
}

double dist(obs ob, cent cn)
{
    double dx= ob.coord.x - cn.coord.x;
    double dy= ob.coord.y - cn.coord.y;

    double D= sqrt((dx*dx)+(dy*dy));

    return D;
}

double promediar(obs* observ, cent cluster, char coo, int cant)
{
    double suma=0.0;
    double cont=0.0;
    double prom=0.0;

    switch (coo)
    {
        case 'x':

            for (int i = 0; i < cant; i++)
            {
                obs ob= *(observ +i);
                if (cluster.etiq == ob.etiq)
                {
                    suma= suma + ob.coord.x;
                    cont++;
                }  
            }
            if (cont == 0)
            {
                prom=cluster.coord.x;
            }
            else
            {
                prom= suma/cont;
            }
            break;

        case 'y':
            
            for (int i = 0; i < cant; i++)
            {
                obs ob= *(observ +i);
                if (cluster.etiq == ob.etiq)
                {
                    suma= suma + ob.coord.y;
                    cont++;
                }  
            }
            if (cont == 0)
            {
                prom=cluster.coord.y;
            }
            else
            {
                prom= suma/cont;
            }
            break;
    }    
    return prom;
}

void escribirCent(FILE* archivo, cent centr)
{
    fprintf(archivo, "%.1f %.1f %d\n", centr.coord.x, centr.coord.y, centr.etiq);
}

void escribirObs(FILE* archivo, obs observ)
{
    fprintf(archivo, "%.1f %.1f %d\n", observ.coord.x, observ.coord.y, observ.etiq);
}
