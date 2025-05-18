#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include "AlgoritmosOrdenacion.h"
#include "GeneraVectores.h"

class ExperimentoK {
public:
    static void ejecutarExperimento();
    static void determinarKOptimo();
private:
    static double promedioTiempos(const std::vector<double>& tiempos);
    static std::vector<int> generarVectorAleatorio(int talla, std::mt19937& gen);
    static void graficarResultados(const std::vector<std::pair<int, double>>& resultados, int talla);
};
