#include <Servo.h>

#include <NewPing.h>
#include <SparkFun_TB6612.h>
#include <DHT.h>
#include <DHT_U.h>

#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9
#define DHTPIN A1
#define DHTTYPE DHT11

const int offsetA = 1;
const int offsetB = 1;

#define MAX_DISTANCE 200

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  myServo.attach(9);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0, i<=180, i++){
    myServo.write(i)
    delay(50)
    
  }

}
