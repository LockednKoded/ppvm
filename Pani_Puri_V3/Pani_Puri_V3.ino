#include <LiquidCrystal.h>
#include <Servo.h>

/* PIN ASSIGNMENT  */

  int PD = 22;

  int CD = 23;

  int Hole_Plus = 34;
  int Hole_Minus = 35;

  // do we need this?
  int Aloo_Plus = 28;
  int Aloo_Minus = 29;

  int Aloo_Valve = 26;

  int pani = 27;

  int Token = 0;  //Analog Read pin A0

  int LED = 13; //Token accepted LED


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
  */

  // initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(8,9,4,5,6,7);

  /*Servo initialization*/
    Servo Main;
    Servo Second;
    int Main_pin = 12;
    int Sec_pin = 11;
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

  int button1 = 36;//button to press for player 1
  int button1_2 = 37;
  int button2 = 32;//button to press for player 2
  int button2_2 = 33;
  int score1 = 0;
  int score2 = 0;

  int coin =0; //this is for showing the INSERT COIN TO BEGIN statement only once.


void setup() {
  //LCD Setup
  // set up the LCD's number of columns and rows


  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);

  //for lcd pot contrast pin Vo
  pinMode(10, OUTPUT);
  analogWrite(10, 110);

  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);

  // doesn't work need to connect to vcc connected servo instead
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);

  pinMode(51, OUTPUT);
  digitalWrite(51, LOW);

  pinMode(50,OUTPUT);   //this is for l293d enable high
  digitalWrite(50,HIGH);

  lcd.begin(16, 2);

  //yeh button kelia tha
  /*
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW); */

  // button setup
  pinMode(button1_2,OUTPUT);
  digitalWrite(button1_2,LOW);
  pinMode(button2_2,OUTPUT);
  digitalWrite(button2_2,LOW);

  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  pinMode(button2, INPUT);
  digitalWrite(button2, HIGH);

  //Agitator setup
  pinMode(PD, OUTPUT);
  digitalWrite(PD, LOW);

  //CD Setup
  pinMode(CD, OUTPUT);
  digitalWrite(CD, LOW);

  // Servo setup
  Main.attach(Main_pin);
  Second.attach(Sec_pin);
  Main.write(MC);       //MF closed
  Second.write(SC);     //SF closed

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
  digitalWrite(pani,LOW);

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
}

void Rotate_CD() {
  delay(500);

  Serial.println("Rotate CD");
  lcd.clear();
  lcd.print("Rotate CD");

  digitalWrite(CD,HIGH);
  delay(545);

  digitalWrite(CD,LOW);
}

void Puri() {

  Serial.println("Agitator Begins");
  lcd.clear();
  lcd.print("Puri");

  digitalWrite(PD,HIGH);        //Start Agitator

  Serial.println("Flap Sequence");
  Main.write(MO);        //MF open
  delay(2000);
  Main.write(MC);       //MF closed
  delay(1000);

  Second.write(SO);      //SF open
  delay(2000);
  Second.write(SC);     //SF closed

  digitalWrite(PD,LOW);       // Stop Agitator
  Serial.println("Agitator Stops");
}

void Hole() {

  Serial.println("H");

  lcd.clear();
  lcd.print("PRICK");

  delay(200);

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
}

void Aloo() {

  lcd.clear();
  lcd.print("ALOO");

  Serial.println("A_V");

  digitalWrite(Aloo_Valve,HIGH);
  delay(100);
  digitalWrite(Aloo_Valve,LOW);

  Serial.println("A_On");
  digitalWrite(Aloo_Plus,HIGH);
  digitalWrite(Aloo_Minus,LOW);
  delay(10000);
  digitalWrite(Aloo_Plus,LOW);
  digitalWrite(Aloo_Minus,LOW);
  Serial.println("A_Off");

}

void Pani() {

  lcd.clear();
  lcd.print("PAANI");

  Serial.println("P_On");
  digitalWrite(pani, HIGH);
  delay(8000);
  digitalWrite(pani, LOW );
  Serial.println("P_Off");

  lcd.clear();
  lcd.print("Ready!");
}

 // for debouncing function
int Button_Press(int pin)
  {
      int state=0;
      if(digitalRead(pin)==LOW)
      {
        delay(10);
        if(digitalRead(pin)==LOW)
        {
           state=1;
           //button_count++;
           Serial.println("ButtonPress");
        }
      }
      return(state);
  }

int Token_Accept() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  /*  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert Coin");
  lcd.setCursor(0,1);
  lcd.print("to begin!"); */

  int ldrstatus=analogRead(Token);

  if(ldrstatus<=threshold) // <= threshold value
    {
      Serial.print("T_Yes: ldrstatus ");
      Serial.println(ldrstatus);
      digitalWrite(LED,HIGH);
      return 1;
    }
  else
    {
      //Serial.println("T_No: ldrstatus "+ldrstatus);
      digitalWrite(LED,LOW);
      return 0;
    }
}

int Select_Mode() {
  int s1 = 0;
  int s2 = 0;

  lcd.clear();
  lcd.print("B1 = Single");
  lcd.setCursor(0,1);
  lcd.print("B2 = Multi");

    //for(int i = 0; i<36; i++)
    while(!(s1 || s2))
    {
      /*lcd.scrollDisplayLeft();
      delay(400); */
      s1 = Button_Press(button1);
      s2 = Button_Press(button2);

      /*if(s1 || s2)
          break; */
    }

    if(s1)
      return 1;

     if(s2)
      return 2;
}

void Startup() {

    Serial.println("Startup");

    Rotate_CD();
    Puri();
    Rotate_CD();
    Puri();
    Hole();
    Rotate_CD();
    Puri();
    Aloo();
    Hole();
    Rotate_CD();
    Puri();
    Aloo();
    Hole();
    Pani();
    Rotate_CD();
    Puri();
    Aloo();
    Hole();

    Serial.println("Startup End");

    p=2;
    a=4;
    h=5;
    pu=6;
}

void Single_Puri()
{
  Rotate_CD();
  Puri();
  Rotate_CD();
  Hole();
  Rotate_CD();
  Aloo();
  Rotate_CD();
  Pani();
  Rotate_CD();
}

void Dispense() {

      do{
          if(Button_Press(button1))
            {
              button_count++;
              Serial.print("button_count= ");
              Serial.println(button_count);

              if(button_count == 1)
               {
                 Startup();
               }

              if(button_count<=6 && button_count >1)
                {
                  if(p<=6)
                    {
                      Pani();
                      p++;
                    }

                  Rotate_CD();

                  if(a<=6)
                    {
                      Aloo();
                      a++;
                    }

                  if(h<=6)
                    {
                      Hole();
                      h++;
                    }

                  if(pu<=6)
                    {
                      Puri();
                      pu++;
                    }
               }

              lcd.clear();
              lcd.print("Press B1 for");
              lcd.setCursor(0,1);
              lcd.print("next puri");
          }
        }while(button_count<6);

        if(button_count == 6)
          {
            button_count=0;
            p = 0;
            a = 0;
            h = 0;
            pu = 0;
            token_status=0;
            //digitalWrite(LED,LOW);
            lcd.clear();
            lcd.print("That's all folks!");
            Serial.println("Next Plate");
          }

      }

void Disp_Score() {
  lcd.clear();
  lcd.setCursor(0, 0);  // top left
  lcd.print("HOME");
  lcd.setCursor(10, 0);  //top right
  lcd.print("AWAY");
  lcd.setCursor(0, 1);  //bottom left
  lcd.print(score1);
  lcd.setCursor(10, 1);  //bottom right
  lcd.print(score2);
}

void Multiplayer() {
  score1 = score2 = 0;
  int checkcoin = 0;
  Disp_Score();

  do{

      do{

            if(Button_Press(button1))
            {
              score1++;
              Single_Puri();
              Disp_Score();
            }

            else if(Button_Press(button2))
              {
                score2++;
                Single_Puri();
                Disp_Score();
              }

        }while((score1+score2)%4);

      delay(1500);
      lcd.clear();
      lcd.setCursor(0, 0);
      checkcoin = 0;
      lcd.print("Insert coin to");
      lcd.setCursor(0, 1);
      lcd.print("continue: ");

      int i=1000;
      for(int sec = 5;sec>=0;sec-- )
      {
        lcd.setCursor(11,1);
        //lcd.print(sec+" ");
        lcd.print(sec);
        i=1000;
        while((i>0) && !(checkcoin = Token_Accept()) )
          {
            i--;
            delay(1);    //should we try a smaller delay?
          }
        if(checkcoin==1)
          break;
      }

    }while(checkcoin);
    lcd.clear();
    lcd.print("GAME OVER");
    delay(2000);
    Disp_Score();
    delay(2000);
    lcd.clear();

}

void loop() {

 //s token_status=1;

  if (coin ==0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Insert Coin");
      lcd.setCursor(0,1);
      lcd.print("to begin!");

      coin=1;
    }

  if (token_status==0) {

     token_status = Token_Accept();
  }

  if(token_status==1)
  {

      if(mode==0)
        mode = Select_Mode();

      if(mode == 1)  //single pani puri eater mode
      {
        Dispense();
        coin =0;
      }

      else if(mode == 2)  //multi player mode
      {
        Multiplayer();
        coin =0;
      }

      token_status=0;
      mode=0;
   }
}
