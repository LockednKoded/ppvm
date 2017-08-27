#include <TimerThree.h>

#include <TimerOne.h>



int flag = 0;
int check  = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void isr()
{
  flag++;
  Serial.println(flag);
}

void function()
{
  Timer3.initialize(10000);
  Timer3.attachInterrupt(isr);
  
}

void function2()
{
  Serial.println("Entered function 2");
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(check == 0)
    {
      function();
      check = 1;
    }
  

    delay(1000);

    
    

    //if(flag > 10 && flag<20)
    //{
      Timer3.detachInterrupt();
      //function2();
    //}

    if(check == 1)
    {
      Serial.println("*********************************************");
      check = 2;
      function2();
    }
      
  

}
