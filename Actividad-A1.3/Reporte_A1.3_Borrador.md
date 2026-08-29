# A1.3 Avances de Proyecto 2

## 1. Introducción
El presente reporte documenta la segunda fase de desarrollo de un sistema de entretenimiento interactivo. El objetivo principal de esta iteración es escalar el sistema inicial (de un solo botón y un LED) a una interfaz que integra 3 botones de distintos colores y 3 luces LED correspondientes. El sistema debe ser capaz de seleccionar y encender un LED de forma aleatoria, manteniendo este estado hasta que el usuario presione exclusivamente el botón del color asociado. Una vez presionado el botón correcto, el ciclo se reinicia seleccionando un nuevo LED al azar. Este avance sienta las bases lógicas para la futura implementación de contadores de aciertos, temporizadores y retroalimentación auditiva.

## 2. Metodología

### 2.1. Diseño de Hardware y Conexiones
Para la construcción del circuito se utilizaron los siguientes componentes:
*   **Microcontrolador:** [Modelo, ej. Arduino Uno] utilizado como cerebro del sistema.
*   **LEDs:** 3 diodos emisores de luz (colores [Color 1, Color 2, Color 3]).
*   **Botones:** 3 push buttons (pulsadores) asociados a cada color.
*   **Resistencias:** [Ej. 3 resistencias de 220 Ω para limitar la corriente de los LEDs y 3 de 10 kΩ para configuración pull-down de los botones].

**Justificación técnica:** 
[Aquí se redactará la justificación técnica basada en la Ley de Ohm para los LEDs y la necesidad de asegurar estados lógicos definidos (LOW/HIGH) en los pines de lectura de los botones].

![Diagrama de Conexiones del Sistema]([nombre_de_tu_imagen.jpg/png])
*Figura 1. Diagrama de conexiones implementado en Tinkercad.*

### 2.2. Diseño de Software

El código fuente fue estructurado para garantizar que la aleatoriedad y la lectura de los estados de los botones se ejecuten de manera eficiente y sin bloqueos innecesarios.

**Configuración Inicial (`setup`):**
[Aquí se explicará la configuración de los pines como `OUTPUT` e `INPUT`, así como la inicialización de la semilla para la función random].

**Lógica Principal (`loop`):**
[Aquí detallaremos cómo el sistema: 1) Selecciona un número aleatorio, 2) Enciende el LED correspondiente, 3) Entra en un estado de espera leyendo constantemente los botones, y 4) Ignora las pulsaciones incorrectas hasta detectar el botón que hace "match" con el LED activo].

```cpp
[Aquí se insertará el código fuente en C++]
```

## 3. Resultados y Funcionamiento
Al energizar el sistema, se comprobó que el comportamiento cumple con las especificaciones establecidas. Al encenderse un LED al azar, presionar los botones no correspondientes no altera el estado del sistema, demostrando un correcto filtrado de entradas incorrectas. Únicamente al presionar el botón del color correcto, el LED se apaga y el sistema genera una nueva selección aleatoria de forma inmediata.

A continuación, se presenta la evidencia en video del funcionamiento:
[Enlace al video demostrativo]

## 4. Conclusiones
[Aquí redactaremos la conclusión técnica sobre la integración de múltiples entradas y salidas con lógica condicional cruzada y aleatoriedad en sistemas embebidos].
