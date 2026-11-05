const int PIN_A = 13;     // botón izquierdo
const int PIN_B = 12;     // botón central
const int PIN_MODO = 11;  // botón derecho
const int PIN_LED = 5;

int modo = 0;                 // 0 = AND, 1 = OR, 2 = NOT
bool ultimoEstadoModo = false;
int ultimaSalida = -1;

void setup() {
  pinMode(PIN_A, INPUT);      // pull-down externo
  pinMode(PIN_B, INPUT);
  pinMode(PIN_MODO, INPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Funcion actual: AND");
}

void loop() {
  bool a = (digitalRead(PIN_A) == HIGH);      // true si está presionado
  bool b = (digitalRead(PIN_B) == HIGH);
  bool botonModo = (digitalRead(PIN_MODO) == HIGH);

  if (botonModo && !ultimoEstadoModo) {
    modo = (modo + 1) % 3;
    ultimaSalida = -1;
    delay(50);
  }
  ultimoEstadoModo = botonModo;

  bool salida = false;
  const char* nombre;

  switch (modo) {
    case 0: salida = a && b; nombre = "AND"; break;
    case 1: salida = a || b; nombre = "OR";  break;
    case 2: salida = !a;     nombre = "NOT (usa solo boton A)"; break;
  }

  digitalWrite(PIN_LED, salida);

  int estado = (modo * 100) + (a * 10) + b;
  if (estado != ultimaSalida) {
    ultimaSalida = estado;
    Serial.print("Funcion: ");
    Serial.print(nombre);
    Serial.print(" | A=");
    Serial.print(a);
    Serial.print(" B=");
    Serial.print(b);
    Serial.print(" -> LED=");
    Serial.println(salida);
  }
}