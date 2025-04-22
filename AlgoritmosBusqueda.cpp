#include "AlgoritmosBusqueda.h"

int AlgoritmosBusqueda::busquedaBinaria1(int A[], int izq, int der, int x)
{

    if (izq > der) {
        return -1;
    } else {
        int medio = (izq + der) / 2;
        if (A[medio] == x) {
            return medio;
        } else if (A[medio] > x) {
            return busquedaBinaria1(A, izq, medio - 1, x);
        } else {
            return busquedaBinaria1(A, medio + 1, der, x);
        }
    }
    
}

int AlgoritmosBusqueda::busquedaBinaria2(int A[], int izq, int der, int x)
{

    if (izq > der) {
        return -1;
    } else {
        int medio = (izq + der) / 2;
        if (A[medio] == x && (medio == izq || A[medio - 1] != x)) { // AND (medio = izq OR A[medio-1] ≠ x)
            return medio;
        } else if (A[medio] >= x) {
            return busquedaBinaria2(A, izq, medio - 1, x);
        } else {
            return busquedaBinaria2(A, medio + 1, der, x);
        }
    }
    
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
    
