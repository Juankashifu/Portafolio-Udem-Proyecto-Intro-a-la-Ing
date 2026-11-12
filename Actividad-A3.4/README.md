# 📚 Actividad A3.4: Avances de Proyecto 7 — Ensamblaje de Hardware y Soldadura

> Avance enfocado en la construcción física, dimensionamiento de chasis y ruteo de potencia para el minirrover del Rover Challenge Jr.

---

## 1) Resumen

- **Materia:** Proyectos Intro a la Ingeniería
- **Profesor:** Dr. Antonio Martínez Torteya
- **Equipo:** 
  - Juan Carlos Valdés Pérez
  - Antonio Isidoro Ureña Chaidez 
  - Marcelo Cantú Palacios
  - Sofía Posas
- **Fecha:** 12/11/2026
- **Placa:** ESP32
- **Descripción breve:** Ensamblaje físico y soldadura de componentes de control de motores (Puentes H MX1508) en el laboratorio de electrónica. Se definió la topología de alimentación dual y se realizó el dimensionamiento espacial en el chasis para integrar el microcontrolador, la matriz de 24 LEDs y el sistema de telemetría OLED sin realizar aún pruebas de código.

---

## 2) Introducción

El presente reporte documenta los avances correspondientes a la etapa inicial de ensamblaje físico del Proyecto 7. El objetivo general de este proyecto es construir un minirrover para el *Rover Challenge Jr.* de la UDEM, capaz de explorar un terreno simulado de Marte, localizar piedras de colores, identificarlas mediante sensores integrados y trasladarlas a una zona de recolección[cite: 5]. El rover debe operar con dimensiones máximas de 30x20 cm, procesar todo localmente y emitir señales visuales (LED) y auditivas acordes al color detectado[cite: 5].

Para esta actividad (A3.4), el enfoque fue exclusivamente de hardware. Las tareas consistieron en acudir al laboratorio de electrónica y robótica para soldar los puentes H, realizar el cableado inicial de potencia y estructurar la distribución espacial de los componentes recientemente adquiridos (luz de 24 LEDs, display OLED y portapilas). Este avance sienta las bases mecánicas y eléctricas para la futura programación e integración lógica del ESP32.

---

## 3) Metodología

### 3.1 Arquitectura de Componentes y Justificación Técnica

Para cumplir con las restricciones de tamaño[cite: 5] y garantizar la estabilidad electrónica del sistema, se tomaron las siguientes decisiones de diseño:

- **División del Sistema de Alimentación:**
  Se optó por una topología de fuentes aisladas para separar la etapa de control (lógica) de la etapa de potencia (cargas inductivas).
  - **Potencia (Motores):** Alimentados por un portapilas doble de baterías 18650 (aprox. 7.4 V). Los motores de corriente continua generan picos de consumo al arrancar o atascarse, además de ruido eléctrico (fuerza contraelectromotriz). Al dedicar una fuente de mayor amperaje y voltaje exclusivo para ellos, se asegura un torque óptimo.
  - **Lógica (Sensores y ESP32):** Alimentados por un portapilas de 4 baterías AA (aprox. 6 V). Esto garantiza que las caídas de tensión provocadas por los motores no afecten al ESP32 (evitando reinicios súbitos o *brownouts*) y proporciona un voltaje estable para el sensor de color y el display.

- **Puentes H (Módulos MX1508):**
  Se reemplazaron los tradicionales *drivers* (como el L298N) por los módulos MX1508. La justificación es triple:
  1. **Dimensión:** Son extremadamente compactos, lo cual es crítico para cumplir con el área máxima del vehículo (30x20 cm)[cite: 5].
  2. **Eficiencia:** Utilizan tecnología MOSFET en lugar de transistores bipolares (BJT), minimizando la caída de tensión interna y la disipación de calor.
  3. **Control Optimizado:** Permiten el control de dirección y modulación por ancho de pulso (PWM) utilizando únicamente 2 pines del microcontrolador por motor, optimizando los puertos disponibles del ESP32 para el resto de los periféricos.

- **Sensores e Indicadores:**
  - **Mini Display OLED:** Se comunicará vía I2C con el ESP32. Su función principal será fungir como interfaz de telemetría local para mostrar un contador en tiempo real de los colores detectados por el sensor de color TCS34725.
  - **Sensor TCS34725:** Encargado del reconocimiento cromático para validar si la piedra es roja, azul o verde[cite: 5].
  - **Matriz de 24 LEDs:** Elemento luminoso de alta intensidad para cumplir con la regla de encender una luz del mismo color que la piedra al realizar la detección[cite: 5], maximizando la visibilidad para los jueces.

### 3.2 Proceso de Ensamblaje (Laboratorio)

Durante esta sesión, no se implementó código de prueba. El trabajo se centró en la manipulación física de los componentes:

1. **Soldadura de Pines:** Se utilizaron cautines y soportes articulados con lupa ("tercera mano") en el laboratorio para soldar las regletas de pines a los puentes H MX1508 (evidenciado en las imágenes adjuntas). Se aseguró una soldadura cónica y brillante para evitar resistencias parásitas en la etapa de potencia.
2. **Dimensionamiento:** Se distribuyeron espacialmente los portapilas y la electrónica sobre el chasis del rover, evaluando los espacios para evitar interferencias con el mecanismo recolector que se implementará posteriormente[cite: 5, 6].

---

## 4) Resultados y Evidencia Física

Al tratarse de una fase de construcción, los resultados se evalúan mediante la calidad del ensamblaje y las conexiones. Se logró soldar exitosamente los módulos de control de motores y se dimensionaron las conexiones sin presentar cortos circuitos.

### 4.1 Evidencia del Laboratorio de Electrónica

A continuación, se muestran las fotografías del proceso de soldadura de los módulos MX1508 y el dimensionamiento en el chasis:

*(Nota: En el repositorio también se encuentra el archivo de video de la soldadura y las fotografías de los componentes en su empaque de llegada: luz LED, display OLED y los dos modelos de portapilas).*

<p align="center">
  <img src="Recursos/imgs/Foto 1 conexiones.jpeg" alt="Dimensionamiento y conexiones en el chasis" width="45%">
  <img src="Recursos/imgs/Foto 2 Soldando.jpeg" alt="Proceso de soldadura con lupa - Vista 1" width="45%">
</p>
<p align="center">
  <img src="Recursos/imgs/Foto 3 Soldando.jpeg" alt="Proceso de soldadura con lupa - Vista 2" width="45%">
  <img src="Recursos/imgs/Foto 4 Soldando.jpeg" alt="Proceso de soldadura con lupa - Vista 3" width="45%">
</p>

---

## 5) Conclusiones

La actividad A3.4 se completó de manera satisfactoria. La elección de aislar los circuitos de alimentación (7.4 V para motores y 6 V para lógica) es una base técnica sólida que evitará los problemas más comunes de inestabilidad en robótica móvil. Asimismo, el uso de los módulos MX1508 ahorrará espacio en el chasis y pines en el ESP32, facilitando la futura integración del bus I2C (para el OLED y el sensor TCS34725). 

Con el hardware de potencia soldado y el espacio dimensionado de forma óptima para no rebasar los 30x20 cm reglamentarios[cite: 5], el sistema se encuentra mecánicamente listo para iniciar la fase de cableado final y el desarrollo del software de control, lectura de color y telemetría visual.