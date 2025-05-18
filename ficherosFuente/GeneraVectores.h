#pragma once

#include <random>
using namespace std;

/**
 * Clase para generar vectores aleatorios.
 */
class GeneraVectores
{

public :
    // Función para generar un vector de n elementos aleatorios sin números repetidos
    static vector<int> NoRepes(int n, mt19937 &gen);

    // Función para generar un vector de n elementos con distribución exponencial
    static vector<int> Exponencial(int n, mt19937 &gen);
    
    // Función para generar un vector de n elementos con distribución cuadrática
    static vector<int> XCuadrado(int n, mt19937 &gen);
    
    // Función para generar un vector de n elementos aleatorios con números repetidos
    static vector<int> ConRepes(int n, mt19937 &gen);

    // Función para generar un vector de n elementos aleatorios con números repetidos
    // Devuelve el índice del primer elemento repetido
    static vector<int> ConRepes(int n, mt19937 &gen, int &iPrimElemRepe);
};
