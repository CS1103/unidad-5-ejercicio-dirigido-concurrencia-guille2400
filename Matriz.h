//
// Created by sanch on 12/1/2019.
//

#ifndef PD_POO2_MATRIZ_H
#define PD_POO2_MATRIZ_H
#include<vector>
#include <iostream>
#include <sys/time.h>
#define NUM_HILOS 2
using namespace std;


template <typename T>
vector<vector<T>> m1;
template <typename T>
vector<vector<T>> m2;
template <typename T>
vector<vector<T>> m3;



template<typename P>
class Matriz {
public:
    int filas{}, columnas{};
    vector<vector<P>> matriz;
    Matriz() = default;
    Matriz(int filas, int columnas) : filas{filas}, columnas{columnas}{}
    void fill_Matriz(vector<P>&);
    void print_Matriz();
    Matriz<P> operator * (Matriz<P> m);

};

template<typename P>
void Matriz<P>::fill_Matriz( vector<P> &v)
{
    for (auto it = v.begin() ; it < v.end();)
    {
        for(auto i=0;i<filas;i++)
        {
            vector<P> vec;
            for(int j=0;j<columnas;j++)
            {
                //Guardar valores de columnas
                vec.push_back(*it);
                it++;
            }
            //Guardar en el vector de vectores
            matriz.push_back(vec);
        }

    }
}


template<typename P>
void Matriz<P>::print_Matriz()
{
    for(int i=0;i<filas;i++)
    {
        for(int j=0;j<columnas;j++)
        {
            // at da referencia a la posicion
            cout<<matriz.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}

struct datos {
    long thread_id;
    int num_filas1;
    int num_columnas1;
    int num_filas2;
    int num_columnas2;
};

struct datos datos_pasar[NUM_HILOS];


template <typename T>
void* parallel_Multiplication(void* parametros) {

    int j, filas1, columnas1, columnas2,z;
    long i, lim_inf, lim_sup;
    long t;
    struct datos* mis_datos;
    mis_datos=(struct datos*)parametros;
    t = mis_datos->thread_id;
    filas1 = mis_datos->num_filas1;
    columnas1 = mis_datos->num_columnas1;
    columnas2 = mis_datos->num_columnas2;

    if(filas1%NUM_HILOS != 0 && t==NUM_HILOS-1 )
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS) +1;
    }
    else
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS);
    }

    T sum=0;

    for (i = lim_inf; i < lim_sup; i++) {
        for (j = 0; j < columnas2; j++) {
            for (z = 0; z < columnas1; z++) {
                sum += m1<T>[i][z]*m2<T>[z][j];
            }
            m3<T>[i][j]=sum;
            sum=0;
        }
    }

    pthread_exit(nullptr);
}



template<typename P>
Matriz<P> Matriz<P>::operator * (Matriz<P> m)
{

    if(columnas == m.filas )
    {
        Matriz<P> R =Matriz<P>(filas,m.columnas);
        for(int i=0;i<filas;i++)
        {
            vector<P> a;
            for(int j=0;j<m.columnas;j++){
                a.push_back(0);
            }
            m3<P>.push_back(a);
        }

        m1<P>  =matriz;
        m2<P>  =m.matriz;

        int rc;
        long t;
        void* status;

        struct timeval start;
        struct timeval finish;


        pthread_t hilos[NUM_HILOS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        gettimeofday(&start, 0);

        for (t = 0;t < NUM_HILOS; t++) {
            datos_pasar[t].thread_id=t;
            datos_pasar[t].num_filas1=filas;
            datos_pasar[t].num_columnas1=columnas;
            datos_pasar[t].num_filas2=m.filas;
            datos_pasar[t].num_columnas2=m.columnas;
            printf("Se crea el hilo %ld \n",t);

            rc = pthread_create(&hilos[t],&attr,parallel_Multiplication<P>,(void*)&datos_pasar[t]);

            if (rc) {
                printf("Error con codigo: %d \n",rc);
                exit(-1);
            }


        }

        pthread_attr_destroy(&attr);

        for(t=0;t<NUM_HILOS;t++) {
            rc = pthread_join(hilos[t],&status);
            if (rc) {
                printf("Error con codigo: %d \n",rc);
                exit(-1);
            }
        }
        gettimeofday(&finish, 0);
        cout<<endl;
        R.matriz = m3<P>;
        R.print_Matriz();

        pthread_exit(nullptr);

    }
    else
        throw runtime_error("Multiplicacion invalida");



}

#endif //PD_POO2_MATRIZ_H
