int enA = 9; 

int in1 = 8;

int in2 = 7; 


int enB = 3; 

int in3 = 5; 

int in4 = 4; 

void setup(){

	pinMode(enA, OUTPUT); 
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	

	digitalWrite(in1, LOW); 
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}



void loop() {

  

  digitalWrite(enA, HIGH); 
  digitalWrite(enB,HIGH);
  
	digitalWrite(in1, HIGH); 
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);

	digitalWrite(in4, LOW);
	delay(2000); 
  
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH); 

	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH); 


	delay(2000); 

	
	
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
        delay(2000); 
}