#include <Metro.h>
int sensorPin = A1;    // select the input pin for the potentiometer
int ledPin = 13;      
int sensorRead = 0;  // variable to store the value coming from the sensor
int sensorReadTotal = 0;    //variable to store our average of readings until we increment the dosage
int sensorReadCount = 0;  //use for the average
int dosageTotal = 0;
// Instantiate a metro object and set the interval to 100 milliseconds (0.1 seconds).
Metro metroSensor = Metro(100); 
// Instantiate another metro object and set the interval to 1 second
Metro metroDosage = Metro(1000); 
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
}
void loop() {
  //sensor update
  if (metroSensor.check() == 1) {
    // read the value from the sensor:
    sensorRead = analogRead(sensorPin);
    sensorReadCount++;
    int sensorReadPercent =  map(sensorRead,0,1024,100,0); //make it more easy to grok
    sensorReadTotal = sensorReadTotal + sensorReadPercent;
    int sensorCurAvg = sensorReadTotal / sensorReadCount;   //switch to float later if needed 
    //Serial.print(sensorReadCount);
    //Serial.print(":");
    //Serial.print(sensorRead);
    //Serial.print("->");
    //Serial.print(sensorReadTotal);
    //Serial.print("->");
    //if (sensorCurAvg <10) Serial.print("0");
    //Serial.print(sensorCurAvg);
    //Serial.print(" ");
  }
  //dosage update
  if (metroDosage.check() == 1) { 
    //Serial.print(dosageTotal);
    //Serial.print("+");
    int dose =  sensorReadTotal / sensorReadCount; //switch to float later if needed
    dosageTotal = dosageTotal + dose; 
    sensorReadCount = 0;
    sensorReadTotal = 0;
    //Serial.print(dose);
    //Serial.print("=");
    Serial.println(dosageTotal);
  }
}
