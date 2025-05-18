#include "GeneraVectores.h"
#include "AlgoritmosBusqueda.h"
#include <iostream>

/**
 * Función para generar un vector de n elementos aleatorios sin números repetidos.
 * 
 * @param n Número de elementos en el vector.
 * @param gen Generador de números aleatorios.
 * @return Un vector de enteros aleatorios sin repeticiones.
 */
vector<int> GeneraVectores::NoRepes(int n, mt19937 &gen)
{
    vector<int> vec(n);
    for (int i = 0; i < n; ++i)
    {
        vec[i] = i + 1; // Llena el vector con números del 1 al n
    }
    shuffle(vec.begin(), vec.end(), gen); // Mezcla los números aleatoriamente usando el algoritmo de Fisher-Yates
    return vec;
}


vector<int> GeneraVectores::Exponencial(int n, mt19937 &gen){
    exponential_distribution<double> distrib(5.0);   // esta distribucion solo toma double, no integers
    //vector<double> vec_double(n); // Vector temporal para doubles
    double generadoAux;
    vector<int> vec(n); // Vector final de enteros
    
    // Generar números double con distribución exponencial
    for (int i = 0; i < n; ++i) {
        generadoAux = distrib(gen) * n; // Para que los valores no estén unicamente cerca de 0
        if(generadoAux > INT_MAX){ // Si el generado es mayor que el límite de un entero.
            vec.at(i) = INT_MAX - i; // límite - iteración actual, para que no sean todos el mismo.
        } else {
            vec.at(i) = (int)(round(generadoAux)); // Redondear al más cercano antes de truncar 
        }
        
    }

    return vec;
}

vector<int> GeneraVectores::XCuadrado(int n, mt19937 &gen){
    chi_squared_distribution<double> distrib(10.0);   // esta distribucion solo toma double, no integers
    //vector<double> vec_double(n); // Vector temporal para doubles
    double generadoAux;
    vector<int> vec(n); // Vector final de enteros
    
    // Generar números double con distribución exponencial
    for (int i = 0; i < n; ++i) {
        generadoAux = distrib(gen) * 10; // Para que los valores no estén unicamente cerca de 0
        if(generadoAux > INT_MAX){ // Si el generado es mayor que el límite de un entero.
            vec.at(i) = INT_MAX - i; // límite - iteración actual, para que no sean todos el mismo.
        } else {
            vec.at(i) = (int)(round(generadoAux)); // Redondear al más cercano antes de truncar 
        }
        
    }

    return vec;
}



/**
 * Función para generar un vector de n elementos aleatorios con números repetidos.
 * 
 * @param n Número de elementos en el vector.
 * @param gen Generador de números aleatorios.
 * @return Un vector de enteros aleatorios con repeticiones.
 */
vector<int> GeneraVectores::ConRepes(int n, mt19937 &gen)
{
    // Distribución uniforme entre 1 y n*10 para valores del vector
    uniform_int_distribution<int> distrib(1, n*10); 

    vector<int> vec(n);
    
    for (int i = 0; i < n; ++i)
    {
        
        // Si un aleatorio generado es divisible entre 7, repetimos elemento anterior.
        // Si no, generamos nuevo aleatorio
        if(i != 0 && gen()%7 == 0){ // El primer elemento no puede copiar al anterior
            
            vec.at(i) = vec.at(i-1);
        }else{
            vec.at(i) = distrib(gen); // Llena el vector con números aleatorios de la distribución
        }
    }
    // Hay que ordenar el vector después, no pasa nada si los repetidos están juntos.
    return vec;
}

/**
 * Función para generar un vector de n elementos aleatorios con números repetidos.
 * 
 * @param n Número de elementos en el vector.
 * @param gen Generador de números aleatorios.
 * @param iPrimElemRepe Índice del primer elemento repetido.
 * @return Un vector de enteros aleatorios con repeticiones.
 */
vector<int> GeneraVectores::ConRepes(int n, mt19937 &gen, int &PrimElemRepe)
{
    // Distribución uniforme entre 1 y n*10 para valores del vector
    uniform_int_distribution<int> distrib(1, n*10); 
    bool repetido = false;
    vector<int> vec(n);
    
    for (int i = 0; i < n; ++i)
    {
        
        // Si un aleatorio generado es divisible entre 7, repetimos elemento anterior.
        // Si no, generamos nuevo aleatorio
        if(i != 0 && gen()%7 == 0){ // El primer elemento no puede copiar al anterior
            vec.at(i) = vec.at(i-1);
            // Guardo el indice del primer elemento repetido
            if(!repetido){
                PrimElemRepe = vec.at(i); // Guardamos el valor actual
                repetido = true;
            }
        }else{
            vec.at(i) = distrib(gen); // Llena el vector con números aleatorios de la distribución
        }
    }

    // ordenamos el vector
    // Método que hace uso de quicksort para ordenar vector
    sort(vec.begin(), vec.end());

    // Buscamos primera ocurrencia del vector con busqueda secuencial
    PrimElemRepe = AlgoritmosBusqueda::busquedaSecuencial(vec, PrimElemRepe); 

    if (PrimElemRepe == -1) {
        cerr << "No se encontró el primer elemento repetido." << endl;
        exit(-1); // abortamos programa
    }

    return vec;
}