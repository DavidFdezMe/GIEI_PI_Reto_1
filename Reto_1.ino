//Librerias
#include <Servo.h>.

//Piness
#define trigPin 10
#define echoPin 11
#define servoPin 12

long duracion;
int distancia;

Servo myServo;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
}

int calcularDistancia(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia= duracion*0.01723;
  return distancia;
}

//Funcion radar
void radar(){
   for(int i=0;i<=120;i++){
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();
    Serial.print(i);
    Serial.print("º | ");
    Serial.print(distancia);
    Serial.print(" cm");
  }

  for(int i=120;i>0;i--){  
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();
    Serial.print(i);
    Serial.print("º | ");
    Serial.print(distancia);
    Serial.print(" cm");
  }
}

void loop() {

 
}
