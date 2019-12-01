#include <iostream>
#include "Matriz.h"
#include "leer_Archivo.h"
using namespace std;
int main()
{
    Matriz<int> m1;
    Matriz<int> m2;
    Matriz<int> matriz_Resultado;
    lectura("ejemplo1.txt", m1, m2);
    cout<<endl;
    cout << "Imprimir matriz m1" << endl;
    m1.print_Matriz();
    cout << endl;
    cout << "Imprimir matriz m2" << endl;
    m1.print_Matriz();
    cout << endl;
    cout << "Multiplicación de m1 x m2: " << endl;
    matriz_Resultado = m1*m2;
    matriz_Resultado.print_Matriz();
    cout << endl;
    return 0;
}