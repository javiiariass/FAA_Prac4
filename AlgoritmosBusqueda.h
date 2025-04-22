#pragma once
class AlgoritmosBusqueda
{

// 	BUSQUEDABINARIA1(A[izq..der], x):
//  if izq > der
//  return -1
//  else
//  medio ← ⌊(izq + der)/2⌋
//  if A[medio] = x
//  return medio
//  else if A[medio] > x
//  return BUSQUEDABINARIA1(A[izq..medio-1], x)
//  else
// return BUSQUEDABINARIA1(A[medio+1..der], x)

public:

    static int busquedaBinaria1(int A[], int izq, int der, int x);
    static int busquedaBinaria2(int A[], int izq, int der, int x);
    static int busquedaBinariaInterpolacion(int A[], int izq, int der, int x);
};