#include "AlgoritmosOrdenacion.h"


/*
procedimiento inserción(T[1..n])
para i← 2 hasta n hacer
x ← T[i]
j ← i-1
mientras j>0 AND x < T[j] hacer
T[j+1] ← T[j]
j ← j-1
fmientras
T[j+1] ← x
fpara
fprocedimiento

*/


void AlgoritmosOrdenacion::insertSort(vector<int>::iterator inicio, vector<int>::iterator fin)
{
    for (auto it = inicio + 1; it < fin; ++it)
    {
        auto key = *it;
        auto j = it - 1;

        while (j > inicio && key < *j)
        {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}

/**
 * Algoritmo de ordenación Mergesort.
 * Implementa el algoritmo de ordenación Mergesort para ordenar un vector de objetos Bar.
 * @param inicio Iterador al inicio del vector. Funcionan como punteros
 * @param fin Iterador al final del vector. Funcionan como punteros
 * @param criterio Criterio de ordenación (función que compara dos objetos Bar)
 */
void AlgoritmosOrdenacion::MergesortHibrido(vector<int>::iterator inicio, vector<int>::iterator fin,int parametroK)
{
	if((fin - inicio) <= parametroK) //  + 1 sobra aquí. La resta de los iteradores ya da el tamaño del vector
	{
		// Si el tamaño del vector es menor o igual a K, se utiliza el algoritmo de inserción
		insertSort(inicio, fin);
		return;
	}
	else if (fin - inicio > 0)
	{
		// El compilador deduce el tipo de la variable de auto

		// Al puntero incio le sumamos el tamaño del vector/2 -> (fin - inicio) / 2
		auto medio = inicio + (fin - inicio) / 2;

		MergesortHibrido(inicio, medio, parametroK);
		MergesortHibrido(medio, fin, parametroK);
		Merge(inicio, medio, fin);
	}
}

/**
 * Función principal para ordenar un vector de enteros.
 * Esta función llama a la función MergesortHibrida con el vector completo.
 * @param vector Vector de enteros a ordenar
 */
void AlgoritmosOrdenacion::MergesortHibrido(vector<int> &vector,int parametroK)
{
    // Llamamos a la función MergesortHibrido con el vector completo
    MergesortHibrido(vector.begin(), vector.end(), parametroK);
}


/**
 * Función de mezcla para el algoritmo Mergesort.
 * Combina dos subvectores ordenados en un solo vector ordenado.
 * @param inicio Iterador al inicio del vector
 * @param medio Iterador al medio del vector
 * @param fin Iterador al final del vector
 * 
 * @note Esta función es parte del algoritmo Mergesort y no debe ser llamada directamente.
 */
 void AlgoritmosOrdenacion::Merge(vector<int>::iterator inicio, vector<int>::iterator medio, vector<int>::iterator fin)
{
	vector<int> aux(fin - inicio); // Crear un vector auxiliar del tamaño adecuado
	

	//vector<int>::iterator no es más que un iterador, básicamente un puntero
	
	// el tipo auto hace que el compilador deduzca el tipo de la variable
	// Es lo mismo que poner vector<int>::iterator
	auto it = aux.begin(); // Primer elemento del vector auxiliar 
	auto it1 = inicio;
	auto it2 = medio;

	// Al hacer ++ sobre un iterador, se avanza al siguiente elemento

	// hasta que el elemento izdo llegue al medio o el elemento dcho llegue al final
	while (it1 < medio && it2 < fin)
	{
		
		if (*it1 < *it2)
		{
			// Si el elemento de la izquierda es menor que el de la derecha
			// se copia el elemento de la izquierda al vector auxiliar y se avanza el iterador
			// al siguiente elemento
			*it++ = *it1++;
		}
		else
		{
			// Si el elemento de la derecha es menor o igual que el de la izquierda
			// se copia el elemento de la derecha al vector auxiliar y se avanza el iterador
			// al siguiente elemento
			*it++ = *it2++;
		}
	}

	// Copiar el resto de los elementos que quedan en la parte izquierda
	// y en la parte derecha al vector auxiliar
	while (it1 < medio)
	{
		*it++ = *it1++;
	}

	while (it2 < fin)
	{
		*it++ = *it2++;
	}

	// Copiamos el resultado del vector auxiliar al vector original
	// en las posiciones correspondientes desde la posición incicada por inicio
	copy(aux.begin(), aux.end(), inicio); 
}

void MergeOptimizado(vector<int>::iterator inicio, vector<int>::iterator medio, vector<int>::iterator fin, vector<int>& aux) 
{
    // Guardar los índices para usarlos como referencia
    int tamanio = fin - inicio;
    int inicio_idx = inicio - aux.begin();
    int medio_idx = medio - aux.begin();
    int fin_idx = fin - aux.begin();
    
    int i = inicio_idx;
    int j = medio_idx;
    int k = inicio_idx;
    
    // Fusionar las dos mitades ordenadas directamente en el vector auxiliar
    while (i < medio_idx && j < fin_idx) {
        if (aux[i] <= aux[j]) {
            *(inicio + (k - inicio_idx)) = aux[i++];
        } else {
            *(inicio + (k - inicio_idx)) = aux[j++];
        }
        k++;
    }
    
    // Copiar los elementos restantes de la primera mitad
    while (i < medio_idx) {
        *(inicio + (k - inicio_idx)) = aux[i++];
        k++;
    }
    
    // Copiar los elementos restantes de la segunda mitad
    while (j < fin_idx) {
        *(inicio + (k - inicio_idx)) = aux[j++];
        k++;
    }
    
    // Actualizar el vector auxiliar con los valores ordenados
    for (int p = inicio_idx; p < fin_idx; p++) {
        aux[p] = *(inicio + (p - inicio_idx));
    }
}