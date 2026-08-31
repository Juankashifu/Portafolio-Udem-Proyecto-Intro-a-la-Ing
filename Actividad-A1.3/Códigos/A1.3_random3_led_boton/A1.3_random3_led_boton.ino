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