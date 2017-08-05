/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int coin = ; //insert pin number for coin input signal
int button1 = ; //button to press for player 1
int button2 = ; //button to press for player 2

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome!!!");
  pinMode(coin,INPUT);
  pinMode(mode,INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("Insert Coin to eat");
  if(digitalRead(coin))
  {
    lcd.print("Press button1 for single mode, button2 for multiplayer mode");
    for(int i = 0; i<36; i++)
    {
      lcd.scrollDisplayLeft();
      delay(200);
    }
    digitalRead(button1);
    digitalRead(button2);
    
    /* multi player mode*/
    if(button2 == HIGH) 
    {
      int score1, score2;
      score1 = score2 = 0;

      do{
          lcd.clear();
          lcd.setCursor(0, 0);  // top left
          lcd.print("HOME");
          lcd.setCursor(15, 0);  //top right
          lcd.print("AWAY");
          lcd.setCursor(0, 1);  //bottom left
          lcd.print(score1);
          lcd.setCursor(15, 1);  //bottom right
          lcd.print(score2);      
      do{
            button1 = button2 = 0;
      
            if(digitalRead(button1))
            { 
              score1++;
              //insert all puri dispensing steps
            }
            
            if(digitalRead(button2))
            {
              score2++;
              //insert all puri dispensing steps
            } 
            }while((score1+score2)%10);
      lcd.print("Insert coin to continue");
    }while(digitalRead(coin));
   }   
 /* single player mode */ 
    else   
    {
       // insert all functions of pani puri dispensing
       lcd.clear();
       lcd.print("PURI");
       delay(500);
       lcd.clear();
       lcd.print("PRICK");
       delay(500);
       lcd.clear();
       lcd.print("ALOO");
       delay(500);
       lcd.clear();
       lcd.print("PAANI");
       delay(500);
       lcd.clear();
       lcd.print("EAT, YOU MOFO");
       delay(500);
       lcd.clear();
       lcd.print("  :)  ");
       delay(500);
       
    }
    
  }
  }
}

