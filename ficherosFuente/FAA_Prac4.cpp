#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <limits>
#include <iomanip>
#include "AlgoritmosBusqueda.h"
#include "GeneraVectores.h"
#include "ExtraFunciones.h"
#include "EstudioEmpirico.h"
#include "ExperimentoK.h"

using namespace std;

// ------------------------------- Constantes para varias las tallas -------------------------------

// Numero de busquedas
const int N_BUSQUEDAS = 5;
// Talla inicial
const int TALLA_INICIAL = 1000;
// Talla final
const int TALLA_FINAL = 10000;
// Incremento entre iteraciones de la talla
const int TALLA_INCREMENTO = 1000;

int menuAleatorios();
int menuLaterales();
int menuPrincipal();
int menuDistribuciones();
int menuVector();
int menuB1vsBInter();
void generaDistribuciones(random_device &rd);

/**
 * Pide valor al usuario hasta que introduce valor
 * correcto acotado entre los dos parámetros
 */
int seleccionCorrecta(int valorInicial, int valorFinal);

int main(int argc, char *argv[])
{

    random_device rd; // inicializa la semilla
    EstudioEmpirico estudio(N_BUSQUEDAS, TALLA_INICIAL, TALLA_FINAL, TALLA_INCREMENTO, rd);
    bool salir = false;
    do
    {
        system("cls");
        switch (menuPrincipal())
        {
        case 1:
            estudio.ArrayVacio();
            break;
        // Arrays vacios
        case 2:
            estudio.Array1Elemento();
            break;
        case 3:
            estudio.Repetidos();
            break;
        case 4:
        {
            int opcion = menuLaterales();
            if (opcion != 0)
                estudio.LimitesCentro(opcion - 1);
        }
            break;
        case 5:
            estudio.comprobarPrimeraOcurrencia();
            break;
        case 6:
        {
            int opcion = menuAleatorios();
            if (opcion != 0)
                estudio.Aleatorio(opcion - 1);
        }
            break;
        case 7:
            estudio.recursivosVsIterativos();
            break;
        case 8:
            {
                int opcionAlgoritmo = menuB1vsBInter();
                if (opcionAlgoritmo == 0)
                    break;
                int opcionDistri = menuAleatorios();

                if (opcionDistri != 0)
                    estudio.B1vsBInter(opcionAlgoritmo-1, opcionDistri-1);
            }
            break;
        case 9:
            generaDistribuciones(rd);
            break;
        case 10:
            estudio.determinarKOptimo();
            break;
        case 0:
            salir = true;
            break;
        }
        system("pause");
    } while (!salir);
    return 0;
}

int seleccionCorrecta(int inicio, int final)
{
    int a;

    do
    {
        cout << "Opcion: ";
        cin >> a;

        if (cin.fail())
        {
            // Si introduce un carácter en vez de un número
            a = final + 1; // o cualquier num no valido en menu
            cin.clear();   // Reset a la flag fail
            fflush(stdin); // Descartamos de buffer los caracteres leidos
        }
    } while (a < inicio || a > final);

    return a;
}

int menuPrincipal()
{

    cout << "Estudio Empírico Algoritmos Busqueda\n";
    cout << "---------------------------------------\n";
    cout << "Seleccione una opción:\n";
    cout << "1. Vector vacío\n";
    cout << "2. Vector con 1 elemento\n";
    cout << "3. Vector con elementos repetidos\n";
    cout << "4. Búsqueda de elementos a principio/centro/fin del vector\n";
    cout << "5. Comprobar primera ocurrencia en algoritmo con indice de primera ocurrencia\n";
    cout << "6. Vector con valores aleatorios: Elegir distintas distribuciones\n";
    cout << "7. Recursivos Vs Iterativos\n";
    cout << "8. Binaria1 Vs Binaria Interpolación\n";
    cout << "9. Probar generación de Vector con distintas distribuciones\n";
    cout << "10. Experimento para determinar K óptimo en MergesortHibrido\n";
    cout << "0. Salir\n";

    return seleccionCorrecta(0, 10);
}

int menuLaterales()
{

    cout << "\n----------------\n";
    cout << "Elija ubicación del elemento a buscar\n";
    cout << "----------------\n";
    cout << "1. Elemento al principio del vector\n";
    cout << "2. Elemento en el medio del vector\n";
    cout << "3. Elemento al final del vector\n";
    cout << "0. Regresar\n";
    return seleccionCorrecta(0, 3);
}

int menuAleatorios()
{
    cout << "\n----------------\n";
    cout << "Elija tipo de distribución para generar valores aleatorios\n";
    cout << "----------------\n";
    cout << "1. Distribución uniforme\n";
    cout << "2. Distribución exponencial\n";
    cout << "3. Distribución x^2\n";
    cout << "0. Regresar\n";
    return seleccionCorrecta(0, 3);
}

int menuDistribuciones()
{

    cout << "\n----------------\n";
    cout << "Seleccione una distribución para generar valores aleatorios:\n";
    cout << "1. Uniforme sin repeticiones\n";
    cout << "2. Uniforme con repeticiones\n";
    cout << "3. Exponencial\n";
    cout << "4. Cuadrática\n";
    cout << "0. Salir\n";
    return seleccionCorrecta(0, 4);
}

int menuVector()
{

    cout << "\n----------------\n";
    cout << "Qué desea hacer con el vector generado:\n";
    cout << "1. Mostrar Vector\n";
    cout << "2. Mostrar Histograma\n";
    cout << "0. Regresar\n";
    return seleccionCorrecta(0, 2);
}

int menuB1vsBInter(){
    
    cout << "\n----------------\n";
    cout << "Seleccione qué algoritmos quiere:\n";
    cout << "1. Recursivos\n";
    cout << "2. Iterativos\n";
    cout << "0. Regresar\n";
    return seleccionCorrecta(0, 2);
}

void generaDistribuciones(random_device &rd)
{

    int opcion;
    do
    {
        opcion = menuDistribuciones();
        if (opcion == 0)
            break; // Si salimos sin operar

        int talla;
        do
        {
            cout << "Introduzca la talla del vector: ";
            cin >> talla;
        } while (talla < 0);

        vector<int> vec(talla);
        mt19937 gen(rd()); // Generador de aleatorios con la semilla rd()

        switch (opcion)
        {
        case 1:
            vec = GeneraVectores::NoRepes(talla, gen);
            break;

        case 2:
            vec = GeneraVectores::ConRepes(talla, gen);
            break;

        case 3:
            vec = GeneraVectores::Exponencial(talla, gen);
            break;

        case 4:
            vec = GeneraVectores::XCuadrado(talla, gen);
            break;

        default:
            cout << "Opción no válida." << endl;
            break;
        }

        // Ordenamos vector
        EstudioEmpirico::ordenaVector(vec);

        // Mostramos menu opciones con vector
        int op;
        do
        {
            system("cls");
            op = menuVector();
            if (op == 1)
            {
                // Mostramos vector
                cout << "Vector generado: \n[";

                for (int i : vec)
                    cout << i << " ";

                cout << "]" << endl;
            }
            else if (op == 2)
                // Mostramos histograma
                ExtraFunciones::histogramaVector(vec);

            system("pause");
        } while (op != 0);

    } while (opcion != 0);
}