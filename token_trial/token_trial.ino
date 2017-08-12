int Token = 0;  //Analog Read pin A15

int LED = 13; //Token accepted LED

int token_status = 0;
int threshold = 95;
int coin =0; //this is for showing the INSERT COIN TO BEGIN statement only once
int ldrstatus;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

  Serial.println("Everything is setup!");

  //lcd.clear();
  //lcd.print("Good to go!");
  Serial.println("Good to go!");
  delay(2000);
  
  threshold = analogRead(Token) -20;
  Serial.print("Threshold: ");
  Serial.println(threshold);
  delay(1000);

  

}

int Token_Accept() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //lcd.print("Insert Coin to eat");
  //Serial.println("Insert Coin to eat");

  ldrstatus=analogRead(Token);

  if(ldrstatus<=threshold) // <= threshold value
    {
      Serial.println("T_Yes: ldrstatus ");
      Serial.println(ldrstatus);
      digitalWrite(LED,HIGH);
      return 1;
    }
  else
    {
      Serial.println("T_No: ldrstatus "+ldrstatus);
      digitalWrite(LED,LOW);
      return 0;
    }
}


void loop() {

  if (coin ==0)
    {
      //lcd.clear();
      //lcd.setCursor(0, 0);
      //lcd.print("Insert Coin");
      //lcd.setCursor(0,1);
      //lcd.print("Insert Coin");

      Serial.println("Insert Coin To Begin: ");
      coin=1;
    }

  if (token_status==0) {

     token_status = Token_Accept();
     Serial.println("T_No: ldrstatus ");
     Serial.println(ldrstatus);
  }

  if(token_status==1)
  {
    Serial.println("TOKEN DETECTED");
    Serial.println("T_Yes: ldrstatus ");
    Serial.println(ldrstatus);

      /*if(mode==0)
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
      }*/
   }

}

