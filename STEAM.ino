#include <Servo.h>

#include <NewPing.h>
#include <SparkFun_TB6612.h>
#include <DHT.h>
#include <DHT_U.h>

#define AIN1 8
#define BIN1 15
#define AIN2 12
#define BIN2 16
#define PWMA 11
#define PWMB 10
#define STBY 7
#define DHTPIN 13
#define DHTTYPE DHT11
#define TRIGGER_PIN 5
#define ECHO_PIN 4
const int offsetA = 1;
const int offsetB = 1;

#define MAX_DISTANCE 200

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  myServo.attach(9);
}

void loop() {
  for(int i=15;i<=165;i++){  
    myServo.write(i);
    delay(30);
    int distance = sonar.ping_cm();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    
    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print("/");
    Serial.print(dht11.readTemperature());
    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
    for(int i=165;i>15;i--){  
      myServo.write(i);
      delay(30);
      int distance = sonar.ping_cm();
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);
      Serial.print("/");
      Serial.print(dht11.readTemperature());
      Serial.print(".");
  }
    String sulfate = Serial.readString();
    int distance = sonar.ping_cm();
    if (distance<=15){
      brake(motor1, motor2);
      back(motor1, motor2, -150);
      motor1.drive(255, 1000); 
      }[
    else if (sulfate=="R"){
      motor1.drive(255,1000);
      delay(1000);
      brake(motor1, motor2);
    }
    else if (sulfate=="L"){
      motor2.drive(255,1000);
      delay(1000);
      brake(motor1, motor2);
    }
    else if (sulfate=="F"){
      forward(motor1, motor2, 150);
      delay(1000);
      brake(motor1, motor2);
    else if (sulfate=="S"){
      brake(motor1, motor2);
      delay(1000);
    }
    }
}
