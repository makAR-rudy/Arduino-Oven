#include <Metro.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int sensorPin = A1;    // select the input pin for the sensor   
int sensorRead = 0;  // variable to store the value coming from the sensor
int sensorReadTotal = 0;    //variable to store our average of readings until we increment the dosage
int sensorReadCount = 0;  //use for the average
int dosageTotal = 0;
// Instantiate a metro object and set the interval to 100 milliseconds (0.1 seconds).
Metro metroSensor = Metro(100); 
// Instantiate another metro object and set the interval to 1 second
Metro metroDosage = Metro(1000); 
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;
}
void setup() {
   lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Dosage Total"); // print a simple message
  Serial.begin(9600);
}
void loop() 
{
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(dosageTotal);      // display dosage


 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
{
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }
  //sensor update
  if (metroSensor.check() == 1) {
    // read the value from the sensor:
    sensorRead = analogRead(sensorPin);
    sensorReadCount++;
    int sensorReadPercent =  map(sensorRead,0,1024,0,100); //make it more easy to grok
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
