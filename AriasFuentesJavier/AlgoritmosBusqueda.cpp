#include "AlgoritmosBusqueda.h"

int AlgoritmosBusqueda::busquedaBinaria1(int A[], int izq, int der, int x)
{

    if (izq > der) {  // 1 OE comparación
        return -1;
    } else {
        int medio = (izq + der) / 2; // 3 OE -> Asignación y 2 operaciones aritméticas
        if (A[medio] == x) { // 2 OE -> acceso al vector y comparación
            return medio;
        } else if (A[medio] > x) { // 2 OE -> acceso al vector y comparación
            return busquedaBinaria1(A, izq, medio - 1, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
        } else {
            return busquedaBinaria1(A, medio + 1, der, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
        }
    }

    // 1 OE de cualquier return en cualquier caso. Arriba no las tuve en cuenta para hacerlo aquí
    
}

int AlgoritmosBusqueda::busquedaBinaria2(int A[], int izq, int der, int x)
{

    if (izq > der) { // 1 OE comparación
        return -1;
    } else {
        int medio = (izq + der) / 2; // 3 OE -> Asignación y 2 operaciones aritméticas
        if (A[medio] == x && (medio == izq || A[medio - 1] != x)) {  
            // 2 OE -> 2 accesos al vector, 3 comparaciones, 2 op lógicas, 1 op aritmética
            return medio;
        } else if (A[medio] >= x) { // 2 OE -> acceso al vector y comparación
            return busquedaBinaria2(A, izq, medio - 1, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
        } else {
            return busquedaBinaria2(A, medio + 1, der, x); // 2 OE -> llamada a función y operación aritmética + Recursividad
        }
    
    }
    // 1 OE de cualquier return en cualquier caso. Arriba no las tuve en cuenta para hacerlo aquí
    
}


//BUSQUEDABINARIAINTERPOLACION(A[izq..der], x):
//  if izq > der OR x < A[izq] OR x > A[der]
//  return -1
//  else
//  // La posición estimada si los datos estuvieran uniformemente
//  // distribuidos
//  pos ← izq + ⌊((x - A[izq]) * (der - izq)) / (A[der] - A[izq])⌋

//  if pos < izq OR pos > der // Por si acaso hay problemas numéricos
//  pos ← ⌊(izq + der)/2⌋

//  if A[pos] = x
//  return pos
//  else if A[pos] > x
//  return BUSQUEDABINARIAINTERPOLACION(A[izq..pos-1], x)
//  else
//  return BUSQUEDABINARIAINTERPOLACION(A[pos+1..der], x)
int AlgoritmosBusqueda::busquedaBinariaInterpolacion(int A[], int izq, int der, int x)
{
    
    if (izq > der || x < A[izq] || x > A[der]) {
        return -1;
    } else {
        int pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
        if (pos < izq || pos > der) {
            pos = (izq + der) / 2;
        }
        if (A[pos] == x) {
            return pos;
        } else if (A[pos] > x) {
            return busquedaBinariaInterpolacion(A, izq, pos - 1, x);
        } else {
            return busquedaBinariaInterpolacion(A, pos + 1, der, x);
        }
    }
}
    
