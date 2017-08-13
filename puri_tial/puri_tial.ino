#include <Servo.h>


 int PD = 0;
/*Servo initialization*/
    Servo Main;
    Servo Second;
    int Main_pin = 12;
    int Sec_pin = 11;
    int MO = 0;
    int MC = 90;
    int SO = 0;
    int SC = 100;

void setup() {
  // put your setup code here, to run once:

   //Agitator setup
   pinMode(PD, OUTPUT);
  digitalWrite(PD, LOW);

  // Servo setup
  Main.attach(Main_pin);
  Second.attach(Sec_pin);
  Main.write(MC);       //MF closed
  Second.write(SC);     //SF closed

  Serial.begin(9600);

  Serial.println("Everything is setup!");


}

void Puri() {

  Serial.println("Agitator Begins");
  //lcd.clear();
  //lcd.print("Puri");

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

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Puri() function called");
  Puri();
  Serial.println("exited Puri() function");
  delay(10000);
  Serial.println("TIME FOR NEXT PURI");

}
