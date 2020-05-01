#include "RunningAverage.h"

RunningAverage myRA(10);
int samples = 0;
int sensorPin = A1;
int sensorValue = 0;

void setup(void) 
{
  Serial.begin(9600);
  myRA.clear(); // explicitly start clean
}

void loop(void) 
{
  long sens = analogRead(sensorPin) ;
  myRA.addValue(sens * .1);
  samples++;
  Serial.println(myRA.getAverage(), 3);

  if (samples == 300)
  {
    samples = 0;
    myRA.clear();
  }
  delay(100);
}
