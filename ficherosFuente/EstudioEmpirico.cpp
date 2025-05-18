#include "EstudioEmpirico.h"
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <limits>
#include <iomanip>
#include "AlgoritmosBusqueda.h"
#include "AlgoritmosOrdenacion.h"
#include "GeneraVectores.h"
#include "ExtraFunciones.h"

/**
 * Resetea los tiempos de búsqueda a sus valores iniciales.
 */
void EstudioEmpirico::reseteaTiempos()
{

    tiempo_total_B1 = 0.0;
    mejor_tiempo_B1 = numeric_limits<double>::max(); // Se inicializa con el valor más grande posible (DBL_MAX en <cfloat>).
    peor_tiempo_B1 = 0.0;
    tiempo_medio_B1 = 0.0;

    tiempo_total_B2 = 0.0;
    mejor_tiempo_B2 = numeric_limits<double>::max(); // Se inicializa con el valor más grande posible (DBL_MAX en <cfloat>).
    peor_tiempo_B2 = 0.0;
    tiempo_medio_B2 = 0.0;

    tiempo_total_BInter = 0.0;
    mejor_tiempo_BInter = numeric_limits<double>::max(); // Se inicializa con el valor más grande posible (DBL_MAX en <cfloat>).
    peor_tiempo_BInter = 0.0;
    tiempo_medio_BInter = 0.0;
}

/**
 * Ordena un vector utilizando el algoritmo de ordenación quicksort.
 * Con este método podemos modificar el algoritmo de ordenación de los estudios empíricos
 */
void EstudioEmpirico::ordenaVector(vector<int> &vector)
{
    // Internamente usa quicksort
    sort(vector.begin(), vector.end());
    // podemos usar cualquier algoritmo de ordenación que implementemos
    // AlgoritmosOrdenacion::MergesortHibrido(vector, 10);
}

/**
 * Escribe la primera línea en el archivo logico con formato:
 * talla vector;Binario1;Binario2;Interpolacion
 * donde cada algoritmo tiene mejor, peor y tiempo medio
 */
void EstudioEmpirico::escribePrimeraLineaExcel(ofstream &archivo)
{
    archivo << "Tamano del Vector;B1:Mejor Tiempo (us); B1:Peor Tiempo(us); B1:Tiempo Medio(us);;"
            << "B2:Mejor Tiempo (us); B2:Peor Tiempo(us); B2:Tiempo Medio(us);;"
            << "BInter:Mejor Tiempo (us); BInter:Peor Tiempo(us); BInter:Tiempo Medio(us)" << endl;
}

/**
 * Escribe una linea en el archivo logico con formato:
 * talla vector;Binario1;Binario2;Interpolacion
 * donde cada algoritmo tiene mejor, peor y tiempo medio
 */
void EstudioEmpirico::escribeLineaExcel(ofstream &archivo, const int &talla)
{
    archivo << talla << ";" << mejor_tiempo_B1 << ";" << peor_tiempo_B1 << ";" << tiempo_medio_B1 << ";;"
            << mejor_tiempo_B2 << ";" << peor_tiempo_B2 << ";" << tiempo_medio_B2 << ";;"
            << mejor_tiempo_BInter << ";" << peor_tiempo_BInter << ";" << tiempo_medio_BInter << endl;
}

/**
 * Función para realizar un estudio empírico con arrays vacíos.
 */
void EstudioEmpirico::ArrayVacio()
{
    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, "resultadosArrayVacio");
    escribePrimeraLineaExcel(archivo);
    // Aunque la talla de igual porque el vector está vacío.
    // Iteramos las mismas veces que el resto de busquedas para tener un resultado más "exacto"
    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {
        // Generamos el vector vacio
        vector<int> vectorVacio(0);

        // Estos algoritmos de búsqueda hacen uso del vector ordenado
        // Método que hace uso de quicksort para ordenar vector
        // sort(vectorAleatorio.begin(), vectorAleatorio.end());

        reseteaTiempos();

        uniform_int_distribution<int> distrib(1, n); // Distribución uniforme entre 1 y n

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 y n
            int encontrado;

            double tiempo_busqueda;

            // Binaria1
            auto inicio_B1 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorVacio, 0, vectorVacio.size(), valorAleatorio);
            auto fin_B1 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
            tiempo_total_B1 += tiempo_busqueda;

            mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
            peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

            // Binaria2
            auto inicio_B2 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorVacio, 0, vectorVacio.size(), valorAleatorio);
            auto fin_B2 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2 - inicio_B2).count(); // Calcular el coste en microsegundos
            tiempo_total_B2 += tiempo_busqueda;

            mejor_tiempo_B2 = min(mejor_tiempo_B2, tiempo_busqueda);
            peor_tiempo_B2 = max(peor_tiempo_B2, tiempo_busqueda);

            // BinariaInterpolacion
            auto inicio_BInter = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorVacio, 0, vectorVacio.size(), valorAleatorio);
            auto fin_BInter = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
            tiempo_total_BInter += tiempo_busqueda;

            mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
            peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_B2 = tiempo_total_B2 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        escribeLineaExcel(archivo, n);
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo 'resultadosArrayVacio.csv'." << endl;
}

/**
 * Función para realizar un estudio empírico con un solo elemento en el vector.
 */
void EstudioEmpirico::Array1Elemento()
{
    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, "resultadosArray1Elemento");
    escribePrimeraLineaExcel(archivo);

    // Aunque la talla de igual porque el vector tiene un elemento.
    // Iteramos las mismas veces que el resto de busquedas para tener un resultado más "exacto"
    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {

        // Inicializa el generador de números aleatorios

        uniform_int_distribution<int> distrib(1, n); // Distribución uniforme entre 1 y n

        // Generamos el vector con un elemento
        vector<int> vectorUnicoElemento(1);
        vectorUnicoElemento.at(0) = distrib(gen);

        // Estos algoritmos de búsqueda hacen uso del vector ordenado
        // Método que hace uso de quicksort para ordenar vector
        // sort(vectorAleatorio.begin(), vectorAleatorio.end());

        reseteaTiempos();

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            // De manera aleatoria(pero con más probabilidades que antes), hacemos que el
            // elemento a buscar sea el único elemento del array
            int valorAleatorio;
            // Si el aleatorio generado es divisible entre 7 -> hacemos que sea el elemento del array
            if (gen() % 7 == 0)
                valorAleatorio = vectorUnicoElemento.at(0); // Primer elemento del vector -> igual que vectorUnicoElemento[0]
            else                                            // Si no, hacemos que sea uno aleatorio acotado en el rango
                valorAleatorio = distrib(gen);

            int encontrado;

            double tiempo_busqueda;

            // Binaria1
            auto inicio_B1 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorUnicoElemento, 0, vectorUnicoElemento.size() - 1, valorAleatorio);
            auto fin_B1 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
            tiempo_total_B1 += tiempo_busqueda;

            mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
            peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);
            // cout << " Completado B1  " << i + 1 << " de " << N_BUSQUEDAS << endl;
            //  Binaria2
            auto inicio_B2 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorUnicoElemento, 0, vectorUnicoElemento.size() - 1, valorAleatorio);
            auto fin_B2 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2 - inicio_B2).count(); // Calcular el coste en microsegundos
            tiempo_total_B2 += tiempo_busqueda;

            mejor_tiempo_B2 = min(mejor_tiempo_B2, tiempo_busqueda);
            peor_tiempo_B2 = max(peor_tiempo_B2, tiempo_busqueda);

            // cout << " Completado B2  " << i + 1 << " de " << N_BUSQUEDAS << endl;
            //  BinariaInterpolacion
            auto inicio_BInter = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorUnicoElemento, 0, vectorUnicoElemento.size() - 1, valorAleatorio);
            auto fin_BInter = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
            tiempo_total_BInter += tiempo_busqueda;

            mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
            peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
            // cout << " Completado BInter  " << i + 1 << " de " << N_BUSQUEDAS << endl;
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_B2 = tiempo_total_B2 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        escribeLineaExcel(archivo, n);
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo 'resultadosArray1Elemento.csv'." << endl;
}

/**
 * Función para realizar un estudio empírico con vectores aleatorios con números repetidos.
 *
 * Esta función mide el tiempo de búsqueda de diferentes algoritmos en vectores de tamaño variable.
 */
void EstudioEmpirico::Repetidos()
{
    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, "resultadosConRepetidos");
    escribePrimeraLineaExcel(archivo);

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {
        // Generamos el vector
        vector<int> vectorAleatorio = GeneraVectores::ConRepes(n, gen);

        ordenaVector(vectorAleatorio);

        reseteaTiempos();

        uniform_int_distribution<int> distrib(1, n); // Distribución uniforme entre 1 y n

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            // int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 y n

            // De manera aleatoria(pero con más probabilidades que antes), hacemos que el
            // elemento a buscar sea el único elemento del array
            int valorAleatorio;

            // Si el aleatorio generado es divisible entre 7 -> hacemos que sea el elemento del vector
            if (gen() % 7 == 0)
            {
                uniform_int_distribution<int> distrib(0, vectorAleatorio.size() - 1);
                valorAleatorio = vectorAleatorio.at(distrib(gen)); // Le asignamos el valor de un elemento del vector.
            }
            else                               // Si no, hacemos que sea uno aleatorio acotado en el rango
                valorAleatorio = distrib(gen); // Puede ser o no un elemento del vector

            int encontrado;

            double tiempo_busqueda;

            // Binaria1
            auto inicio_B1 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B1 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
            tiempo_total_B1 += tiempo_busqueda;

            mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
            peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

            // Binaria2
            auto inicio_B2 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B2 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2 - inicio_B2).count(); // Calcular el coste en microsegundos
            tiempo_total_B2 += tiempo_busqueda;

            mejor_tiempo_B2 = min(mejor_tiempo_B2, tiempo_busqueda);
            peor_tiempo_B2 = max(peor_tiempo_B2, tiempo_busqueda);

            // BinariaInterpolacion
            auto inicio_BInter = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_BInter = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
            tiempo_total_BInter += tiempo_busqueda;

            mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
            peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_B2 = tiempo_total_B2 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        escribeLineaExcel(archivo, n);
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo 'resultadosConRepetidos.csv'." << endl;
}

/**
 * Función para realizar un estudio empírico en el que el elemento a buscar está en una de las tres opciones que indica el parámetro.
 * @param opcion Indica la ubicación del elemento a buscar: 0 para principio, 1 para centro, 2 para final.
 */
void EstudioEmpirico::LimitesCentro(int opcion)
{

    // Early return
    if (opcion < 0 || opcion > 2)
        return;

    // Guardamos en distintos archivos en función del elemento a buscar
    string nombreArchivo;

    if (opcion == 0)
    {
        nombreArchivo = "resultadosElementosPrincipio";
    }
    else if (opcion == 1)
    {
        nombreArchivo = "resultadosElementosMedio";
    }
    else
    {
        nombreArchivo = "resultadosElementosFinal";
    }

    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, nombreArchivo);
    escribePrimeraLineaExcel(archivo);

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {
        // Generamos el vector
        vector<int> vectorAleatorio = GeneraVectores::NoRepes(n, gen);

        ordenaVector(vectorAleatorio);
        reseteaTiempos();

        int valorBusqueda;

        if (opcion == 0)
        {
            // elemento inicial
            valorBusqueda = vectorAleatorio.at(0);
        }
        else if (opcion == 1)
        {
            // elemento central
            valorBusqueda = vectorAleatorio.at(vectorAleatorio.size() / 2);
        }
        else
        {
            // ultimo elemento
            valorBusqueda = vectorAleatorio.at(vectorAleatorio.size() - 1);
        }

        // Realiza N_BUSQUEDAS  y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {

            int encontrado;

            double tiempo_busqueda;

            // Binaria1
            auto inicio_B1 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorBusqueda);
            auto fin_B1 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
            tiempo_total_B1 += tiempo_busqueda;

            mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
            peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

            // Binaria2
            auto inicio_B2 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorBusqueda);
            auto fin_B2 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2 - inicio_B2).count(); // Calcular el coste en microsegundos
            tiempo_total_B2 += tiempo_busqueda;

            mejor_tiempo_B2 = min(mejor_tiempo_B2, tiempo_busqueda);
            peor_tiempo_B2 = max(peor_tiempo_B2, tiempo_busqueda);

            // BinariaInterpolacion
            auto inicio_BInter = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorBusqueda);
            auto fin_BInter = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
            tiempo_total_BInter += tiempo_busqueda;

            mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
            peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_B2 = tiempo_total_B2 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        escribeLineaExcel(archivo, n);
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo '" << nombreArchivo << ".csv'." << endl;
}

/**
 * Función para comprobar si algoritmo BusquedaBinaria2 realmente encuentra la primera ocurrencia de un elemento en un vector.
 *
 */
void EstudioEmpirico::comprobarPrimeraOcurrencia()
{

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {

        uniform_int_distribution<int> distrib(1, n); // Distribución uniforme entre 1 y n

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            // Generamos Un vector de talla n
            int indicePrimeraOcurrencia;
            vector<int> vectorAleatorio = GeneraVectores::ConRepes(n, gen, indicePrimeraOcurrencia);

            int valorBusqueda = vectorAleatorio.at(indicePrimeraOcurrencia);
            // int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 y n

            // De manera aleatoria(pero con más probabilidades que antes), hacemos que el
            // elemento a buscar sea el único elemento del array

            int encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorBusqueda);

            if (encontrado != indicePrimeraOcurrencia)
            {
                cout << "Indice encontrado: " << encontrado
                     << "\nIndice Primera Ocurrencia: " << indicePrimeraOcurrencia << endl;
                cerr << "Error. Un elemento encontrado no coincide con la primera ocurrencia del elemento\n";
                return;
            }
        }
    }

    cout << "Todas las búsquedas han encontrado la primera ocurrencia\n";
}

/**
 * Función para realizar un estudio empírico con vectores aleatorios.
 *
 * Esta función mide el tiempo de búsqueda de diferentes algoritmos en vectores de tamaño variable.
 * @param opcion Tipo de distribución para generar valores aleatorios (0: uniforme, 1: exponencial, 2: x^2)
 */
void EstudioEmpirico::Aleatorio(int opcion)
{
    // early return
    if (opcion < 0 || opcion > 2)
        return;

    string nombreFich;

    if (opcion == 0)
        nombreFich = "resultadosAleatorioUniforme";

    else if (opcion == 1)
        nombreFich = "resultadosAleatorioExponencial";

    else
        nombreFich = "resultadosAleatorioXCuadrado";

    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, nombreFich);
    escribePrimeraLineaExcel(archivo);

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {

        reseteaTiempos();

        // Generamos el vector
        vector<int> vectorAleatorio;
        if (opcion == 0)
        {
            vectorAleatorio = GeneraVectores::NoRepes(n, gen);
        }
        else if (opcion == 1)
        {
            vectorAleatorio = GeneraVectores::Exponencial(n, gen);
        }
        else
            vectorAleatorio = GeneraVectores::XCuadrado(n, gen);

        uniform_int_distribution<int> distrib(1, INT_MAX); // Distribución uniforme entre 1 e INT_MAX

        ordenaVector(vectorAleatorio);

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            // Da igual la distribución del número a buscar
            int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 e INT_MAX
            int encontrado;

            double tiempo_busqueda;

            // Binaria1
            auto inicio_B1 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B1 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
            tiempo_total_B1 += tiempo_busqueda;

            mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
            peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

            // Binaria2
            auto inicio_B2 = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B2 = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2 - inicio_B2).count(); // Calcular el coste en microsegundos
            tiempo_total_B2 += tiempo_busqueda;

            mejor_tiempo_B2 = min(mejor_tiempo_B2, tiempo_busqueda);
            peor_tiempo_B2 = max(peor_tiempo_B2, tiempo_busqueda);

            // BinariaInterpolacion
            auto inicio_BInter = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_BInter = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
            tiempo_total_BInter += tiempo_busqueda;

            mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
            peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_B2 = tiempo_total_B2 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        escribeLineaExcel(archivo, n);
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo '" << nombreFich << ".csv'." << endl;
}

/**
 * Función para comparar el rendimiento de algoritmos recursivos e iterativos.
 * Genera vectores aleatorios +-uniformes
 * Datos exportados a .csv con el formato:
 * talla mejorTiempo Recursivos mejorTiempo Iterativos ...
 * talla tiempoMedio Recursivos tiempoMedio Iterativos ...
 * talla peorTiempo Recursivos peorTiempo Iterativos
 */
void EstudioEmpirico::recursivosVsIterativos()
{
    string nombreFich = "resultadosRecursivosVsIterativos";

    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, nombreFich);
    // Debido a que vamos a estudiar 6 algoritmos, unicamente mediremos el tiempo medio, no tendremos en
    // cuenta ni mejor ni peor tiempo
    /*archivo << "Tamano del Vector;B1R:Mejor Tiempo (us);B2R:Mejor Tiempo (us);BInterR:Mejor Tiempo (us);"
            << "B1I:Mejor Tiempo (us);B2I:Mejor Tiempo (us);BInterI:Mejor Tiempo (us);;"*/

    archivo << "Tamano del Vector;B1R:Tiempo Medio(us);B2R:Tiempo Medio(us);BInterR:Tiempo Medio(us);"
            << "B1I:Tiempo Medio(us);B2I:Tiempo Medio(us);BInterI:Tiempo Medio(us);" << endl; /*<< ";"

            << "Tamano del Vector;B1R:Peor Tiempo(us); B2R:Peor Tiempo(us);BInterR:Peor Tiempo(us); "
            << "Tamano del Vector;B1I:Peor Tiempo(us); B2I:Peor Tiempo(us);BInterI:Peor Tiempo(us); " << endl;*/

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {

        double tiempo_total_B1R = 0.0;
        double tiempo_total_B1I = 0.0;

        double tiempo_total_B2R = 0.0;
        double tiempo_total_B2I = 0.0;

        double tiempo_total_BInterR = 0.0;
        double tiempo_total_BInterI = 0.0;

        // Generamos el vector
        // vector<int> vectorAleatorio;
        // if (opcion == 0)
        // {
        //     vectorAleatorio = GeneraVectores::NoRepes(n, gen);
        // }
        // else if (opcion == 1)
        // {
        //     vectorAleatorio = GeneraVectores::Exponencial(n, gen);
        // }
        // else
        //     vectorAleatorio = GeneraVectores::XCuadrado(n, gen);

        uniform_int_distribution<int> distrib(1, INT_MAX); // Distribución uniforme entre 1 e INT_MAX para elemento a buscar
        vector<int> vectorAleatorio = GeneraVectores::NoRepes(n, gen);

        ordenaVector(vectorAleatorio);

        // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
        for (int i = 0; i < N_BUSQUEDAS; ++i)
        {
            // Da igual la distribución del número a buscar
            int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 e INT_MAX
            int encontrado;

            double tiempo_busqueda;

            // ------------------------------------------------- Recursivas -------------------------------------------------
            // Binaria1
            auto inicio_B1R = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B1R = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1R - inicio_B1R).count(); // Calcular el coste en microsegundos
            tiempo_total_B1R += tiempo_busqueda;

            // Binaria2
            auto inicio_B2R = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B2R = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2R - inicio_B2R).count(); // Calcular el coste en microsegundos
            tiempo_total_B2R += tiempo_busqueda;

            // BinariaInterpolacion
            auto inicio_BInterR = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_BInterR = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInterR - inicio_BInterR).count(); // Calcular el coste en microsegundos
            tiempo_total_BInterR += tiempo_busqueda;

            // ------------------------------------------------- Iterativas -------------------------------------------------
            // Binaria1
            auto inicio_B1I = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B1I = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B1I - inicio_B1I).count(); // Calcular el coste en microsegundos
            tiempo_total_B1I += tiempo_busqueda;

            // Binaria2
            auto inicio_B2I = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinaria2(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_B2I = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_B2I - inicio_B2I).count(); // Calcular el coste en microsegundos
            tiempo_total_B2I += tiempo_busqueda;

            // BinariaInterpolacion
            auto inicio_BInterI = chrono::high_resolution_clock::now();
            encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
            auto fin_BInterI = chrono::high_resolution_clock::now();

            tiempo_busqueda = chrono::duration<double, micro>(fin_BInterI - inicio_BInterI).count(); // Calcular el coste en microsegundos
            tiempo_total_BInterI += tiempo_busqueda;
        }

        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        double tiempo_medio_B1R = tiempo_total_B1R / N_BUSQUEDAS;
        double tiempo_medio_B2R = tiempo_total_B2R / N_BUSQUEDAS;
        double tiempo_medio_BInterR = tiempo_total_BInterR / N_BUSQUEDAS;

        double tiempo_medio_B1I = tiempo_total_B1I / N_BUSQUEDAS;
        double tiempo_medio_B2I = tiempo_total_B2I / N_BUSQUEDAS;
        double tiempo_medio_BInterI = tiempo_total_BInterI / N_BUSQUEDAS;

        archivo << n << ";" << tiempo_medio_B1R << ";" << tiempo_medio_B2R << ";" << tiempo_medio_BInterR << ";"
                << tiempo_medio_B1I << ";" << tiempo_medio_B2I << ";" << tiempo_medio_BInterI << ";" << endl;
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo '" << nombreFich << ".csv'." << endl;
}

/**
 * Función para realizar un estudio empírico con vectores aleatorios.
 *
 * Esta función mide el tiempo de búsqueda de algoritmos B1 y B interpolaicon en vectores de tamaño variable.
 * @param tipoAlgoritmo Indica si se utilizan los algoritmos recursivos o iterativos (0: Recursivo, 1: Iterativo)
 * @param opcion Tipo de distribución para generar valores aleatorios (0: uniforme, 1: exponencial, 2: x^2)
 */
void EstudioEmpirico::B1vsBInter(int tipoAlgoritmo, int opcion)
{
    // early return
    if (opcion < 0 || opcion > 2 || tipoAlgoritmo < 0 || tipoAlgoritmo > 1)
        return;

    string nombreFich = "resultadosB1vsInter";

    if (tipoAlgoritmo == 0)
    {
        nombreFich += "_Recursivo";
    }
    else
    {
        nombreFich += "_Iterativo";
    }

    if (opcion == 0)
        nombreFich += "_Uniforme";

    else if (opcion == 1)
        nombreFich += "_Exponencial";

    else
        nombreFich += "_XCuadrado";

    cout << nombreFich << endl;

    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, nombreFich);

    archivo << "Tamano del Vector;B1:Mejor Tiempo (us); B1:Peor Tiempo(us); B1:Tiempo Medio(us);;"
            << "BInter:Mejor Tiempo (us); BInter:Peor Tiempo(us); BInter:Tiempo Medio(us)" << endl;

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {

        reseteaTiempos();

        // Generamos el vector
        vector<int> vectorAleatorio;
        if (opcion == 0)
        {
            vectorAleatorio = GeneraVectores::NoRepes(n, gen);
        }
        else if (opcion == 1)
        {
            vectorAleatorio = GeneraVectores::Exponencial(n, gen);
        }
        else
            vectorAleatorio = GeneraVectores::XCuadrado(n, gen);

        uniform_int_distribution<int> distrib(1, INT_MAX); // Distribución uniforme entre 1 e INT_MAX

        ordenaVector(vectorAleatorio);

        // ---------------------------------------- Recursiva -----------------------------------
        if (tipoAlgoritmo == 0)
        {

            // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
            for (int i = 0; i < N_BUSQUEDAS; ++i)
            {
                // Da igual la distribución del número a buscar
                int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 e INT_MAX
                int encontrado;

                double tiempo_busqueda;

                // Binaria1
                auto inicio_B1 = chrono::high_resolution_clock::now();
                encontrado = AlgoritmosBusqueda::busquedaBinaria1(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
                auto fin_B1 = chrono::high_resolution_clock::now();

                tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
                tiempo_total_B1 += tiempo_busqueda;

                mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
                peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

                // BinariaInterpolacion
                auto inicio_BInter = chrono::high_resolution_clock::now();
                encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacion(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
                auto fin_BInter = chrono::high_resolution_clock::now();

                tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
                tiempo_total_BInter += tiempo_busqueda;

                mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
                peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
            }
        }

        // ---------------------------------------- Iterativa -----------------------------------
        else
        {
            // Realiza N_BUSQUEDAS  aleatorias y mide el tiempo
            for (int i = 0; i < N_BUSQUEDAS; ++i)
            {
                // Da igual la distribución del número a buscar
                int valorAleatorio = distrib(gen); // Genera el número aleatorio entre 1 e INT_MAX
                int encontrado;

                double tiempo_busqueda;

                // Binaria1
                auto inicio_B1 = chrono::high_resolution_clock::now();
                encontrado = AlgoritmosBusqueda::busquedaBinaria1Iterativa(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
                auto fin_B1 = chrono::high_resolution_clock::now();

                tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
                tiempo_total_B1 += tiempo_busqueda;

                mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
                peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

                // BinariaInterpolacion
                auto inicio_BInter = chrono::high_resolution_clock::now();
                encontrado = AlgoritmosBusqueda::busquedaBinariaInterpolacionIterativa(vectorAleatorio, 0, vectorAleatorio.size() - 1, valorAleatorio);
                auto fin_BInter = chrono::high_resolution_clock::now();

                tiempo_busqueda = chrono::duration<double, micro>(fin_BInter - inicio_BInter).count(); // Calcular el coste en microsegundos
                tiempo_total_BInter += tiempo_busqueda;

                mejor_tiempo_BInter = min(mejor_tiempo_BInter, tiempo_busqueda);
                peor_tiempo_BInter = max(peor_tiempo_BInter, tiempo_busqueda);
            }
        }
        // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
        tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
        tiempo_medio_BInter = tiempo_total_BInter / N_BUSQUEDAS;

        archivo << n << ";" << mejor_tiempo_B1 << ";" << peor_tiempo_B1 << ";" << tiempo_medio_B1 << ";;"
                << mejor_tiempo_BInter << ";" << peor_tiempo_BInter << ";" << tiempo_medio_BInter << endl;
    }

    archivo.close();
    cout << "Los resultados se han guardado en el archivo '" << nombreFich << ".csv'." << endl;
}

// ------------------------------------------------- Mergesort -------------------------------------------------

void EstudioEmpirico::determinarKOptimo()
{
    string nombreFich = "resulatadosKOptimo";

    ofstream archivo;
    ExtraFunciones::abrirFichero(archivo, nombreFich);

    

    for (int n = TALLA_INICIAL; n <= TALLA_FINAL; n += TALLA_INCREMENTO)
    {
        // Escribimos la primera línea del archivo
        // Una cabecera por cada talla para que sea más fácil de leer
        archivo << "Tamano del Vector;Valor de K;K:Mejor Tiempo (us);K:Peor Tiempo(us);K:Tiempo Medio(us);" << endl;
        // Con cada valor de K, hacemos 10 búsquedas
        // y medimos el tiempo
        int valorInicialK = 5;
        for (int j = 1; j <= 20; j++)
        {
            
            reseteaTiempos();
            // Ordena 10 veces con cada valor de K
            for (int i = 0; i < N_BUSQUEDAS; ++i)
            {
                // Generamos el vector
                vector<int> vectorAleatorio = GeneraVectores::NoRepes(n, gen);
                //cout << "talla: " << n << "\nFin-Inicio:" << (vectorAleatorio.end() - vectorAleatorio.begin()) << endl;
                
                double tiempo_busqueda;
                
                // tiempo de ordenación
                auto inicio_B1 = chrono::high_resolution_clock::now();
                // Ordenamos con MergesortHibrido
                AlgoritmosOrdenacion::MergesortHibrido(vectorAleatorio, (valorInicialK * j));  // Empezamos con K=5
                auto fin_B1 = chrono::high_resolution_clock::now();


                tiempo_busqueda = chrono::duration<double, micro>(fin_B1 - inicio_B1).count(); // Calcular el coste en microsegundos
                
                tiempo_total_B1 += tiempo_busqueda;
                mejor_tiempo_B1 = min(mejor_tiempo_B1, tiempo_busqueda);
                peor_tiempo_B1 = max(peor_tiempo_B1, tiempo_busqueda);

            }

            // Calcula y guarda el tiempo medio, mejor y peor tiempo de búsqueda en el archivo
            tiempo_medio_B1 = tiempo_total_B1 / N_BUSQUEDAS;
            
            archivo << n << ";" << (valorInicialK * j) << ";" << mejor_tiempo_B1 << ";" << peor_tiempo_B1 << ";" << tiempo_medio_B1 << endl;
            
        }
    }
    // Dejamos una linea en blanco para separar los resultados de cada talla
    archivo << endl;

    archivo.close();
    cout << "Los resultados se han guardado en el archivo '" << nombreFich << ".csv'." << endl;
}