/*
Actividad Realizada por:
Oliver Martin Dostert Pérez
David Fernández Mesa
Ángel Ortega Lucena

Para la asignatura de Procesadores integrados
*/


//Librerias
#include <Servo.h>.

//Piness
#define trigPin 10
#define echoPin 11
#define servoPin 12

//LEDs
#define LED 3 
#define GREEN_LED 8  //  LED verde
#define YELLOW_LED 9  //  LED amarillo
#define RED_LED 7  //  LED rojo

//Botones
Button boton1=Button(5);
Button boton2=Button(4);
Button boton3=Button(6);

unsigned long t1;

void botones(){ 
  if (boton1.pressed()){  //Encendido
    digitalWrite(LED,HIGH);
  } 
  if (boton2.pressed()){ //Apagado
    digitalWrite(LED,LOW);
  }
  if(boton3.pressed()) {   
    if(millis()>= t1+250){             
  		digitalWrite(LED, !digitalRead(LED));
    	t1+=250;
    }
  }
}

long duracion;
int distancia;

Servo myServo;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);


  boton1.begin();
  boton2.begin();
  boton3.begin();
  pinMode(LED,OUTPUT);
}
}

// Función para calcular la distancia usando el sensor ultrasónico
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

// Función para manejar los LEDs según la distancia medida
void LED() {
  if (distancia > 60) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  } else if (distancia > 30 && distancia <= 60) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else if (distancia <= 30) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
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

     LED(); //Llama a la función LED para que tome la variable de distancia desde aquí, ya que se trata de una variable local
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
  botones(); 
  radar();
}
