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
3. Resultados y Funcionamiento
Al energizar el sistema, se comprobó que el comportamiento cumple con las especificaciones establecidas. Al encenderse un LED al azar, presionar los botones no correspondientes no altera el estado del sistema, demostrando un correcto filtrado de entradas incorrectas. Únicamente al presionar el botón del color correcto, el LED se apaga y el sistema genera una nueva selección aleatoria de forma inmediata.

A continuación, se presenta la evidencia en video del funcionamiento:
[Enlace al video demostrativo]

4. Conclusiones
[Aquí redactaremos la conclusión técnica sobre la integración de múltiples entradas y salidas con lógica condicional cruzada y aleatoriedad en sistemas embebidos].
"""

file_path = "Reporte_A1.3_Borrador.md"
with open(file_path, 'w', encoding='utf-8') as f:
f.write(md_content)

print(f"[file-tag: {file_path}]")


```text?code_stdout&code_event_index=1
[file-tag: Reporte_A1.3_Borrador.md]

Tu archivo Markdown (borrador inicial) está listo.

Ícono de MD
Reporte_A1.3_Borrador
 MD 
Abrir
He analizado a detalle las instrucciones de la práctica A1.3 y la rúbrica de evaluación del Dr. Torteya. He generado un primer borrador / plantilla estructural del reporte para asegurar que cubrimos todos los criterios necesarios para alcanzar el nivel "Proficient" en la rúbrica (como la justificación técnica de las conexiones, explicaciones claras del código y evidencia directa).  
PDF
+ 1

Sin embargo, para poder adaptarme exactamente a tu estilo de redacción y completar la información técnica, necesito que me ayudes con lo siguiente:

1. El README de ejemplo:
Mencionaste que ibas a anexar un ejemplo de tu estilo de reporte, pero no se adjuntó en tu mensaje. Por favor, compárteme el texto de ese README (puedes pegarlo aquí directamente) para que yo pueda analizar cómo estructuras los párrafos, el tono que usas, si prefieres viñetas o texto continuo, etc.

2. Componentes y Conexiones (Hardware):

¿Qué microcontrolador utilizaste (ej. Arduino Uno, ESP32)?

¿Cuáles fueron los colores exactos de los 3 LEDs y los 3 botones?

¿A qué pines (números exactos) conectaste cada LED y cada botón?

¿Utilizaste resistencias físicas para los botones (pull-down/pull-up de 10kΩ) o activaste las resistencias internas del microcontrolador (INPUT_PULLUP)? ¿De qué valor fueron las resistencias para los LEDs?

¿Cómo se llama el archivo de imagen de tu diagrama de conexiones (ej. diagrama_tinkercad.png) para referenciarlo correctamente en el Markdown?

3. El Código (Software):
Por favor, pega aquí el código fuente completo que utilizaste. Con esto redactaré la explicación paso a paso del setup, el loop, y la lógica matemática detrás de la selección aleatoria y la validación de estados.

4. Evidencia:
¿Tienes el enlace de YouTube o Drive de tu video demostrativo para incluirlo en la sección de Resultados?

Una vez que me proporciones esta información y tu documento de ejemplo, reescribiré y refinaré este Markdown al 100% con tu propio estilo y con todos los fundamentos técnicos necesarios. ¡Quedo a la espera!




Gemini es una IA y puede cometer errores.

Analizando
Explicar
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
Reporte_A1.3_Borrador.md
Mostrando Reporte_A1.3_Borrador.md.
