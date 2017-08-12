#include <Servo.h>

  Servo Main;
  Servo Second;
  int Main_pin = 12;
  int Sec_pin =11; 
  int MO = 20;
  int MC = 90;
  int SO = 100;
  int SC = 10;
  
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
