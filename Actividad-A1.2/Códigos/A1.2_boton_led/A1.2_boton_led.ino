int button = 12;
int led = 4;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT); // Configuramos como entrada
  Serial.begin(9600);     // Se inicializa solo una vez
}

void loop()
{
  int estado = digitalRead(button); // Guardamos la lectura continua
  Serial.print("Estado de boton: "); 
  Serial.println(estado);
  delay(100);

  // Evaluamos el estado actual del botón en cada ciclo
  if (estado == 1) {
    digitalWrite(led, 0);  
  } else {
    digitalWrite(led, 1);
  }
}