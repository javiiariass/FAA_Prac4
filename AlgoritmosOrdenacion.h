#pragma once
#include <vector>
using namespace std;
class AlgoritmosOrdenacion
{
protected:
    static void insertSort(vector<int>::iterator inicio, vector<int>::iterator fin);
    static void Merge(vector<int>::iterator inicio, vector<int>::iterator medio, vector<int>::iterator fin);
    // Merge optimizado con un unico vector auxiliar
    static void MergeOptimizado(vector<int>::iterator inicio, vector<int>::iterator medio, vector<int>::iterator fin, vector<int> &aux);
    static void MergesortHibrido(vector<int>::iterator inicio, vector<int>::iterator fin, int parametroK);
    
public:
    static void MergesortHibrido(vector<int> &vector, int parametroK);
    

};

