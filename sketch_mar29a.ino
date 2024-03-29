//Motor Setup:-
#include <SparkFun_TB6612.h>
#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9
const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
//Ultrasonic Setup:-
#include <Bonezegei_HCSR04.h>
const int TRIGGER_PIN = 26;
const int ECHO_PIN = 27;
Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);
int d=0;

//DHT Setup:-
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


//Servo Setup:- 
#include <Servo.h>
Servo myservo;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int t = dht.readTemperature();
  Serial.print(t, ",");
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print(pos, ",");
    delay(15);
    d=ultrasonic.getDistance();
    Serial.print(d);
    if (d<=20; 0<pos<90){
      brake(motor1, motor2);
      motor1.drive(255, 1000);
    }
    else if(d<=20; 0<pos<180){
      brake(motor1, motor2);
      motor2.drive(255, 1000);
    }
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    Serial.print(pos, ",");
    d=ultrasonic.getDistance();
    Serial.print(d);
    delay(15);                       // waits 15 ms for the servo to reach the position
    if (d<=20; 0<pos<90){
      brake(motor1, motor2);
      motor1.drive(255, 1000);
    }
    else if(d<=20; 0<pos<180){
      brake(motor1, motor2);
      motor2.drive(255, 1000);
    }
    }
  if(Serial.read()=="f"){
    forward(motor1, motor2, 200);
    delay(50);
    brake(motor1, motor2);
  }
  if(Serial.read()=="b"){
    forward(motor1, motor2, -200);
    delay(50);
    brake(motor1, motor2);
  } 
  if(Serial.read()=="r"){
  right(motor1, motor2, 500);
  delay(50);
  brake(motor1, motor2);
  }
  if(Serial.read()=="l"){
  left(motor1, motor2, 500);
  delay(50);
  brake(motor1, motor2);
  }
  if(Serial.read()=="s")
  brake(motor1, motor2);
  }

