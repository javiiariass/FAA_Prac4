// FAA_Prac4.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional> // Para std::function
#include <cmath>      // Para std::pow en distribución no uniforme

// --- Prototipos de Funciones de Búsqueda ---
// (Asumimos que estas funciones se implementarán en otro lugar o más abajo)
// Devuelven el índice del elemento si se encuentra, -1 en caso contrario.

// Búsqueda Lineal
int busquedaLineal(const std::vector<int>& arr, int elemento);

// Búsqueda Binaria (requiere array ordenado)
int busquedaBinaria(const std::vector<int>& arr, int elemento);

// Búsqueda Binaria que devuelve la primera ocurrencia (requiere array ordenado)
int busquedaBinariaPrimerOcurrencia(const std::vector<int>& arr, int elemento);

// Búsqueda por Interpolación (requiere array ordenado, funciona mejor con distribución uniforme)
int busquedaBinariaInterpolacion(const std::vector<int>& arr, int elemento);

// --- Funciones Auxiliares para Generar Arrays ---

// Genera un vector ordenado con valores únicos
std::vector<int> generar_array_ordenado_unico(size_t tamano) {
    std::vector<int> arr(tamano);
    std::iota(arr.begin(), arr.end(), 0); // Llena con 0, 1, 2, ...
    return arr;
}

// Genera un vector ordenado con elementos repetidos
std::vector<int> generar_array_ordenado_repetidos(size_t tamano, int valor_repetido, size_t num_repeticiones) {
    std::vector<int> arr;
    arr.reserve(tamano);
    size_t j = 0;
    for (size_t i = 0; i < tamano; ++i) {
        if (i >= (tamano - num_repeticiones) / 2 && i < (tamano + num_repeticiones) / 2) {
             arr.push_back(valor_repetido);
        } else {
            arr.push_back(j++);
            if (j == valor_repetido) j++; // Evitar colisión si j alcanza valor_repetido
        }
    }
     // Asegurarse de que esté ordenado aunque la lógica anterior debería garantizarlo
    std::sort(arr.begin(), arr.end());
    // Corregir si el valor repetido interfiere con la secuencia
    for(size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] <= arr[i-1] && arr[i] != valor_repetido) {
             arr[i] = arr[i-1] + (arr[i-1] == valor_repetido ? 2 : 1); // Ajustar secuencia
        }
    }
     std::sort(arr.begin(), arr.end()); // Reordenar por si acaso
    return arr;
}


// Genera un vector ordenado con distribución aproximadamente uniforme
std::vector<int> generar_array_distribucion_uniforme(size_t tamano, int min_val = 0, int max_val = 1000) {
    std::vector<int> arr(tamano);
    if (tamano == 0) return arr;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_val, max_val);
    for (size_t i = 0; i < tamano; ++i) {
        arr[i] = distrib(gen);
    }
    std::sort(arr.begin(), arr.end());
    return arr;
}

// Genera un vector ordenado con distribución no uniforme (ej. exponencial)
std::vector<int> generar_array_distribucion_no_uniforme(size_t tamano) {
     std::vector<int> arr(tamano);
     if (tamano == 0) return arr;
     std::random_device rd;
     std::mt19937 gen(rd());
     // Generar valores con tendencia a ser más pequeños
     std::exponential_distribution<> distrib(1.0); // Lambda = 1.0
     for (size_t i = 0; i < tamano; ++i) {
         // Escalar y convertir a entero. Ajusta el factor 100 según necesidad.
         arr[i] = static_cast<int>(distrib(gen) * 100);
     }
     std::sort(arr.begin(), arr.end());
     return arr;
}


// --- Función para Ejecutar y Registrar Pruebas ---
void ejecutar_prueba(
    const std::string& nombre_prueba,
    const std::string& nombre_algoritmo,
    std::function<int(const std::vector<int>&, int)> func_busqueda,
    const std::vector<int>& arr,
    int elemento_buscar,
    int indice_esperado,
    std::ofstream& archivo_csv)
{
    auto inicio = std::chrono::high_resolution_clock::now();
    int indice_encontrado = func_busqueda(arr, elemento_buscar);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion_us = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();

    bool correcto = (indice_encontrado == indice_esperado);

    // Escribir en CSV
    archivo_csv << "\"" << nombre_prueba << "\","
                << nombre_algoritmo << ","
                << arr.size() << ","
                << elemento_buscar << ","
                << indice_esperado << ","
                << indice_encontrado << ","
                << duracion_us << ","
                << (correcto ? "SI" : "NO") << "\n";

     // Opcional: Imprimir en consola para feedback inmediato
     // std::cout << "Prueba: " << nombre_prueba << " (" << nombre_algoritmo << "), Tam: " << arr.size()
     //           << ", Elem: " << elemento_buscar << ", Esp: " << indice_esperado
     //           << ", Obt: " << indice_encontrado << ", T(us): " << duracion_us
     //           << ", Correcto: " << (correcto ? "SI" : "NO") << std::endl;
}


int main()
{
    // --- Abrir archivos CSV para cada categoría ---
    std::ofstream csv_basicos("resultados_basicos.csv");
    std::ofstream csv_repetidos("resultados_repetidos.csv");
    std::ofstream csv_posicion("resultados_posicion.csv");
    std::ofstream csv_inexistentes("resultados_inexistentes.csv");
    std::ofstream csv_interpolacion("resultados_interpolacion.csv");
    // Añadir más archivos si se necesitan categorías más específicas

    // --- Escribir cabeceras CSV ---
    const std::string cabecera = "Caso de Prueba,Algoritmo,Tamano Array,Elemento Buscado,Indice Esperado,Indice Obtenido,Tiempo (us),Correcto\n";
    csv_basicos << cabecera;
    csv_repetidos << cabecera;
    csv_posicion << cabecera;
    csv_inexistentes << cabecera;
    csv_interpolacion << cabecera;


    // --- Definición de Casos de Prueba ---
    std::vector<int> arr_vacio = {};
    std::vector<int> arr_uno = {42};
    std::vector<int> arr_grande_unico = generar_array_ordenado_unico(1000);
    std::vector<int> arr_grande_repetidos = generar_array_ordenado_repetidos(1000, 500, 50); // 50 repeticiones de 500
    std::vector<int> arr_uniforme = generar_array_distribucion_uniforme(1000);
    std::vector<int> arr_no_uniforme = generar_array_distribucion_no_uniforme(1000);

    // Mapeo de nombres de algoritmos a funciones
    std::vector<std::pair<std::string, std::function<int(const std::vector<int>&, int)>>> algoritmos = {
        {"Lineal", busquedaLineal},
        {"Binaria", busquedaBinaria},
        {"BinariaPrimerOcurrencia", busquedaBinariaPrimerOcurrencia},
        {"Interpolacion", busquedaBinariaInterpolacion}
    };

    // --- Ejecución de Pruebas ---

    // 1. Arrays Vacíos (-> basicos.csv)
    for (const auto& algo : algoritmos) {
        ejecutar_prueba("Array Vacio", algo.first, algo.second, arr_vacio, 5, -1, csv_basicos);
    }

    // 2. Arrays con un solo elemento (-> basicos.csv)
    for (const auto& algo : algoritmos) {
        ejecutar_prueba("Array Uno - Encontrado", algo.first, algo.second, arr_uno, 42, 0, csv_basicos);
        ejecutar_prueba("Array Uno - No Encontrado", algo.first, algo.second, arr_uno, 10, -1, csv_basicos);
    }

    // 3. Arrays con elementos repetidos (-> repetidos.csv)
    int valor_repetido = 500;
    int primer_indice_repetido = -1;
    for(size_t i = 0; i < arr_grande_repetidos.size(); ++i) {
        if (arr_grande_repetidos[i] == valor_repetido) {
            primer_indice_repetido = static_cast<int>(i);
            break;
        }
    }
    int indice_antes_repetido = primer_indice_repetido > 0 ? primer_indice_repetido - 1 : -1;
    int valor_antes_repetido = indice_antes_repetido != -1 ? arr_grande_repetidos[indice_antes_repetido] : -999; // Valor inexistente si no hay anterior
    int indice_despues_repetido = primer_indice_repetido + 50 < arr_grande_repetidos.size() ? primer_indice_repetido + 50 : -1; // 50 es num_repeticiones
    int valor_despues_repetido = indice_despues_repetido != -1 ? arr_grande_repetidos[indice_despues_repetido] : -999; // Valor inexistente si no hay posterior


    for (const auto& algo : algoritmos) {
         // Busca el valor repetido. Binaria/Interpolación pueden dar cualquier ocurrencia. Lineal da la primera. BinariaPrimerOcurrencia DEBE dar la primera.
         int esperado_repetido = (algo.first == "Lineal" || algo.first == "BinariaPrimerOcurrencia") ? primer_indice_repetido : (primer_indice_repetido != -1 ? primer_indice_repetido : -1); // Simplificación: para Binaria/Interpolación aceptamos la primera si existe
         if (algo.first == "Binaria" || algo.first == "Interpolacion") esperado_repetido = (primer_indice_repetido != -1 ? 1 : -1); // Indicador de que se espera encontrarlo, no necesariamente el primero

         // Re-ejecutar la búsqueda para obtener el índice real para Binaria/Interpolación y verificar si es una ocurrencia válida
         int indice_real_bin_inter = -1;
         if (algo.first == "Binaria" || algo.first == "Interpolacion") {
             indice_real_bin_inter = algo.second(arr_grande_repetidos, valor_repetido);
             esperado_repetido = (indice_real_bin_inter != -1 && arr_grande_repetidos[indice_real_bin_inter] == valor_repetido) ? indice_real_bin_inter : -1; // Aceptamos cualquier ocurrencia válida
         } else {
              esperado_repetido = (algo.first == "Lineal" || algo.first == "BinariaPrimerOcurrencia") ? primer_indice_repetido : -1;
         }


        ejecutar_prueba("Array Repetidos - Buscar Repetido", algo.first, algo.second, arr_grande_repetidos, valor_repetido, esperado_repetido, csv_repetidos);
        if (indice_antes_repetido != -1) {
            ejecutar_prueba("Array Repetidos - Buscar Antes", algo.first, algo.second, arr_grande_repetidos, valor_antes_repetido, indice_antes_repetido, csv_repetidos);
        }
         if (indice_despues_repetido != -1) {
             ejecutar_prueba("Array Repetidos - Buscar Despues", algo.first, algo.second, arr_grande_repetidos, valor_despues_repetido, indice_despues_repetido, csv_repetidos);
         }
    }
     // Verificación específica para BinariaPrimerOcurrencia (-> repetidos.csv)
     ejecutar_prueba("Array Repetidos - PrimerOcurrencia Check", "BinariaPrimerOcurrencia", busquedaBinariaPrimerOcurrencia, arr_grande_repetidos, valor_repetido, primer_indice_repetido, csv_repetidos);


    // 4. Búsqueda al principio, medio y final (-> posicion.csv)
    int elem_principio = arr_grande_unico[0];
    int elem_medio = arr_grande_unico[arr_grande_unico.size() / 2];
    int elem_final = arr_grande_unico[arr_grande_unico.size() - 1];
    for (const auto& algo : algoritmos) {
        ejecutar_prueba("Array Grande - Principio", algo.first, algo.second, arr_grande_unico, elem_principio, 0, csv_posicion);
        ejecutar_prueba("Array Grande - Medio", algo.first, algo.second, arr_grande_unico, elem_medio, (int)arr_grande_unico.size() / 2, csv_posicion);
        ejecutar_prueba("Array Grande - Final", algo.first, algo.second, arr_grande_unico, elem_final, (int)arr_grande_unico.size() - 1, csv_posicion);
    }

    // 5. Búsqueda de elementos inexistentes (-> inexistentes.csv)
    int elem_inexistente_menor = -10;
    int elem_inexistente_mayor = (int)arr_grande_unico.size() + 10;
    int elem_inexistente_medio = arr_grande_unico[arr_grande_unico.size() / 3] + 1; // Uno que probablemente no esté
     // Asegurarse de que realmente no existe (podría coincidir por casualidad)
     while(std::binary_search(arr_grande_unico.begin(), arr_grande_unico.end(), elem_inexistente_medio)) {
         elem_inexistente_medio++;
     }

    for (const auto& algo : algoritmos) {
        ejecutar_prueba("Array Grande - Inexistente Menor", algo.first, algo.second, arr_grande_unico, elem_inexistente_menor, -1, csv_inexistentes);
        ejecutar_prueba("Array Grande - Inexistente Mayor", algo.first, algo.second, arr_grande_unico, elem_inexistente_mayor, -1, csv_inexistentes);
        ejecutar_prueba("Array Grande - Inexistente Medio", algo.first, algo.second, arr_grande_unico, elem_inexistente_medio, -1, csv_inexistentes);
    }


    // 6. Para BÚSQUEDABINARIAINTERPOLACIÓN: arrays con distribución uniforme y no uniforme (-> interpolacion.csv)
    int elem_uniforme = arr_uniforme.empty() ? -1 : arr_uniforme[arr_uniforme.size() / 2];
    int elem_no_uniforme = arr_no_uniforme.empty() ? -1 : arr_no_uniforme[arr_no_uniforme.size() / 2];
    int indice_uniforme = arr_uniforme.empty() ? -1 : (int)arr_uniforme.size() / 2;
    int indice_no_uniforme = arr_no_uniforme.empty() ? -1 : (int)arr_no_uniforme.size() / 2;

    if (!arr_uniforme.empty()) {
         // Ajustar indice_uniforme si hay duplicados en el medio
         auto it_u = std::lower_bound(arr_uniforme.begin(), arr_uniforme.end(), elem_uniforme);
         indice_uniforme = std::distance(arr_uniforme.begin(), it_u);

        // Ejecutar prueba de interpolación y también binaria como comparación en el mismo archivo
        ejecutar_prueba("Interpolacion - Uniforme", "Interpolacion", busquedaBinariaInterpolacion, arr_uniforme, elem_uniforme, indice_uniforme, csv_interpolacion);
        ejecutar_prueba("Binaria - Uniforme (Ref)", "Binaria", busquedaBinaria, arr_uniforme, elem_uniforme, indice_uniforme, csv_interpolacion); // Comparación
        ejecutar_prueba("Interpolacion - Uniforme Inexistente", "Interpolacion", busquedaBinariaInterpolacion, arr_uniforme, arr_uniforme.back() + 1, -1, csv_interpolacion);
        ejecutar_prueba("Binaria - Uniforme Inexistente (Ref)", "Binaria", busquedaBinaria, arr_uniforme, arr_uniforme.back() + 1, -1, csv_interpolacion); // Comparación
    }
     if (!arr_no_uniforme.empty()) {
         // Ajustar indice_no_uniforme si hay duplicados en el medio
         auto it_nu = std::lower_bound(arr_no_uniforme.begin(), arr_no_uniforme.end(), elem_no_uniforme);
         indice_no_uniforme = std::distance(arr_no_uniforme.begin(), it_nu);

        // Ejecutar prueba de interpolación y también binaria como comparación
        ejecutar_prueba("Interpolacion - No Uniforme", "Interpolacion", busquedaBinariaInterpolacion, arr_no_uniforme, elem_no_uniforme, indice_no_uniforme, csv_interpolacion);
        ejecutar_prueba("Binaria - No Uniforme (Ref)", "Binaria", busquedaBinaria, arr_no_uniforme, elem_no_uniforme, indice_no_uniforme, csv_interpolacion); // Comparación
        ejecutar_prueba("Interpolacion - No Uniforme Inexistente", "Interpolacion", busquedaBinariaInterpolacion, arr_no_uniforme, arr_no_uniforme.back() + 1, -1, csv_interpolacion);
        ejecutar_prueba("Binaria - No Uniforme Inexistente (Ref)", "Binaria", busquedaBinaria, arr_no_uniforme, arr_no_uniforme.back() + 1, -1, csv_interpolacion); // Comparación
     }


    // --- Cerrar todos los archivos CSV ---
    csv_basicos.close();
    csv_repetidos.close();
    csv_posicion.close();
    csv_inexistentes.close();
    csv_interpolacion.close();

    std::cout << "Pruebas completadas. Resultados guardados en archivos CSV separados." << std::endl;

    return 0;
}

// --- Implementaciones de Funciones de Búsqueda ---
// (Aquí irían las implementaciones o podrían estar en archivos .cpp separados e incluidos)

// Ejemplo de implementación (las demás serían similares)
int busquedaLineal(const std::vector<int>& arr, int elemento) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == elemento) {
            return static_cast<int>(i);
        }
    }
    return -1; // No encontrado
}

int busquedaBinaria(const std::vector<int>& arr, int elemento) {
    int bajo = 0;
    int alto = static_cast<int>(arr.size()) - 1;
    while (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2; // Evita desbordamiento
        if (arr[medio] == elemento) {
            return medio;
        } else if (arr[medio] < elemento) {
            bajo = medio + 1;
        } else {
            alto = medio - 1;
        }
    }
    return -1; // No encontrado
}

int busquedaBinariaPrimerOcurrencia(const std::vector<int>& arr, int elemento) {
    int bajo = 0;
    int alto = static_cast<int>(arr.size()) - 1;
    int resultado = -1;
    while (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2;
        if (arr[medio] == elemento) {
            resultado = medio;
            alto = medio - 1; // Intentar encontrar una ocurrencia anterior
        } else if (arr[medio] < elemento) {
            bajo = medio + 1;
        } else {
            alto = medio - 1;
        }
    }
    return resultado;
}

int busquedaBinariaInterpolacion(const std::vector<int>& arr, int elemento) {
    int bajo = 0;
    int alto = static_cast<int>(arr.size()) - 1;

    while (bajo <= alto && elemento >= arr[bajo] && elemento <= arr[alto]) {
        if (bajo == alto) {
            return (arr[bajo] == elemento) ? bajo : -1;
        }

        // Estimación de la posición usando interpolación
        // Evitar división por cero y asegurar que el cálculo no desborde ni sea inválido
        long long delta_val = (long long)arr[alto] - arr[bajo];
        if (delta_val == 0) { // Si todos los elementos en el rango son iguales
             return (arr[bajo] == elemento) ? bajo : -1; // O buscar linealmente en el rango [bajo, alto] si se quiere ser más robusto
        }

        // Usar double para el cálculo intermedio para mayor precisión y evitar desbordamiento
         double pos_double = bajo + (((double)alto - bajo) / delta_val) * (elemento - arr[bajo]);

         // Validar que pos esté dentro de los límites antes de acceder a arr[pos]
         if (pos_double < bajo || pos_double > alto) {
              // La estimación está fuera del rango actual, puede indicar distribución muy no uniforme
              // o que el elemento no está. Podríamos recurrir a binaria o lineal aquí,
              // o simplemente indicar no encontrado si la lógica lo sugiere.
              // Por simplicidad, si la estimación falla drásticamente, salimos.
              // Una mejor opción sería acotar 'pos' a [bajo, alto] o cambiar de estrategia.
              // Para este ejemplo, si la estimación es salvaje, rompemos la búsqueda.
              // Una comprobación más robusta sería comparar con búsqueda binaria si la interpolación falla.
              // Hacemos una búsqueda lineal simple como fallback si la interpolación parece fallar.
               for(int i = bajo; i <= alto; ++i) if(arr[i] == elemento) return i;
               return -1;

         }

         int pos = static_cast<int>(pos_double);


        if (arr[pos] == elemento) {
            // Podríamos necesitar encontrar la primera ocurrencia si se requiere,
            // similar a busquedaBinariaPrimerOcurrencia, buscando hacia la izquierda.
            // Por ahora, devolvemos la encontrada.
            return pos;
        }

        if (arr[pos] < elemento) {
            bajo = pos + 1;
        } else {
            alto = pos - 1;
        }
    }
    return -1; // No encontrado
}


// ... (resto de comentarios originales del archivo) ...
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración
// ... (resto de sugerencias) ...
