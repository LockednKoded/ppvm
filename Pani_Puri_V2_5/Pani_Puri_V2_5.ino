/* PIN ASSIGNMENT  */

int PD = 22;

int CD = 23;

int Hole_Plus = 34;
int Hole_Minus = 35;

int Aloo_Plus = 28;
int Aloo_Minus = 29;
int Aloo_Valve = 26;

int pani = 30;

int Token = A15;  //Analog Read pin A0

int LED = 13; //Token accepted LED

int Button = 32;

/* Other Variables */

int p = 0 , a = 0, h = 0;  //function counters.
int button_count = 0;
int token_status = 0;
int threshold = 95;  // LDR threshold

void setup() {

  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  
  pinMode(PD, OUTPUT);
  digitalWrite(PD, LOW);

  pinMode(CD, OUTPUT);
  digitalWrite(CD, LOW);

  pinMode(Hole_Plus, OUTPUT);
  pinMode(Hole_Minus, OUTPUT);
  digitalWrite(Hole_Plus,LOW);
  digitalWrite(Hole_Minus,LOW);

  pinMode(Aloo_Plus,OUTPUT);
  pinMode(Aloo_Minus,OUTPUT);
  pinMode(Aloo_Valve,OUTPUT);
  digitalWrite(Aloo_Plus,LOW);
  digitalWrite(Aloo_Minus,LOW);
  digitalWrite(Aloo_Valve,LOW);

  pinMode(pani,OUTPUT);
  digitalWrite(pani,LOW);

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

  pinMode(Button, INPUT);
  digitalWrite(Button, HIGH);

  Serial.begin(9600);

}

void Rotate_CD() {
  delay(500);
  
  Serial.println("R_CD");
  digitalWrite(CD,HIGH);
  delay(545);
  digitalWrite(CD,LOW);
}

void Rotate_PD() {
  Serial.println("R_PD");
  digitalWrite(PD,HIGH);
  delay(1375);
  digitalWrite(PD,LOW);
}

void Hole() {

  Serial.println("H");

  delay(200);

  for ( int i =0; i<3 ;i++)
    {

     digitalWrite(Hole_Minus, LOW);
     digitalWrite(Hole_Plus, HIGH);
     delay(300);

     digitalWrite(Hole_Minus, HIGH);
     digitalWrite(Hole_Plus, LOW);
     delay(310);


     digitalWrite(Hole_Minus, LOW);
     digitalWrite(Hole_Plus, LOW);

     delay(300);

    }
}

void Aloo() {

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

  Serial.println("P_On");
  digitalWrite(pani, HIGH);
  delay(8000);
  digitalWrite(pani, LOW );
  Serial.println("P_Off");
}

int Button_Press()
  {
      int state=0;
      if(digitalRead(Button)==LOW)
      {
        delay(10);
        if(digitalRead(Button)==LOW)
        {
           state=1;
           button_count++;
           Serial.println("ButtonPress");
        }
      }
      return(state);
  }

int Token_Accept() {

  int ldrstatus=analogRead(Token);

  if(ldrstatus<=threshold) // <= threshold value
    {
      Serial.println("T_Yes");
      digitalWrite(LED,HIGH);
      return 1;
    }
  else
    {
      //Serial.println("T_No");
      digitalWrite(LED,LOW);
      return 0;
    }
}

void Startup() {

    Serial.println("Startup");

    Rotate_CD();
    Hole();
    Rotate_CD();
    Aloo();
    Hole();
    Rotate_CD();
    Aloo();
    Hole();
    Pani();
     Rotate_CD();
    Aloo();
    Hole();

    Serial.println("Startup End");

    p=2;
    a=4;
    h=5;
}

void loop() {
  
  if (token_status==0) {
    token_status = Token_Accept();
  }

  if(token_status==1)
  {
    if(Button_Press())
      {
        Serial.print("button_count=");
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
          }

        if(button_count == 6)
          {
            button_count=0;
            p = 0;
            a = 0;
            h = 0;
            token_status=0;
            digitalWrite(LED,LOW);
            Rotate_PD();
            Serial.println("Next Plate");
          }

      
      }
  }

}
