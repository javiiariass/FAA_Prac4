#pragma once
#include <fstream>
#include <vector>
using namespace std;

class ExtraFunciones
{

public:
    static void abrirFichero(ofstream &archivo, string nombreFichSinExtension);
    static void histogramaVector(vector<int> vec); // Para comprobar visualmente la distribución de los vectores.
};

