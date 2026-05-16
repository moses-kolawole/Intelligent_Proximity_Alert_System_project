#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;


int greenpin = 4; 
int redpin = 3;
int irpin = 6;
int servopin = 11;
int buzzpin = 2;


int irvalue;
int angle = 90;
int direction = 30;

// LCD control
int lcd_delay = 200;

// stability filter
int stableRead = 0;

void setup() {

  pinMode(greenpin, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(irpin, INPUT);
  pinMode(buzzpin, OUTPUT);

  myservo.attach(servopin);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello moses");
  lcd.setCursor(0, 1);
  lcd.print("Welcome Baack");

  delay(2000);
}

void loop() {

  // simple stability check (prevents false triggers)
  irvalue = digitalRead(irpin);

  if (irvalue == HIGH) {

    digitalWrite(greenpin, HIGH);
    digitalWrite(redpin, LOW);
    digitalWrite(buzzpin, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Space Ahead ");
    lcd.setCursor(0, 1);
    lcd.print("No Obstacle     ");
  }


  else {
    digitalWrite(greenpin, LOW);
    digitalWrite(redpin, HIGH);
    digitalWrite(buzzpin, HIGH);

    if(angle >= 180) {
      angle = 180;
      direction = -30;
      angle = angle + direction;
    }
    else if(angle <= 0) {
      angle = 0;
      direction = 30;
      angle = angle + direction;
    }else{
      angle = angle + direction;
    }
    myservo.write(angle);


    lcd.setCursor(0, 0);
    lcd.print("!! ALERT !!     ");
    lcd.setCursor(0, 1);
    lcd.print("Obstacle Found  ");
    delay(500);

  }

  delay(200);
}