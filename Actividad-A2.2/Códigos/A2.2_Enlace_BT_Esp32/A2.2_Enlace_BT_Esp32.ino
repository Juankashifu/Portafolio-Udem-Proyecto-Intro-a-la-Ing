#include "BluetoothSerial.h"

// Verifica que el Bluetooth esté habilitado en la placa
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error "Bluetooth no está habilitado. Revisa que sea un ESP32 original."
#endif

BluetoothSerial SerialBT;

const int LED = 32;  // Cambia a 4 si usas LED externo

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