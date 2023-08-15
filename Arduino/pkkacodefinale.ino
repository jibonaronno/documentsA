#include<LiquidCrystal.h>
#include <SD.h>
#include <SPI.h>

File myFile;

LiquidCrystal lcd(10, 9, 7, 6, 5, 4); // rs,e,db4-7

float rev = 0;
int rpm = 0;
int pinCS = 3;
float previous = 0;
float _time = 0;
float ti = 0;
int ButtonValue = 0;
int Button = 13;
int count = -1;
int relay1 = A4;
int relay2 = A5;


void Interrupt() //interrupt service routine
{
  rev++;
}

void setup()
{
  analogWrite(relay1, 0);
  analogWrite(relay2, 0);
  //pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  analogWrite(A0, 30);
  //Serial.begin(9600);
  //pinMode(pinCS, OUTPUT);
  pinMode(2, INPUT);
  pinMode(8, OUTPUT);
  //   SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  // Create/Open file
  myFile = SD.open("data.txt", FILE_WRITE);

  //   if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    //     Write to file
    myFile.print("Time    ");
    myFile.println("RPM");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening data.txt");
  }

  //  Reading the file
  myFile = SD.open("data.txt");
  if (myFile) {
    Serial.println("Read:");
    //   Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else {
    Serial.println("error opening data.txt");
  }
  attachInterrupt(digitalPinToInterrupt(2), Interrupt, RISING); //attaching the interrupt
}

void loop()
{

  if ((millis() - previous) >= 500) {

    detachInterrupt(digitalPinToInterrupt(2));
    ti += 0.5;

    // no of wings of rotating object, for disc object use 1 with white tape on one side
    _time = (millis() - previous) / 1000; //time in sec
    //rpm = ((double)rev) / ((double)_time) ; //calculates rpm
    rpm = (rev / _time) * 60 / 25 ; //calculates rpm

    previous = millis(); //saves the current time
    //rev = 0;
    if (rpm % 10 <= 5)
    {
      rpm = (rpm / 10) * 10;
    }
    else
    {
      rpm = (((rpm + 10) / 10) * 10);
    }
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("S");
    lcd.setCursor(4, 1);
    lcd.print("RPM");
    lcd.print(" ");
    lcd.print(rpm);
    if (rpm > 350 && rpm < 400) 
    {
      //analogWrite(relay1, 800);
      count=0;
      //analogWrite(relay2, 0);
      digitalWrite(8, LOW); //HIGH
   
      //delay(2000);
             
    }
    else {
      digitalWrite(8, HIGH); //LOW
      
      //count =1;
    }
    ButtonValue = digitalRead(Button);

    if (ButtonValue != 0)
    {

      count++;
      delay(300);
      
    }


    if (count % 2 == 0 && count >= 0)
    {
      analogWrite(relay1, 800);
      analogWrite(relay2, 0);
      
    }
    else if (count % 2 != 0 && count >= 0)
    {
      analogWrite(relay1, 0);
      analogWrite(relay2, 800);
      
    }

    
    //Serial.println(rev);
    myFile = SD.open("data.txt", FILE_WRITE);
    if (myFile) {
      myFile.print(ti);
      myFile.print("     ");
      myFile.println(rpm);
      myFile.close(); // close the file
    }

    Serial.println(rpm);
    rev = 0;
    attachInterrupt(digitalPinToInterrupt(2), Interrupt, RISING);
  }
}
