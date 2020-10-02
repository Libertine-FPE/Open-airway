
// include the library code:
#include <LiquidCrystal.h>
#include <stdio.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5;       //DEFINES THE PINS OF THE LCD SCREEN BASED ON DATA SHEET
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//analog pin
int sensorPin = A2;                                             // POT analog input pin  
int sensorPin1 = A3;                                             // POT analog input pin    

float sensorValue = 0;                                          // variable to store the value coming from the BPM Rate sensor
float sensorValuea = 0;                                          // variable to store the value coming from the BPM Rate sensor
float sensorValue1a = 0;                                          // variable to store the value coming from the Force Rate sensor
int sensorValue1 = 0;                                          // variable to store the value coming from the Force Rate sensor
int switchPin =10;                                              // Enable pin from push button
int buttonState = 0;                                            // variable for reading the pushbutton status
char buf[12];
char buf1[12];


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(switchPin, INPUT);                             
   
    lcd.begin(20,4);                                           // Defines the number of characters per line (20) and number of lines (4) of the screen     
    lcd.setCursor(0,0);
    lcd.print("      WELCOME!     ");                           // Splash Screen on startup
    lcd.setCursor(0, 2);
  // Print a message to the LCD.
    lcd.print("  Libertine BVA-V1");
    lcd.setCursor(0,3);
    delay(2000);                                              // Duration of splash screen
    lcd.clear();

}

void loop() {
  buttonState = digitalRead(switchPin);                       // Flash ENABLES when enable pin is HIGH
  if (buttonState==HIGH){                   
      lcd.setCursor(0,0);
      lcd.print("ENABLED ");
      delay(150);
      lcd.setCursor(0,0);
      lcd.print("          ");
      delay(150);
  }
  else
  {
      lcd.setCursor(0,0);
      lcd.print("DISABLED");
  }
  
  sensorValuea = analogRead(sensorPin);                        // Read Analog pin for POT value and scale to 16bit and 5V 
  sensorValue=map(sensorValuea,0,1023,15,5);
  //sensorValue=(5+(5-5*sensorValuea/1023.0)*10/5);                             // Here instead of 5V you can multiply it by the scaling value you need for breath per min.  0--> 5 5-corresponds to 15 
  sensorValue1a = analogRead(sensorPin1);                        // Read Analog pin for POT value and scale to 16bit and 5V 
  sensorValue1=100+(5-5*sensorValue1a/1023)*500/5;                             // Here instead of 5V you can multiply it by the scaling value you need for breath per min. 100ml-->0V and 600ml-->5V   

//  if (sensorValue<0.1){                                         // LOWER LIMIT SATURATION: Here instead of 2V you can change it to the value of breath per min you need as the maximum
//    sensorValue=2;                                            // Here instead of 2V you can change it to the value of breath per min you need as the maximum
//  }
//    else if(sensorValue>4){                                   // UPPER LIMIT SATURATION:Here instead of 4V you can change it to the value of breath per max you need as the maximum       
//      sensorValue=4;                                          // Here instead of 4V you can change it to the value of breath per max you need as the maximum       
//    } 
//   else{
//    sensorValue=sensorValue; 
//  }
//  Serial.println(sensorValue);

  //LCD Display During running state.
  
  lcd.setCursor(0,1);
  lcd.print("BPM:  ");
  lcd.print(sensorValue,1);
  lcd.setCursor(0,2);
  lcd.print("TV :  ");  
  lcd.print(itoa(sensorValue1,buf1,10));
  lcd.setCursor(9,2);
  lcd.print("ml");
  lcd.setCursor(0,3);
  lcd.print("I:E:  ");  
  lcd.print(" 1:2");  
  

}
