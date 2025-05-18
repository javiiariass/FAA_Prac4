#include "ExtraFunciones.h"
#include <iomanip>
#include <iostream>

/**
 * Función para abrir un archivo para escritura.
 * 
 * @param archivo Referencia al objeto ofstream que representa el archivo a abrir.
 */
void ExtraFunciones::abrirFichero(ofstream &archivo, string nombreFichSinExtension){
    
    archivo.open(nombreFichSinExtension + ".csv");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        exit(-1);
    }
    
    archivo << fixed << setprecision(6); // Fijar precisión decimal
    // Cabecera archivo csv


}

/**
 * Función para ver la distribución de un vector.
 * Muestra un histograma de un vector de enteros.
 * 
 */
void ExtraFunciones::histogramaVector(vector<int> vec){
    if (vec.empty()) {
        cerr << "El vector está vacío." << endl;
        return;
    }

    int min_val = vec.front();
    int max_val = vec.back();

    if (min_val < 0) {
        cerr << "Advertencia: La función actualmente no maneja números negativos correctamente para las decenas." << endl;
    }

    int min_decena = min_val / 10;
    int max_decena = max_val / 10;

    size_t current_index = 0; // Índice para recorrer el vector eficientemente

    cout << "Histograma por Decenas:\n";
    cout << "------------------------\n";

    for (int decena = min_decena; decena <= max_decena; ++decena) {
        int count = 0;
        // Avanza el índice contando los elementos que pertenecen a la decena actual
        while (current_index < vec.size() && (vec[current_index] / 10) == decena) {
            count++;
            current_index++;
        }

        // Si se encontraron elementos en esta decena, imprimir la línea del histograma
        if (count > 0) {
            cout << "[" << decena * 10 << "-" << decena * 10 + 9 << "]: ";
            // Imprimir los asteriscos
            for (int k = 0; k < count; ++k) {
                cout << "*";
            }
            cout << endl;
        }
        // Si no hay elementos en esta decena (pero está dentro del rango min/max), no se imprime nada.
    }
     cout << "------------------------\n";
}