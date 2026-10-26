// Fusion: HC-SR04 + buzzer + control de 2 motores con puente H
// Arduino Uno
//
// Motor izquierdo  (M1) -> OUT1/OUT2
// Motor derecho    (M2) -> OUT3/OUT4

const uint8_t TRIG_PIN = 12;
const uint8_t ECHO_PIN = 11;
const uint8_t BUZZER_PIN = 10;

// L293D
const uint8_t ENA = 9;  // PWM canal A
const uint8_t IN1 = 8;
const uint8_t IN2 = 7;
const uint8_t ENB = 6;  // PWM canal B (evita conflicto con tone() en Timer2)
const uint8_t IN3 = 5;
const uint8_t IN4 = 4;

unsigned long lastBeepMs = 0;

float measureDistanceCm();
void forward(uint8_t speedPwm);
void backward(uint8_t speedPwm);
void stopMotors();
void beepEvery(unsigned long intervalMs, unsigned int freqHz);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

void loop() {
  const float cm = measureDistanceCm();

  // Si no hay lectura válida, avance suave por seguridad.
  if (cm <= 0) {
    forward(120);
    noTone(BUZZER_PIN);
    delay(80);
    return;
  }

  if (cm <= 15.0) {
    // Muy cerca: alerta rápida y retroceso breve
    stopMotors();
    beepEvery(120, 1800);
    delay(100);

    backward(170);
    delay(250);
    stopMotors();
    delay(80);
  } else if (cm <= 40.0) {
    // Distancia media: avance lento + beep intermitente
    forward(140);
    beepEvery(350, 1200);
    delay(80);
  } else {
    // Lejos: avance normal sin alarma
    forward(200);
    noTone(BUZZER_PIN);
    delay(80);
  }
}

float measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Timeout ~25 ms (aprox 4 m)
  const unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (duration == 0) {
    return -1.0;
  }

  return (duration * 0.0343f) / 2.0f;
}

void forward(uint8_t speedPwm) {
  analogWrite(ENA, speedPwm);
  analogWrite(ENB, speedPwm);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward(uint8_t speedPwm) {
  analogWrite(ENA, speedPwm);
  analogWrite(ENB, speedPwm);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void beepEvery(unsigned long intervalMs, unsigned int freqHz) {
  const unsigned long now = millis();

  if (now - lastBeepMs >= intervalMs) {
    tone(BUZZER_PIN, freqHz, 70);
    lastBeepMs = now;
  }
}
