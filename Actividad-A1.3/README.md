# 📚 Actividad A1.3: Avances de Proyecto 2 — Sistema de 3 Botones y 3 LEDs

> Segunda etapa de un sistema de entretenimiento tipo juego de memoria, desarrollado con Arduino para la materia de Proyectos Intro a la Ingeniería (UDEM). En esta iteración se incorporan múltiples entradas/salidas y selección aleatoria.

---

## 1) Resumen

- **Materia:** Proyectos Intro a la Ingeniería
- **Profesor:** Dr. Antonio Martínez Torteya
- **Equipo:** Juan Carlos Valdés Pérez, Antonio Isidoro Ureña Chaidez, Marcelo Cantú Palacios, Sofía Posas
- **Fecha:** 31/08/2026
- **Placa:** Arduino Uno R3 (Elegoo)
- **Descripción breve:** Expansión del circuito inicial para controlar 3 LEDs (dos rojos y uno azul) mediante 3 botones (*push buttons*). El sistema enciende un LED al azar y evalúa de forma continua las entradas; solo al presionar el botón que corresponde exactamente al LED activo, este se apaga y se genera una nueva selección aleatoria.

---

## 2) Introducción

El presente reporte documenta la segunda fase del desarrollo de nuestro sistema de entretenimiento. [cite_start]Si bien en la entrega anterior se logró controlar un solo LED mediante un botón, esta nueva iteración escala la complejidad del hardware y del software al integrar 3 botones y 3 LEDs[cite: 10, 15]. 

[cite_start]El objetivo general del sistema en esta etapa es encender uno de los 3 LEDs de forma completamente aleatoria al iniciar el programa[cite: 17]. [cite_start]Dicho LED debe permanecer encendido hasta que el usuario presione de manera exclusiva su botón correspondiente[cite: 18]. [cite_start]Si se presiona un botón incorrecto, el sistema está programado para mantener su estado e ignorar la acción. [cite_start]Una vez que se acierta, la luz se apaga y se selecciona un nuevo color al azar de forma inmediata[cite: 19]. Este avance sienta las bases de la lógica condicional y aleatoria requerida para el juego de memoria final.

---

## 3) Metodología

### 3.1 Conexiones y Hardware

[cite_start]**Componentes utilizados y justificación técnica:**

- **1 Placa Microcontroladora:** Arduino Uno R3.
- **3 LEDs (2 Rojos, 1 Azul):** Actúan como los indicadores visuales del sistema.
- **3 Resistencias de 220 Ω (Limitadoras para los LEDs):** Como se justificó en la práctica anterior, el voltaje directo de los LEDs ronda los 2.0 V a 3.0 V. Aplicando la Ley de Ohm para la fuente de 5 V del microcontrolador:
  $$R = \frac{V_{\text{fuente}} - V_f}{I_f}$$
  Una resistencia de **220 Ω** fija una corriente segura de entre 10 mA y 14 mA, protegiendo a los diodos contra daños por sobrecorriente y al Arduino de exceder su capacidad de salida por pin.
- **3 Pulsadores (*Push Buttons*):** Interruptores momentáneos para la interacción del usuario.
- **3 Resistencias de 10 kΩ (Pull-Down para los botones):** Esenciales para evitar el estado de "pin flotante". Garantizan que el microcontrolador lea un cero lógico (LOW o 0 V) de manera estable cuando los botones están en reposo, filtrando el ruido electromagnético.
- **Protoboard y Jumpers:** Para el ensamblaje del circuito físico.

[cite_start]**Descripción de las conexiones físicas[cite: 26]:**

- **Circuito de Salida (LEDs):** Los ánodos (terminales positivas) de los tres LEDs se conectaron a los **Pines Digitales 4, 5 y 6** del Arduino. Los cátodos (terminales negativas) se conectaron en serie a sus respectivas resistencias de 220 Ω, cerrando el circuito hacia el riel de tierra (**GND**).
- **Circuito de Entrada (Botones):** Un extremo de cada pulsador se conectó al riel de **5V**. El extremo opuesto de cada uno se ramificó hacia dos puntos: a los **Pines Digitales 11, 12 y 13** para su lectura, y a sus respectivas resistencias pull-down de 10 kΩ hacia **GND**.

**Diagrama de conexiones:**
![Diagrama de conexiones]
(Recursos/imgs/Circuito_tinkercad.png)

[cite_start]*(Nota: El archivo de imagen se encuentra adjunto en el repositorio [cite: 27]).*

---

### 3.2 Diseño de Software

[cite_start]El código fuente implementa una lógica de arreglos paralelos y muestreo condicional para vincular los componentes de hardware sin bloquear la ejecución del microcontrolador[cite: 28, 29].

**Lógica de Vinculación (Arreglos):**
[cite_start]En lugar de manejar 6 variables sueltas, se utilizaron dos listas (arreglos) que comparten el mismo tamaño y orden lógico: una para los pines de los LEDs (4, 5, 6) y otra para los pines de los botones (11, 12, 13)[cite: 30]. [cite_start]De esta manera, el sistema sabe que el componente en la posición "0" de la lista de LEDs está emparejado obligatoriamente con el componente en la posición "0" de la lista de botones[cite: 30].

**Configuración Inicial (`setup`):**
Se iteran las listas para configurar todos los pines de manera eficiente. Los LEDs se declaran como salidas (`OUTPUT`) y se apagan inicialmente, mientras que los botones se configuran como entradas (`INPUT`). Adicionalmente, se genera una semilla aleatoria leyendo el "ruido" de un pin analógico desconectado (`analogRead(A0)`). Esto asegura que la secuencia de luces sea impredecible cada vez que se reinicia el sistema. Finalmente, se manda llamar a la función para encender el primer LED.

**Ejecución Principal (`loop`):**
[cite_start]El sistema guarda en memoria la posición (índice) del LED que se encuentra encendido actualmente[cite: 30]. En cada ciclo, el Arduino **únicamente** lee el estado del botón que comparte esa misma posición. 
- [cite_start]Si se presiona cualquier otro botón, el código lo ignora por completo, manteniendo el LED encendido.
- Si el botón correcto es presionado, el sistema apaga el LED, ejecuta un pequeño retardo (antirrebote) para asegurar que el usuario ha soltado el botón, y llama a la función de selección aleatoria.

**Selección Aleatoria Segura:**
La función que elige el nuevo LED utiliza un ciclo matemático (`do-while`) para generar números al azar. [cite_start]Su propósito es garantizar que el nuevo LED elegido nunca sea el mismo que se acaba de apagar, forzando al sistema a buscar un número distinto y haciendo el juego más dinámico[cite: 30].

**Código Fuente:**

```cpp
// Declaración de pines
const int numComponentes = 3;
const int leds[numComponentes] = {4, 5, 6};       // Pines de los LEDs
const int botones[numComponentes] = {11, 12, 13};   // Pines de los botones correspondientes

int ledActivo = -1; // Guarda el índice (0, 1 o 2) del LED encendido

void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(9600);

  for (int i = 0; i < numComponentes; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT); // Configuración Pull-Down externa
    digitalWrite(leds[i], LOW);
  }

  // Prende el primer LED al azar al encender el Arduino
  seleccionarNuevoLED();
}

void loop() {
  // Solo evalúa el botón que CORRESPONDE al LED encendido actualmente
  if (digitalRead(botones[ledActivo]) == HIGH) {
    
    // 1. Apaga el LED actual
    digitalWrite(leds[ledActivo], LOW);
    
    // Antirrebote y espera a que sueltes el botón correcto
    delay(200);
    while (digitalRead(botones[ledActivo]) == HIGH);
    delay(50);

    // 2. Enciende otro LED al azar
    seleccionarNuevoLED();
  }
  // Si presionas un botón incorrecto, el programa lo ignora y el LED se queda prendido
}

void seleccionarNuevoLED() {
  int nuevoLed;
  
  // Garantiza que el nuevo LED elegido no sea el mismo que se acaba de apagar
  do {
    nuevoLed = random(0, numComponentes);
  } while (nuevoLed == ledActivo);

  ledActivo = nuevoLed;
  digitalWrite(leds[ledActivo], HIGH);

  Serial.print("LED encendido: ");
  Serial.println(ledActivo + 1);
}
```
(Nota: El archivo fuente tipo .ino se encuentra adjunto en el repositorio ).  

---

## 4) Resultados

A continuación se presentan las evidencias de funcionamiento del sistema, demostrando el comportamiento esperado:

### 4.1 Demostración en Simulación (Digital)
<p align="center">
  <img src="Recursos/videos/Gif_Funcionamiento_Tinkercad.gif" alt="Demostración Digital en Tinkercad" width="600">
</p>

### 4.2 Demostración en Hardware (Físico)
<p align="center">

Actividad-A1.3/Recursos/videos/Video_Funcionamiento_Fisico.mp4

</p>
> 📹 **Respaldo:** En caso de requerir descarga directa, el archivo multimedia de funcionamiento físico se encuentra en [`Video_Funcionamiento_Fisico.mp4`](./Recursos/videos/Video_Funcionamiento_Fisico.mp4).

### Validación de Comportamiento

- **Aleatoriedad Inicial:** Al energizar el circuito, el sistema selecciona satisfactoriamente y sin intervención humana uno de los 3 LEDs (ya sea uno de los rojos o el azul).
- **Rechazo de Errores:** Se comprobó que al presionar botones no vinculados al LED activo, el circuito mantiene su estado de forma estable, sin parpadeos ni reinicios accidentales, ignorando exitosamente las entradas incorrectas.
- **Transición Exitosa:** Al accionar el botón correcto, el LED se apaga instantáneamente, se ejecuta el retardo de seguridad (antirrebote) y el sistema escoge un nuevo indicador luminoso al azar, validando la efectividad del bucle `do-while` para evitar la repetición del mismo LED.

---

## 5) Conclusiones

La implementación de la práctica A1.3 se concluyó con éxito, cumpliendo íntegramente con los requisitos técnicos de escalabilidad y control aleatorio. La transición de un sistema de lectura simple a un sistema que gestiona múltiples señales simultáneas mediante el uso de arreglos en C++ demostró ser altamente eficiente. 

El dimensionamiento del hardware mediante el uso de resistencias de 10 kΩ en configuración pull-down probó su eficacia al prevenir interferencias o lecturas "flotantes" entre los 3 botones montados en la misma protoboard. Asimismo, la lógica condicional que asocia los índices de los componentes permitió resolver el problema de interacción cruzada, garantizando que el sistema solo avance cuando la respuesta del usuario coincida con la salida activa. Este avance deja el hardware y la estructura algorítmica fundamental completamente preparados para la integración final de los contadores de aciertos, temporizadores y retroalimentación auditiva del juego de memoria.