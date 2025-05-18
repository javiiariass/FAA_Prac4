#pragma once
#include <vector>
using namespace std;

class AlgoritmosBusqueda
{

public:
    /**
     * @brief Búsqueda Secuencial implementada anteriores practicas
     * Esta implementación de búsqueda secuencial busca un elemento en un vector.
     * Devuelve el índice del elemento si se encuentra, de lo contrario devuelve -1.
     * @param vec Vector de enteros donde se realizará la búsqueda.
     * @param target Elemento que se desea buscar en el vector.
     * @return Índice del elemento encontrado o -1 si no se encuentra.
     */
    static int busquedaSecuencial(const vector<int> &vec, int target);

    /**
     * @brief Busqueda Binaria
     * Esta implementación de búsqueda binaria busca un elemento en un vector ordenado.
     * Aplica recursividad
     * @param A Vector de enteros donde se realizará la búsqueda.
     * @param izq Índice izquierdo del vector.
     * @param der Índice derecho del vector.
     * @param x Elemento que se desea buscar en el vector.
     * @return Índice del elemento encontrado o -1 si no se encuentra.
     */
    static int busquedaBinaria1(vector<int> A, int izq, int der, int x);

    /**
     * @brief Búsqueda Binaria con Indice de primera ocurrencia
     * Esta implementación de búsqueda binaria con indice de primera
     * ocurrencia busca un elemento en un vector ordenado.
     * En caso de que haya varios elementos repetidos, devuelve el indice
     * de la primera ocurrencia.
     * Aplica recursividad
     * @param A Vector de enteros donde se realizará la búsqueda.
     * @param izq Índice izquierdo del vector.
     * @param der Índice derecho del vector.
     * @param x Elemento que se desea buscar en el vector.
     * @return Índice del elemento encontrado o -1 si no se encuentra.
     */
    static int busquedaBinaria2(vector<int> A, int izq, int der, int x);

    /**
     * @brief Búsqueda Binaria por Interpolación
     * Esta implementación de búsqueda binaria por interpolación busca un elemento en un vector ordenado.
     * Es optima en distribuciones homogeneas.
     * Aplica recursividad.
     * @param A Vector de enteros donde se realizará la búsqueda.
     * @param izq Índice izquierdo del vector.
     * @param der Índice derecho del vector.
     * @param x Elemento que se desea buscar en el vector.
     * @return Índice del elemento encontrado o -1 si no se encuentra.
     */
    static int busquedaBinariaInterpolacion(vector<int> A, int izq, int der, int x);

    /**
     * @brief Versión Iterativa de busquedaBinaria1 (Estándar).
     * Busca un elemento 'x' en un vector ordenado 'A' dentro del rango [izq, der].
     * Retorna el índice si lo encuentra, -1 si no.
     * @param A El vector de enteros ordenado.
     * @param izq El índice izquierdo del rango de búsqueda.
     * @param der El índice derecho del rango de búsqueda.
     * @param x El elemento a buscar.
     * @return El índice del elemento si se encuentra, -1 si no.
     */
    static int busquedaBinaria1Iterativa(vector<int> A, int izq, int der, int x);

    /**
     * @brief Versión Iterativa de busquedaBinaria2 (Primera Ocurrencia).
     * Busca la primera ocurrencia de un elemento 'x' en un vector ordenado 'A'
     * dentro del rango [izq, der].
     * Retorna el índice de la primera ocurrencia si la encuentra, -1 si no.
     * @param A El vector de enteros ordenado.
     * @param izq El índice izquierdo del rango de búsqueda.
     * @param der El índice derecho del rango de búsqueda.
     * @param x El elemento a buscar.
     * @return El índice de la primera ocurrencia si se encuentra, -1 si no.
     */
    static int busquedaBinaria2Iterativa(vector<int> A, int izq, int der, int x);
    
    /**
     * @brief Versión Iterativa de busquedaBinariaInterpolacion.
     * Busca un elemento 'x' en un vector ordenado 'A' dentro del rango [izq, der]
     * utilizando la búsqueda por interpolación.
     * Retorna el índice si lo encuentra, -1 si no.
     * @param A El vector de enteros ordenado.
     * @param izq El índice izquierdo del rango de búsqueda.
     * @param der El índice derecho del rango de búsqueda.
     * @param x El elemento a buscar.
     * @return El índice del elemento si se encuentra, -1 si no.
     */
    static int busquedaBinariaInterpolacionIterativa(vector<int> A, int izq, int der, int x);


    /**
     * Algortimo del ejercicio 5. Busca los elementos no repetidos en un vector y los devuelve en un nuevo vector.
     * @param A Vector de enteros donde se realizará la búsqueda.
     * @return Un vector de enteros con los elementos no repetidos.
     * 
     */
    static vector<int> busquedaNoRepetidos(vector<int> A);

    /**
     * Algortimo del ejercicio 5. Busca los elementos no repetidos en un vector y los devuelve en un nuevo vector.
     * @param array Vector de enteros donde se realizará la búsqueda.
     * @param k Número de repeticiones que se desea encontrar.
     * @return Un vector de enteros con los elementos no repetidos.
     * 
     */
    static vector<int> ElementosConKRepeticiones(const vector<int> &array, int k);
};