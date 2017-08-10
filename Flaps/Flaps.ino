#include <Servo.h>

  Servo Main;
  Servo Second;
  int Main_pin = 2;
  int Sec_pin = 3; 
  int MO = 0;
  int MC = 90;
  int SO = 0;
  int SC = 100;
  
void setup() {
  // put your setup code here, to run once:
  Main.attach(Main_pin);
  Second.attach(Sec_pin);

  Main.write(MC);       //MF closed
  Second.write(SC);     //SF closed
  delay(500);


  Main.write(MO);        //MF open
  delay(2000);
  Main.write(MC);       //MF closed
  delay(1000);

  Second.write(SO);      //SF open
  delay(2000);
  Second.write(SC);     //SF closed
}

void loop() {
  // put your main code here, to run repeatedly:

}
