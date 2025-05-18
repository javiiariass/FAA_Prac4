# Comparativa entre configuraciones Debug y Release

| Característica | Debug | Release |
|----------------|-------|---------|
| **Optimización** | Mínima o ninguna | Completa (normalmente -O2 o -O3) |
| **Símbolos de depuración** | Completos | Ninguno o mínimos |
| **Macros predefinidas** | _DEBUG | NDEBUG |
| **Comprobaciones en tiempo de ejecución** | Activadas | Desactivadas |
| **Rendimiento** | Lento | Rápido (3-10x más rápido) |
| **Tamaño del ejecutable** | Grande | Pequeño |
| **Uso de memoria** | Alto | Bajo |
| **Capacidad de depuración** | Excelente | Limitada |
| **Comprobación de buffer overflows** | Sí | No |
| **Estado del código** | Exactamente igual al código fuente | Reorganizado y optimizado |

## Explicación detallada

### 1. Optimización
- **Debug**: El compilador mantiene el código lo más fiel posible al original para facilitar la depuración.
- **Release**: El compilador realiza numerosas optimizaciones como:
  - Inlining de funciones
  - Desenrollado de bucles
  - Eliminación de código muerto
  - Optimización de registros
  - Vectorización (SIMD)

### 2. Símbolos de depuración
- **Debug**: Incluye información completa sobre variables, líneas de código, etc.
- **Release**: Típicamente no incluye esta información, o la coloca en archivos PDB separados.

### 3. Macros y aserciones
- **Debug**: Define _DEBUG, permitiendo código como:
  ```cpp
  #ifdef _DEBUG
      // Código que solo se ejecuta en debug
  #endif
  ```
- **Release**: Define NDEBUG, que desactiva automáticamente las aserciones:
  ```cpp
  assert(x > 0);  // No hace nada en Release
  ```

### 4. Comprobaciones en tiempo de ejecución
- **Debug**: Incluye verificaciones de:
  - Acceso a memoria liberada
  - Desbordamiento de buffer
  - Validación de iteradores
  - Uso de memoria no inicializada
- **Release**: Estas comprobaciones se eliminan para mejorar el rendimiento.

### 5. Impacto en el experimento de MergesortHibrido
Las pruebas de rendimiento para determinar el valor óptimo de K:
- Deberían realizarse en **Release** para obtener resultados representativos del rendimiento real.
- Los tiempos en **Debug** serán mucho más lentos y podrían llevar a conclusiones erróneas sobre el valor óptimo de K.
