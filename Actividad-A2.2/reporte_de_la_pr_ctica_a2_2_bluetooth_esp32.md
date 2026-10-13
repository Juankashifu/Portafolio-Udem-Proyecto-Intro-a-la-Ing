# 📚 Actividad A2.2: Enlace Bluetooth de una ESP32

> Comunicación inalámbrica mediante el protocolo Bluetooth Classic (SPP) con ESP32 como base para el desarrollo del control del rover de competencia (UDEM).

---

## 1) Resumen

- **Materia:** Proyectos Intro a la Ingeniería
- **Profesor:** Dr. Antonio Martínez Torteya
- **Equipo:** 
  - Juan Carlos Valdés Pérez
  - Antonio Isidoro Ureña Chaidez
  - Marcelo Cantú Palacios
  - Sofía Posask
- **Fecha:** 12/10/2026
- **Placa:** ESP32 DevKit V1 (Espressif Systems)
- **Descripción breve:** Implementación de un enlace de comunicación inalámbrica vía Bluetooth Classic (Perfil SPP) entre un dispositivo móvil Android y un microcontrolador ESP32. Se sustituyó el módulo HC-05/Arduino debido a fallas mecánicas de falso contacto en los módulos provistos, optando por el hardware integrado del ESP32 para sentar la arquitectura de control inalámbrico del rover de competencia de la UDEM.

---

## 2) Introducción

El presente reporte documenta el desarrollo y la implementación del protocolo de comunicación inalámbrica Bluetooth en un SoC (System on Chip) ESP32. Originalmente, la práctica planteaba el uso de una placa Arduino acoplada a un módulo transceptor Bluetooth externo (tipo HC-05/HC-06). Sin embargo, tras detectar falsos contactos e inestabilidad en las conexiones físicas de los módulos externos disponibles, y en consulta directa con el Dr. Antonio Martínez Torteya, se tomó la decisión de migrar la práctica hacia el ESP32.

El ESP32 incorpora nativamente conectividad Bluetooth Classic y Bluetooth Low Energy (BLE) en el propio microcontrolador, eliminando el ruido y la inestabilidad de un bus cableado externo. Adicionalmente, esta solución resulta directamente aplicable al proyecto integrador del equipo: la construcción y teleoperación de un *rover* para la competencia interna de la UDEM.

El objetivo principal de esta práctica es conocer el funcionamiento del protocolo Bluetooth Classic bajo el perfil de puerto serie (*Serial Port Profile* - SPP), configurar el ESP32 para actuar como esclavo receptor de datos y controlar el estado lógico de un actuador (LED) mediante comandos enviados desde una terminal en un smartphone Android.

---

## 3) Metodología

### 3.1 Conexiones y Justificación Técnica

**Componentes utilizados y justificación técnica:**

- **Microcontrolador ESP32 (DevKit V1):** Microcontrolador de 32 bits dual-core con conectividad Wi-Fi y Bluetooth integrada. Para esta prueba se utiliza el modo **Bluetooth Classic (SPP)**, el cual emula un puerto serie transparente ($UART$) sobre la interfaz de radiofrecuencia (2.4 GHz).
- **1 LED (Diodo Emisor de Luz):** Indicador visual para la verificación de recepción de comandos digital ('1' para encender, '0' para apagar).
- **1 Resistencia de 220 Ω (Limitadora para el LED):** Suponiendo una caída de voltaje directa ($V_f$) de 2.0 V para el LED e impulsado por el nivel lógico de 3.3 V de las salidas GPIO del ESP32:
  $$R = \frac{V_{\text{GPIO}} - V_f}{I_f} = \frac{3.3\text{ V} - 2.0\text{ V}}{0.0058\text{ A}} \approx 224\ \Omega$$
  Se utiliza un resistor de **220 Ω**, garantizando una corriente segura de aproximadamente $5.9\text{ mA}$, muy por debajo del límite máximo por GPIO del ESP32 (20-40 mA).
- **Dispositivo Móvil (Android) con app Serial Bluetooth Terminal:** Actúa como maestro Bluetooth para la transmisión de caracteres ASCII a través de la terminal virtual.

**Descripción de las conexiones físicas:**

- **Circuito de Control del LED:** El ánodo del LED se conecta al **GPIO 32** del ESP32. El cátodo se conecta a través del resistor de 220 Ω al riel de tierra común (**GND**).
- **Alimentación y Programación:** El ESP32 se conecta y energiza vía puerto USB (5V) desde la computadora para la carga de código e inspección de logs vía Monitor Serie en `115200 baudios`.

**Diagrama de conexiones:**
![Diagrama de conexiones ESP32 Bluetooth](Recursos/imgs/Circuito_Bluetooth.png)

*(Nota: El diagrama esquemático editable se encuentra adjunto en la carpeta `/Recursos/imgs/` del repositorio).*

---

### 3.2 Código y Protocolo de Comunicación

#### Alternativas de Protocolos Bluetooth en ESP32
Para determinar la mejor arquitectura de control para el *rover*, se evaluaron las tres modalidades compatibles con el ESP32:
1. **Bluetooth Classic (SPP):** Seleccionado para esta práctica. Emula una conexión Serie ($UART$). Es ideal para comunicación transparente con celulares Android sin requerir lógica compleja de atributos.
2. **Bluetooth Low Energy (BLE):** Enfocado en bajo consumo de energía y transmisión de paquetes pequeños mediante servicios/características (GATT). Adecuado para iOS/Web, pero requiere mayor infraestructura de código.
3. **Bluepad32:** Librería especializada para conectar mandos comerciales (PS4 / Xbox) directamente al ESP32 vía Bluetooth, alternativa a evaluar para el manejo avanzado del *rover*.

#### Explicación del Código

**Directivas y Librerías:**
Se incluye la librería nativa `#include "BluetoothSerial.h"`, la cual encapsula la pila de protocolos Bluedroid de Espressif en funciones equivalentes a la librería estándar `Serial` (como `.available()`, `.read()`, `.println()`). Se incluye una verificación mediante la directiva `#if !defined(...)` para asegurar que el soporte Bluetooth esté activo en el entorno de compilación.

**Configuración (`setup()`):**
- `Serial.begin(115200)`: Inicializa la consola de depuración cableada.
- `pinMode(LED, OUTPUT)`: Configura el GPIO 32 como salida digital.
- `SerialBT.begin("ESP32_Carrito")`: Inicializa la pila de radiofrecuencia Bluetooth asignándole el nombre con el que se anunciará en las búsquedas de dispositivos.

**Bucle Principal (`loop()`):**
- `SerialBT.available()`: Comprueba continuamente si existen bytes recibidos en el búfer circular del receptor Bluetooth.
- `char comando = SerialBT.read()`: Extrae el carácter ASCII enviado desde el teléfono móvil.
- **Evaluación condicional:** Si el comando recibido es `'1'`, establece la salida en nivel alto (`HIGH`) e informa al celular enviando el string `"LED encendido"`. Si el comando es `'0'`, conmuta la salida a nivel bajo (`LOW`) y responde `"LED apagado"`.

**Código Fuente:**

```cpp
#include "BluetoothSerial.h"

// Verifica que el Bluetooth esté habilitado en la placa
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error "Bluetooth no está habilitado. Revisa que sea un ESP32 original."
#endif

BluetoothSerial SerialBT;

const int LED = 32;  // Cambia a 4 o 2 si usas LED integrado/externo

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  SerialBT.begin("ESP32_Carrito");  // Nombre con el que aparecerá
  Serial.println("Listo. Busca 'ESP32_Carrito' en Bluetooth.");
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();

    if (comando == '1') {
      digitalWrite(LED, HIGH);
      SerialBT.println("LED encendido");
    }
    else if (comando == '0') {
      digitalWrite(LED, LOW);
      SerialBT.println("LED apagado");
    }
  }
}
```

---

## 4) Resultados

### 4.1 Evidencia de Conexión y Pruebas en Hardware

<p align="center">
  <img src="Recursos/imgs/Prueba_Bluetooth_Terminal.png" alt="Terminal Bluetooth Android" width="400">
</p>

<p align="center">

https://github.com/user-attachments/assets/6c6a2f0c-a02e-4ec5-8352-e64ee4a22516

</p>

> 📹 **Respaldo:** En caso de requerir descarga directa, el archivo multimedia se encuentra en [`Video_Funcionamiento_BT.mp4`](./Recursos/videos/Video_Funcionamiento_BT.mp4)

---

### Validación de Comportamiento

- **Vinculación y Emparejamiento:** El dispositivo móvil identificó la transmisión de baliza (*beacon*) con el SSID `"ESP32_Carrito"`. El enlace se estableció sin requerir PIN estático de confirmación.
- **Transmisión de Comandos:**
  - Al enviar la trama ASCII `'1'` desde la aplicación *Serial Bluetooth Terminal*, el GPIO 32 pasó a estado lógico de $3.3\text{ V}$, encendiendo el LED al instante y retornando la confirmación de texto `"LED encendido"` a la pantalla del smartphone.
  - Al enviar la trama ASCII `'0'`, el pin conmutó a $0\text{ V}$ (GND), apagando el indicador y devolviendo la respuesta `"LED apagado"`.
- **Estabilidad de Enlace:** A diferencia de las pruebas previas con el módulo externo HC-05 sobre el bus del Arduino, la conexión mantenida directamente dentro del SoC del ESP32 no presentó desconexiones por falso contacto ni pérdida de paquetes.

---

## 5) Conclusiones

- La migración de la arquitectura desde Arduino + módulo HC-05 hacia un módulo ESP32 integrado demostró ser una solución técnicamente superior, solucionando los problemas de falsos contactos mecánicos e inestabilidad en las líneas de datos.
- La librería `BluetoothSerial` simplificó el manejo del protocolo Bluetooth Classic SPP al abstraer la pila de comunicación en llamadas de puerto serie estándar, permitiendo una transmisión bidireccional estable.
- La exitosa prueba del control ON/OFF valida la capa de comunicación inalámbrica que servirá de fundamento para la siguiente etapa: la integración de puentes H (L298N o TB6612FNG) para el control direccional y de velocidad del *rover* en la competencia UDEM.