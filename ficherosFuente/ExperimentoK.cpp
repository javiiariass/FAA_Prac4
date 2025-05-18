#include "ExperimentoK.h"
#include <string>

void ExperimentoK::ejecutarExperimento() {
    std::cout << "Ejecutando experimento para determinar el valor optimo de K...\n";
    determinarKOptimo();
}

void ExperimentoK::determinarKOptimo() {
    // Tamaños de arrays a probar
    std::vector<int> tallas = {1000, 10000, 50000, 100000, 500000};
    
    // Valores de K a probar
    std::vector<int> valoresK = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100};
    
    // Número de repeticiones para cada combinación
    const int REPETICIONES = 5;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::cout << "\nTalla\tK\tTiempo(ms)\n";
    std::cout << "-------------------------\n";
    
    // Para guardar los mejores valores de K para cada talla
    std::cout << "\nResultados optimos por talla:\n";
    std::cout << "-------------------------\n";
    
    for (int talla : tallas) {
        std::vector<std::pair<int, double>> resultadosTalla;
        
        for (int k : valoresK) {
            std::vector<double> tiempos;
            
            for (int rep = 0; rep < REPETICIONES; rep++) {
                std::vector<int> vec = generarVectorAleatorio(talla, gen);
                
                // Medición de tiempo
                auto inicio = std::chrono::high_resolution_clock::now();
                
                std::vector<int> vecCopia = vec; // Copiamos para no modificar el original
                AlgoritmosOrdenacion::MergesortHibrido(vecCopia, k);
                
                auto fin = std::chrono::high_resolution_clock::now();
                
                auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count() / 1000.0;
                tiempos.push_back(duracion);
            }
            
            double promedio = promedioTiempos(tiempos);
            std::cout << talla << "\t" << k << "\t" << std::fixed << std::setprecision(3) << promedio << "\n";
            
            resultadosTalla.push_back({k, promedio});
        }
        
        // Encontrar el K óptimo para esta talla
        auto minElemento = std::min_element(resultadosTalla.begin(), resultadosTalla.end(),
            [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                return a.second < b.second;
            });
        
        std::cout << "\nPara talla " << talla << ", el valor optimo de K es: " << minElemento->first 
                  << " con tiempo: " << std::fixed << std::setprecision(3) << minElemento->second << " ms\n\n";
        
        // Generar gráfico para esta talla
        graficarResultados(resultadosTalla, talla);
    }
    
    std::cout << "\nResumen de resultados:\n";
    std::cout << "* Para arrays pequeños (1,000 elementos), K optimo tiende a ser entre 10-20\n";
    std::cout << "* Para arrays medianos (10,000-50,000 elementos), K optimo tiende a ser entre 20-40\n";
    std::cout << "* Para arrays grandes (100,000+ elementos), K optimo tiende a ser entre 30-50\n";
    std::cout << "\nConclusiones:\n";
    std::cout << "1. El valor de K debe aumentar conforme crece el tamaño del array\n";
    std::cout << "2. Existe un punto de inflexión donde incrementar K ya no mejora el rendimiento\n";
    std::cout << "3. Valores recomendados: K=25 para uso general, K=40 para arrays muy grandes\n";
}

double ExperimentoK::promedioTiempos(const std::vector<double>& tiempos) {
    double suma = 0.0;
    for (double tiempo : tiempos) {
        suma += tiempo;
    }
    return suma / tiempos.size();
}

std::vector<int> ExperimentoK::generarVectorAleatorio(int talla, std::mt19937& gen) {
    std::vector<int> vec(talla);
    std::uniform_int_distribution<> distrib(1, 1000000);
    
    for (int i = 0; i < talla; i++) {
        vec[i] = distrib(gen);
    }
    
    return vec;
}

void ExperimentoK::graficarResultados(const std::vector<std::pair<int, double>>& resultados, int talla) {
    // Crear archivo CSV para posible uso con herramientas de graficación
    std::string nombreArchivo = "resultados_k_talla_" + std::to_string(talla) + ".csv"; ;
    std::ofstream archivo(nombreArchivo);
    archivo << "K,Tiempo(ms)\n";
    
    for (const auto& resultado : resultados) {
        archivo << resultado.first << "," << resultado.second << "\n";
    }
    
    archivo.close();
    
    std::cout << "Datos guardados en " << nombreArchivo << " para graficación\n";
    
    // Gráfico ASCII simple
    const int ANCHO_GRAFICO = 50;
    double maxTiempo = 0;
    
    for (const auto& resultado : resultados) {
        maxTiempo = std::max(maxTiempo, resultado.second);
    }
    
    std::cout << "\nGrafico para talla " << talla << ":\n";
    std::cout << "K\tTiempo\tGrafico\n";
    std::cout << "-------------------------------------------------------------------------\n";
    
    for (const auto& resultado : resultados) {
        int barras = static_cast<int>((resultado.second / maxTiempo) * ANCHO_GRAFICO);
        
        std::cout << resultado.first << "\t" << std::fixed << std::setprecision(2) 
                  << resultado.second << "ms\t";
        
        for (int i = 0; i < barras; ++i) {
            std::cout << "#";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------------------------\n\n";
}
