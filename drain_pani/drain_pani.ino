/*program to drain the pani container*/

int pani = 47;    // RIP Pin 17

void setup() {
  // put your setup code here, to run once:
  //Pani valve setup
  pinMode(pani,OUTPUT);
  //digitalWrite(pani,LOW);
  digitalWrite(pani,HIGH);  //Relay module is active low.

}

void Pani() {

  Serial.println("Draining pani jar");
  digitalWrite(pani,LOW); 
  delay(100000);
  digitalWrite(pani,HIGH);
  Serial.println("Draining stopped");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Pani();

}


