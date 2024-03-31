#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 13
#define BIN1 4
#define AIN2 7
#define BIN2 5
#define PWMA 10
#define PWMB 11
#define STBY 12
#define trigPin A5
#define echoPin 2
#define DHTPIN 9
#define DHTTYPE DHT11
// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = -1;
const int offsetB = -1;
long duration;
int distance;
int d;
char input;
int i=172;
int temp;
// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Servo myServo;
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
 //Nothing here
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 dht.begin();
}


void loop(){
  d=calculateDistance();
  temp=dht.readTemperature();
  if (Serial.available()>0){
    input=Serial.read();
  }
  if (d<=20){
    brake(motor1, motor2);
    if (input=='R'){
    motor1.drive(200);
    }
    else if (input=='L'){
    motor2.drive(200);
    }
    else if (input=='B'){
    forward(motor1, motor2, -200);
    }
  }
  else if (input=='S'){
    brake(motor1, motor2);
  }
  else if (input=='F'){
    forward(motor1, motor2, 200);
  }
  else if (input=='R'){
    motor1.drive(200);
  }
  else if (input=='L'){
    motor2.drive(200);
  }
  else if (input=='B'){
    forward(motor1, motor2, -200);
  }
    delay(1000);
    Serial.print(i);
    Serial.print(",");
    Serial.print(d);
    Serial.print("/");
    Serial.print(temp);
    Serial.print(".");
}
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}