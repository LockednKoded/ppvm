#include <TimerThree.h>

#include <TimerOne.h>

/*attempting interrupts*/

#include <LiquidCrystal.h>
#include <Servo.h>

/* PIN ASSIGNMENT  */

  int PD_Plus = 26;
  int PD_Minus = 27;

  int CD_Plus = 24;
  int CD_Minus = 25;

  int Hole_Plus = 30;
  int Hole_Minus = 31;
 
  int Aloo_Plus = 22;
  int Aloo_Minus = 23;

  int Aloo_Valve = 43;

  int pani = 47;    // RIP Pin 17

  int Token = 0;  //Analog Read pin A0
/*  int Token_VCC = 42;
  int Token_GND = 43; */

  int LED = 13; //Token accepted LED

  int M1_ENABLE = 28;  //enable pin for motor driver

  int f_agitate = 0;    //flag for the agitator
  int agitate_time = 16;  //time to set for agitator time


  //int Button = 3;

  /* For LCD Display*/
  /*  The circuit:
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
   * LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
   * 
  */

  // initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(8,9,4,5,6,7);
  int lcd_pot = 10;
  int lcd_rw = 11;
  int lcd_plus = 14;
  int lcd_minus = 15;
  
  /*Servo initialization*/
    Servo Main;
    Servo Second;
    int Main_pin = 2;
    int Sec_pin = 3;
    /*servo angles*/
    int MO = 20;  
    int MC = 90;
    int SO = 100;
    int SC = 10;

  /* Other Variables */

  int p = 0 , a = 0, h = 0, pu = 0;  //function counters.
  int button_count = 0;
  int token_status = 0;
  int mode = 0;
  int threshold = 95;  // LDR threshold

  //Token ka variable is for what?
  //int coin = 31; //insert pin number for coin input signal

  int button1 = 48;//button to press for player 1
  int button1_2 = 49;
  int button2 = 50;//button to press for player 2
  int button2_2 = 51;
   int button3 = 18;//button to press for player 2
  int button3_2 = 16;
  int score1 = 0;
  int score2 = 0;

  int coin =0; //this is for showing the INSERT COIN TO BEGIN statement only once.


void setup() {
  //LCD Setup
  // set up the LCD's number of columns and rows


  //for lcd pot contrast pin Vo
  pinMode(lcd_pot, OUTPUT);
  analogWrite(lcd_pot, 110);
  //for some mmore pins of lcd
  pinMode(lcd_rw, OUTPUT);
  digitalWrite(lcd_rw, LOW);
  pinMode(lcd_plus, OUTPUT);
  digitalWrite(lcd_plus, HIGH);
  pinMode(lcd_minus, OUTPUT);
  digitalWrite(lcd_minus, LOW);

  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);

  // doesn't work need to connect to vcc connected servo instead
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);

  pinMode(51, OUTPUT);
  digitalWrite(51, LOW);

    /*TOKEN POWER*/
  /*pinMode(Token_VCC,OUTPUT);
  digitalWrite(Token_VCC,HIGH);
  pinMode(Token_GND,OUTPUT);
  digitalWrite(Token_GND,LOW);*/

  /*this is for l293d enable high for aloo and pricker, the new motor driver needs no enable*/
  pinMode(M1_ENABLE,OUTPUT);   
  digitalWrite(M1_ENABLE,HIGH);

  lcd.begin(16, 2);

 
  // button setup
  pinMode(button1_2,OUTPUT);
  digitalWrite(button1_2,LOW);
  pinMode(button2_2,OUTPUT);
  digitalWrite(button2_2,LOW);

  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  pinMode(button2, INPUT);
  digitalWrite(button2, HIGH);

  pinMode(button3_2,OUTPUT);
  digitalWrite(button3_2,LOW);
  pinMode(button3, INPUT);
  digitalWrite(button3, HIGH);

  // Servo setup
  Main.attach(Main_pin);
  Second.attach(Sec_pin);
  Main.write(MC);       //MF closed
  Second.write(SC);     //SF closed

 // Circular Disk (CD) setup
  pinMode(CD_Plus, OUTPUT);
  pinMode(CD_Minus, OUTPUT);
  digitalWrite(CD_Plus,LOW);
  digitalWrite(CD_Minus,LOW);
 
 //Agitator (PD) setup
  pinMode(PD_Plus, OUTPUT);
  pinMode(PD_Minus, OUTPUT);
  digitalWrite(PD_Plus,LOW);
  digitalWrite(PD_Minus,LOW);
  
  // Pricker setup
  pinMode(Hole_Plus, OUTPUT);
  pinMode(Hole_Minus, OUTPUT);
  digitalWrite(Hole_Plus,LOW);
  digitalWrite(Hole_Minus,LOW);

  // Aloo system setup
  pinMode(Aloo_Plus,OUTPUT);
  pinMode(Aloo_Minus,OUTPUT);
  pinMode(Aloo_Valve,OUTPUT);
  digitalWrite(Aloo_Plus,LOW);
  digitalWrite(Aloo_Minus,LOW);
  digitalWrite(Aloo_Valve,LOW);

  //Pani valve setup
  pinMode(pani,OUTPUT);
  //digitalWrite(pani,LOW);
  digitalWrite(pani,HIGH);  //Relay module is active low.

  //LED Setup
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

  /*
  pinMode(coin,INPUT);
  digitalWrite(coin,LOW);
  pinMode(mode,INPUT);
  digitalWrite(mode,LOW);
  */

  //threshold = analogRead(Token)-10;
  Serial.begin(9600);

  Serial.println("Everything is setup!");

  lcd.clear();
  lcd.print("Good to go!");


  delay(2000);
  threshold = (analogRead(Token)*70)/100;
  Serial.print("Threshold: ");
  Serial.println(threshold);
  delay(1000);

  /*external interrupt pins
  int0 = 2
  int1 = 3
  int2 = 21
  int3 = 20
  int4 = 19
  int5 = 18
*/
  attachInterrupt(digitalPinToInterrupt(18), Minirotate_CD, RISING); //button to manually rotate CD. Attach to pin 21

  Timer1.initialize(agitate_time*1000000);
  Timer1.attachInterrupt(agitate);
  
}//setup() function ends

void Minirotate_CD()
{
  
  Serial.println("Mini Rotate CD");
  /*lcd.clear();
  lcd.print("Mini Rotate CD"); */

  digitalWrite(CD_Plus,HIGH);
  digitalWrite(CD_Minus,LOW);
  delayMicroseconds(15000);

  digitalWrite(CD_Plus,LOW);
  digitalWrite(CD_Minus,LOW);
  
}

void Rotate_CD() {
  delay(500);

  Serial.println("Rotate CD");
  lcd.clear();
  lcd.print("Rotate CD");

  digitalWrite(CD_Plus,HIGH);
  digitalWrite(CD_Minus,LOW);
  delay(1100);
    
  digitalWrite(CD_Plus,LOW);
  digitalWrite(CD_Minus,HIGH);
  delay(50);

  digitalWrite(CD_Plus,HIGH);
  digitalWrite(CD_Minus,LOW);
  delay(10);

  digitalWrite(CD_Plus,LOW);
  digitalWrite(CD_Minus,HIGH);
  delay(5);

  digitalWrite(CD_Plus,HIGH);
  digitalWrite(CD_Minus,LOW);
  delay(5);

  
  
  digitalWrite(CD_Plus,LOW);
  digitalWrite(CD_Minus,LOW);
}

void agitate()
{

  if(f_agitate == 0)
  {
    digitalWrite(PD_Plus,HIGH);        //Start Agitator
  digitalWrite(PD_Minus,LOW);
  Serial.println("Agitator started");
  f_agitate = 1;
  agitate_time  = 8;
  }
   

  else
  {
    digitalWrite(PD_Plus,LOW);       // Stop Agitator
  digitalWrite(PD_Minus,LOW);
  Serial.println("Agitator stopped");
  f_agitate = 0;
  agitate_time = 16;
  }
  
}

void Puri() {

  Serial.println("Agitator Begins");
  lcd.clear();
  lcd.print("PURI Incoming!");

  digitalWrite(PD_Plus,HIGH);        //Start Agitator
  digitalWrite(PD_Minus,LOW);

  Serial.println("Flap Sequence");
  Main.write(MO);        //MF open
  delay(2000);
  Main.write(MC);       //MF closed
  delay(1000);

  Second.write(SO);      //SF open
  delay(2000);
  Second.write(SC);     //SF closed

  digitalWrite(PD_Plus,LOW);       // Stop Agitator
  digitalWrite(PD_Minus,LOW);
  Serial.println("Agitator Stops");
}

void Hole() {

  Serial.println("H");

  lcd.clear();
  lcd.print("Punching the");
  lcd.setCursor(0,1);
  lcd.print("Hole!");

  delay(3000);

  for ( int i =0; i<3 ;i++)
    {

     digitalWrite(Hole_Minus, LOW);
     digitalWrite(Hole_Plus, HIGH);
     delay(280);

     digitalWrite(Hole_Minus, HIGH);
     digitalWrite(Hole_Plus, LOW);
     delay(290);


     digitalWrite(Hole_Minus, LOW);
     digitalWrite(Hole_Plus, LOW);

     delay(280);

    }

   lcd.clear();
   lcd.print("Hole done");
}

void Aloo() {

  lcd.clear();
  lcd.print("Stuffing ALOO");

  Serial.println("A_V");

  /*removing the aloo valve code cause it will be manual now
  digitalWrite(Aloo_Valve,HIGH);
  delay(100);
  digitalWrite(Aloo_Valve,LOW);
  */

  Serial.println("A_On");
  digitalWrite(Aloo_Plus,HIGH);
  digitalWrite(Aloo_Minus,LOW);
  delay(10000);
  digitalWrite(Aloo_Plus,LOW);
  digitalWrite(Aloo_Minus,LOW);
  Serial.println("A_Off");

  lcd.clear();
  lcd.print("Aloo done");

}

void Pani() {

  lcd.clear();
  lcd.print("Filling PAANI");

  Serial.println("P_On");
  //digitalWrite(pani, HIGH);
  digitalWrite(pani,LOW);
  delay(8000);
  //digitalWrite(pani, LOW );
  digitalWrite(pani,HIGH);
  Serial.println("P_Off");

  lcd.clear();
  lcd.print("Paani over");
}




void selection(int toggle) {

    switch(toggle){
    
      case 1 : Rotate_CD();
               break;
               
      case 2 : Hole();
               break;
    
      case 3 : Aloo();
               break;
               
      case 4 : Pani();
               break; 
    
      case 5 : puri();
               agitate();
               break;
    
      default: lcd.print("Default");
    }
    delay(1000);

}

int Button_Accept() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  /*  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Coin");
  lcd.setCursor(0,1);
  lcd.print("to begin!"); */

  if(digitalRead(Token));
}



void loop() {

 //s token_status=1;

  if (coin ==0)
   {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Test Mode");
      lcd.setCursor(0,1);
      lcd.print("Button1 to  begin!");

      coin=1;
    }

  if (token_status==0) {

     token_status = Button_Accept();
  }

  if(token_status==1)
  {

      if(mode==0)
        mode = Select_Mode();

      if(mode == 1)  //single pani puri eater mode
      {
        Dispense();
        digitalWrite(LED,LOW);
        coin =0;
      }

      else if(mode == 2)  //multi player mode
      {
        Multiplayer();
        digitalWrite(LED,LOW);
        coin =0;
      }

      token_status=0;
      mode=0;
   }
}
