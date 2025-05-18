#pragma once
#include <fstream>
#include <vector>
#include <random>
using namespace std;

class EstudioEmpirico
{
    // Para medir tiempos estudios
    double tiempo_total_B1;
    double tiempo_total_B2;
    double tiempo_total_BInter;
    double mejor_tiempo_B1;
    double peor_tiempo_B1;
    double mejor_tiempo_B2;
    double peor_tiempo_B2;
    double mejor_tiempo_BInter;
    double peor_tiempo_BInter;
    double tiempo_medio_B1;
    double tiempo_medio_B2;
    double tiempo_medio_BInter;
    // Numero de busquedas
    const int N_BUSQUEDAS;
    // Talla inicial
    const int TALLA_INICIAL;
    // Talla final
    const int TALLA_FINAL;
    // Incremento entre iteraciones de la talla
    const int TALLA_INCREMENTO;
    mt19937 gen;                        // generador de números aleatorio basado en el algoritmo Mersenne Twister 19937

    /**
     * Resetea los tiempos de búsqueda a sus valores iniciales.
     */
    void reseteaTiempos();

    
    /**
     * Escribe la primera línea en el archivo logico con formato:
     * talla vector;Binario1;Binario2;Interpolacion
     * donde cada algoritmo tiene mejor, peor y tiempo medio
     */
    void escribePrimeraLineaExcel(ofstream& archivo);

    /**
     * Escribe una linea en el archivo logico con formato:
     * talla vector;Binario1;Binario2;Interpolacion
     * donde cada algoritmo tiene mejor, peor y tiempo medio
     */
    void escribeLineaExcel(ofstream& archivo, const int& talla);

public:
    /**
     * Constructor para inicializar el estudio empírico.
     */
    EstudioEmpirico(int nBusquedas, int tallaInicial, int tallaFinal, int tallaIncremento, random_device& rd)
        : N_BUSQUEDAS(nBusquedas), TALLA_INICIAL(tallaInicial), TALLA_FINAL(tallaFinal), TALLA_INCREMENTO(tallaIncremento) {
            reseteaTiempos();
            gen = mt19937(rd());  // establecemos la semilla rd()
        }

    /**
     * Ordena un vector utilizando el algoritmo de ordenación quicksort.
     * Con este método podemos modificar el algoritmo de ordenación de los estudios empíricos
     */
    static void ordenaVector(vector<int>& vector);


    /**
     * Función para realizar un estudio empírico con arrays vacíos.
     */
    void ArrayVacio();
    
    /**
     * Función para realizar un estudio empírico con un solo elemento en el vector.
     */
    void Array1Elemento();
    
    /**
     * Función para realizar un estudio empírico con vectores aleatorios con números repetidos.
     * 
     * Esta función mide el tiempo de búsqueda de diferentes algoritmos en vectores de tamaño variable.
     */
    void Repetidos();
    
    /**
     * Función para realizar un estudio empírico el elemento a buscar en una de las tres opciones que indica el parámetro.
     * @param opcion Indica la ubicación del elemento a buscar: 0 para principio, 1 para centro, 2 para final.
     */
    void LimitesCentro(int opcion); 
    
    /**
     * Función para comprobar si algoritmo BusquedaBinaria2 realmente encuentra la primera ocurrencia de un elemento en un vector.
     * 
     */
    void comprobarPrimeraOcurrencia();
    
    /**
     * Función para realizar un estudio empírico con vectores aleatorios.
     * 
     * Esta función mide el tiempo de búsqueda de diferentes algoritmos en vectores de tamaño variable.
     * @param opcion Tipo de distribución para generar valores aleatorios (0: uniforme, 1: exponencial, 2: x^2)
     */
    void Aleatorio(int opcion);

    /**
     * Función para realizar un estudio empírico comprobando la 
     * diferencia entre las implementaciones recursivas e iterativas.
     */
    void recursivosVsIterativos();

    /**
     * Función para comparar el rendimiento de Búsqueda Binaria 1 y Búsqueda Interpolada.
     * @param tipoAlgoritmo Indica si se utilizan los algoritmos recursivos o iterativos (0: Recursivo, 1: Iterativo)
     * @param opcion Tipo de distribución para generar valores aleatorios (0: uniforme, 1: exponencial, 2: x^2)
     */
    void B1vsBInter(int tipoAlgoritmo, int opcion);


    // --------------------------------------------------- mergesort ---------------------------------------------------

    /**
     * Función para realizar un estudio empírico para determinar el valor óptimo de K en Mergesort Híbrido.
     */
    void determinarKOptimo();
};



