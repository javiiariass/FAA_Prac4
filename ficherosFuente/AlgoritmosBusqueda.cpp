#include "AlgoritmosBusqueda.h"
#include "AlgoritmosOrdenacion.h"

/**
 * @brief Búsqueda Secuencial implementada anteriores practicas
 * Esta implementación de búsqueda secuencial busca un elemento en un vector.
 * Devuelve el índice del elemento si se encuentra, de lo contrario devuelve -1.
 * @param vec Vector de enteros donde se realizará la búsqueda.
 * @param target Elemento que se desea buscar en el vector.
 * @return Índice del elemento encontrado o -1 si no se encuentra.
 */
int AlgoritmosBusqueda::busquedaSecuencial(const vector<int> &vec, int target)
{
    for (unsigned int num = 0; num < vec.size(); num++)
    {
        if (vec[num] == target)
        {
            return num; // Si se encuentra el elemento, devuelve el índice
        }
    }
    return -1; // Si no se encuentra el elemento, devuelve -1
}

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
int AlgoritmosBusqueda::busquedaBinaria1(vector<int> A, int izq, int der, int x)
{
    // Excepción. Realmente no forma parte de la búsqueda como tal
    if (izq > der || A.empty()) // 1 OE comparación
        return -1;

    int medio = (izq + der) / 2; // 3 OE -> Asignación y 2 operaciones aritméticas
    if (A[medio] == x)
    { // 2 OE -> acceso al vector y comparación
        return medio;
    }

    else if (A[medio] > x)
    {                                                  // 2 OE -> acceso al vector y comparación
        return busquedaBinaria1(A, izq, medio - 1, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
    }

    else
    {
        return busquedaBinaria1(A, medio + 1, der, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
    }

    // 1 OE de cualquier return en cualquier caso. Arriba no las tuve en cuenta para hacerlo aquí
}

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
 * @return Índice de la primera ocurrencia del elemento encontrado o -1 si no se encuentra.
 */
int AlgoritmosBusqueda::busquedaBinaria2(vector<int> A, int izq, int der, int x)
{

    if (izq > der || A.empty())
    { // 1 OE comparación
        return -1;
    }

    int medio = (izq + der) / 2; // 3 OE -> Asignación y 2 operaciones aritméticas
    if (A[medio] == x && (medio == izq || A[medio - 1] != x))
    {
        // 2 OE -> 2 accesos al vector, 3 comparaciones, 2 op lógicas, 1 op aritmética
        return medio;
    }
    else if (A[medio] >= x)
    {                                                  // 2 OE -> acceso al vector y comparación
        return busquedaBinaria2(A, izq, medio - 1, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
    }
    else
    {
        return busquedaBinaria2(A, medio + 1, der, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
    }

    // 1 OE de cualquier return en cualquier caso. Arriba no las tuve en cuenta para hacerlo aquí
}

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
int AlgoritmosBusqueda::busquedaBinariaInterpolacion(vector<int> A, int izq, int der, int x)
{
    if (izq > der || A.empty() || x < A[izq] || x > A[der])
    { // 7 OE -> 5 Op. lógicas y 2 accesos a vector
        return -1;
    }

    // Si la resta de los elementos extremos es 0. Crashea -> Hay que controlarlo
    int denominador = (A[der] - A[izq]); // 4 OE -> 1 asignación, 2 accesos vector y 1 op. aritmética
    if (denominador == 0)                // 1 OE -> op. lógica
        denominador = 1;                 // 1 OE -> 1 asignación

    int pos = izq + ((x - A[izq]) * (der - izq)) / denominador; // 7 OE -> 1 Asignacion, 5 Op. aritméticas, 1 Acceso vector
    if (pos < izq || pos > der)                                 // 3 OE -> 3 Op. lógicas
        pos = (izq + der) / 2;                                  // 3 OE -> 1 Asignación, 2 Operación aritmética

    if (A[pos] == x)
    { // 2 OE -> 1 Acceso vector y 1 Op. lógica
        return pos;
    }
    else if (A[pos] > x)
    {                                                            // 2 OE -> 1 Acceso vector y 1 Op. lógica
        return busquedaBinariaInterpolacion(A, izq, pos - 1, x); // 2 OE -> 1 salto y 1 op. aritmética
    }
    else
    {
        return busquedaBinariaInterpolacion(A, pos + 1, der, x); // 2 OE -> 1 salto y 1 op. aritmética
    }
}

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
int AlgoritmosBusqueda::busquedaBinaria1Iterativa(std::vector<int> A, int izq, int der, int x)
{
    // Excepción. Realmente no forma parte de la búsqueda como tal
    // Manejo de casos base: array vacío o rango inválido inicial
    if (A.empty() || izq > der)
    {
        return -1;
    }

    // Bucle principal: continúa mientras el rango de búsqueda sea válido
    while (izq <= der)
    {
        int medio = (izq + der) / 2; // Calcular el punto medio

        // Si el elemento en el medio es el buscado
        if (A[medio] == x)
        {
            return medio; // Elemento encontrado, retornar su índice
        }
        // Si el elemento en el medio es mayor que el buscado
        else if (A[medio] > x)
        {
            der = medio - 1; // Descartar la mitad derecha (incluido el medio)
        }
        // Si el elemento en el medio es menor que el buscado
        else
        {
            izq = medio + 1; // Descartar la mitad izquierda (incluido el medio)
        }
    }

    // Si el bucle termina, significa que el elemento no fue encontrado
    return -1;
}

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
int AlgoritmosBusqueda::busquedaBinaria2Iterativa(std::vector<int> A, int izq, int der, int x)
{
    // Manejo de casos base: array vacío o rango inválido inicial
    if (A.empty() || izq > der)
    {
        return -1;
    }

    int resultado = -1; // Variable para almacenar el índice de la primera ocurrencia

    // Bucle principal: continúa mientras el rango de búsqueda sea válido
    while (izq <= der)
    {
        int medio = (izq + der) / 2; // Calcular el punto medio

        // Si el elemento en el medio es el buscado
        if (A[medio] == x && (medio == izq || A[medio - 1] != x))
        {
            return medio; // Potencial primera ocurrencia, la almacenamos
        }
        // Si el elemento en el medio es mayor que el buscado
        else if (A[medio] >= x)
        {
            der = medio - 1; // Descartar la mitad derecha
        }
        // Si el elemento en el medio es menor que el buscado
        else
        {
            izq = medio + 1; // Descartar la mitad izquierda
        }
    }

    // Retornar el índice de la primera ocurrencia encontrada (o -1 si no se encontró ninguna)
    return resultado;
}

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
int AlgoritmosBusqueda::busquedaBinariaInterpolacionIterativa(std::vector<int> A, int izq, int der, int x)
{
    // Manejo de casos base: array vacío, rango inválido o x fuera del rango de los extremos actuales
    if (A.empty() || izq > der || x < A[izq] || x > A[der])
    {
        return -1;
    }

    // Bucle principal: continúa mientras el rango de búsqueda sea válido y x esté dentro del rango de los extremos
    while (izq <= der && x >= A[izq] && x <= A[der])
    {
        // Si la resta de los elementos extremos es 0. Crashea -> Hay que controlarlo
        int denominador = (A[der] - A[izq]); // 4 OE -> 1 asignación, 2 accesos vector y 1 op. aritmética
        if (denominador == 0)                // 1 OE -> op. lógica
            denominador = 1;                 // 1 OE -> 1 asignación

        int pos = izq + ((x - A[izq]) * (der - izq)) / denominador; // 7 OE -> 1 Asignacion, 5 Op. aritméticas, 1 Acceso vector
        if (pos < izq || pos > der)                                 // 3 OE -> 3 Op. lógicas
            pos = (izq + der) / 2;                                  // 3 OE -> 1 Asignación, 2 Operación aritmética

        // Si el elemento en la posición estimada es el buscado
        if (A[pos] == x)
        {
            return pos; // Elemento encontrado
        }
        // Si el elemento en la posición estimada es mayor que el buscado
        else if (A[pos] > x)
        {
            der = pos - 1; // Descartar la parte derecha
        }
        // Si el elemento en la posición estimada es menor que el buscado
        else
        {
            izq = pos + 1; // Descartar la parte izquierda
        }
    }

    // Si el bucle termina, el elemento no fue encontrado
    return -1;
}

/**
 * Algortimo del ejercicio 5. Busca los elementos no repetidos en un vector y los devuelve en un nuevo vector.
 * @param A Vector de enteros donde se realizará la búsqueda.
 * @return Un vector de enteros con los elementos no repetidos.
 *
 */
vector<int> AlgoritmosBusqueda::busquedaNoRepetidos(vector<int> A)
{
    // Si el array está vacío, devolver array vacío
    if (A.empty())
    {
        return {};
    }

    // Crear una copia del array para ordenarlo sin modificar el original
    vector<int> ordenado = A;

    // Ordenar usando MergeSort (algoritmo estudiado) - O(n log n)
    AlgoritmosOrdenacion::MergesortHibrido(ordenado, 30); // Usando K=30 como valor óptimo
    
    // Vector para almacenar el resultado
    vector<int> unicos;

    // Proceso para encontrar elementos únicos en el array ordenado - O(n)
    int n = ordenado.size();

    // Comprobar el primer elemento
    if (n == 1 || (ordenado[0] != ordenado[1]))
    {
        unicos.push_back(ordenado[0]);
    }

    // Comprobar elementos intermedios
    for (int i = 1; i < n - 1; i++)
    {
        if (ordenado[i] != ordenado[i - 1] && ordenado[i] != ordenado[i + 1])
        {
            unicos.push_back(ordenado[i]);
        }
    }

    // Comprobar el último elemento
    if (n > 1 && ordenado[n - 1] != ordenado[n - 2])
    {
        unicos.push_back(ordenado[n - 1]);
    }

    return unicos;
}


vector<int> AlgoritmosBusqueda::ElementosConKRepeticiones(const vector<int> &array, int k) 
{
    // Si el array está vacío o k <= 0, devolver array vacío
    if (array.empty() || k <= 0) {
        return {};
    }
    
    // Crear una copia del array para ordenarlo sin modificar el original
    vector<int> ordenado = array;
    
    // Ordenar usando MergeSort - O(n log n)
    AlgoritmosOrdenacion::MergesortHibrido(ordenado, 30); 
    
    // Vector para almacenar el resultado
    vector<int> resultado;
    
    // Proceso para encontrar elementos que aparecen exactamente k veces - O(n)
    int n = ordenado.size();
    
    if (n == 0) return resultado;
    
    int valorActual = ordenado[0];
    int contador = 1;
    
    // Recorremos todos los elementos excepto el último
    for (int i = 1; i < n; i++) {
        if (ordenado[i] == valorActual) {
            // Si el elemento actual es igual al anterior, incrementamos el contador
            contador++;
        } else {
            // Si encontramos un elemento diferente, verificamos si el anterior apareció k veces
            if (contador == k) {
                resultado.push_back(valorActual);
            }
            // Reiniciamos para el nuevo elemento
            valorActual = ordenado[i];
            contador = 1;
        }
    }
    
    // Verificar el último conjunto de elementos
    if (contador == k) {
        resultado.push_back(valorActual);
    }
    
    return resultado;
}
