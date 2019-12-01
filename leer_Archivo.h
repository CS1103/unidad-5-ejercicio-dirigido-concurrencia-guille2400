//
// Created by sanch on 12/1/2019.
//

#ifndef PD_POO2_LEER_ARCHIVO_H
#define PD_POO2_LEER_ARCHIVO_H
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include "Matriz.h"
using namespace std;

template <typename T>
void lectura(const string &fileName, Matriz<T> &m1_1, Matriz<T> &m2_1) {

    int n=0, n2=0, m=0, m2=0, contador=0;
    T a;

    vector<T> num;
    vector<T> num2;

    ifstream inFile(fileName);

    if (inFile.is_open()) {

        string linea;

        //Obtiene la primera linea y lo guarda del archivo.
        while (getline(inFile, linea)) {
            istringstream iss(linea);
            vector<string> parts((istream_iterator<string>(iss)), istream_iterator<string>());
            if (contador == 0) {
                n = stoi(parts[0]);
                m = stoi(parts[1]);
            }

            if (0 < contador && contador <= n) {
                for (auto &part : parts) {
                    a = stod(part);
                    num.push_back(a);
                }
            }

            if (contador == (n + 1)) {
                n2 = stoi(parts[0]);
                m2 = stoi(parts[1]);
            }

            if ((contador > (n + 1))) {
                for (auto &part : parts) {
                    a = stod(part);
                    num2.push_back(a);
                }
            }

            contador++;
        }

        m1_1.filas=n;
        m1_1.columnas=m;
        m2_1.filas=n2;
        m2_1.columnas=m2;


    } else
        cout<<"ERROR";

    inFile.close();
    m1_1.fill_Matriz(num);
    m1_1.fill_Matriz(num2);
}
#endif //PD_POO2_LEER_ARCHIVO_H
