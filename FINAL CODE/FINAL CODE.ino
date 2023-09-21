// C++ code
#include <Servo.h>

int randomTime;
int p1_score=0;
int p2_score=0;
// I initialized player 1 LEDs
int orangeLED_1=4;
int orangeLED_2=5;
int orangeLED_3=6;
// Initializing player 2 LEDs 
int blueLED_1=9;
int blueLED_2=10;
int blueLED_3=11;
int successLED_1=7;
int successLED_2=12;
int failureLED_1=8;
int failureLED_2=13;
int pushButton_1=2;
int pushButton_2=3;
// this Boolean variable is inizialed when the player does not press the pushButton 
int Boolp1=0;
int Boolp2=0;
// I initialized the servo to pin 14, which was plugged into A0 in the Arduino
int servopin=14; 
Servo myservo;

void setup()
{
    // I set all the LEDs to be outputs, as they will simply be on or off
  	pinMode(orangeLED_1,OUTPUT);
  	pinMode(orangeLED_2,OUTPUT);
  	pinMode(orangeLED_3,OUTPUT);
  	pinMode(blueLED_1,OUTPUT);
  	pinMode(blueLED_2,OUTPUT);
  	pinMode(blueLED_3,OUTPUT);
  	pinMode(successLED_1,OUTPUT);
    pinMode(successLED_2,OUTPUT);
    // The push buttons are inputs and sends signals to the Arduino
  	pinMode(pushButton_1,INPUT);
  	pinMode(pushButton_2,INPUT);
  	attachInterrupt(digitalPinToInterrupt(2), led_off_p1,FALLING); 
  	attachInterrupt(digitalPinToInterrupt(3),led_off_p2,FALLING); 
  	myservo.attach(servopin);
}

// The functions assigns the LEDs to different positions
void randomizer_p1()
{
  if(random(3)== 0)
  {whacky_1(orangeLED_1,pushButton_1);}
  else if (random(3)== 1){
    whacky_1(orangeLED_2,pushButton_1);}
  else
    whacky_1(orangeLED_3,pushButton_1);  
}

void randomizer_p2()
{   if(random(3)== 0){
    whacky_2(blueLED_1,pushButton_2);}
  else if (random(3)== 1){
    whacky_2(blueLED_2,pushButton_2);}
  else
    whacky_2(blueLED_3,pushButton_2);
}

void loop()
{
  while (p2_score < 10 && p1_score < 10)// I called the randomizer function which will be executed until the score is less than 10
  { 
    // Each chosen LED will have a random delay time until the next one is lit up again.
  	randomTime=random(500,3000); 
  	randomizer_p1();
  	randomizer_p2();
    scorecheck();  // This checks the score for player 1 and player 2 after each chosen LED
  	delay(randomTime);
  } 
    for(int z = 0; z < 5; z++) // if score is greater than 10, then we want to show that the game ended by blinking all the lights
    {
    digitalWrite(orangeLED_1,HIGH);
    digitalWrite(orangeLED_2,HIGH);
    digitalWrite(orangeLED_3,HIGH);
    digitalWrite(successLED_1,HIGH); 
    digitalWrite(failureLED_1,HIGH); 
    digitalWrite(blueLED_1,HIGH);
    digitalWrite(blueLED_2,HIGH);
    digitalWrite(blueLED_3,HIGH);          
    digitalWrite(successLED_2,HIGH); 
    digitalWrite(failureLED_2,HIGH); 
  
    delay(100); // This delay function determins how long all the LEDs will be on for
  
    digitalWrite(orangeLED_1,LOW);
    digitalWrite(orangeLED_2,LOW);
    digitalWrite(orangeLED_3,LOW);
    digitalWrite(successLED_1,LOW); 
    digitalWrite(failureLED_1,LOW); 
    digitalWrite(blueLED_1,LOW);
    digitalWrite(blueLED_2,LOW);
    digitalWrite(blueLED_3,LOW);
    digitalWrite(successLED_2,LOW);
    digitalWrite(failureLED_2,LOW);
    delay(100); // The turned off LEDs, will be off for a certain amount of time   
    }
}

void whacky_1(int p1_LED,int pushButton_1)  
{
  digitalWrite(p1_LED,HIGH); // the chosen LEDs will start of being on
  int molewait_1 = random(200,700); // The LEDs will be on a for a ramdon amount of time
  long startTime_1 = millis();
  
  while(millis() - startTime_1 < molewait_1)  //  This function checks if we were in the duration of the LEDs being on
  { Boolp1=1;
    if (digitalRead(pushButton_1) == LOW)
    {
      digitalWrite(p1_LED,LOW); // we turn of LED as the push button was pressed
      digitalWrite(successLED_1,HIGH); // we turn on the p1 success LED as we captured the LED on time
      delay(200);
      digitalWrite(successLED_1,LOW); 
      p1_score = p1_score + 1; // increase player 1 score, as we pressed button successfully
      return; 
    } 
  }
  // this suggests that that the player ran out of time in pressing the push button
  // Not being in the duration of capturing the LED, resulted to failure LED turning on
  Boolp1=0; 
  digitalWrite(p1_LED,LOW); 
  digitalWrite(failureLED_1,HIGH); 
  delay(350);
  digitalWrite(failureLED_1,LOW);}
    
// Function for player 2
void whacky_2(int p2_LED,int pushButton_2)
{
  digitalWrite(p2_LED,HIGH);
  int molewait_2 = random(200,700);
  long startTime_2 = millis();
  
  while(millis()- startTime_2 < molewait_2)
  {Boolp2=1;    
    if (digitalRead(pushButton_2) == LOW){
      digitalWrite(p2_LED,LOW); 
      digitalWrite(successLED_2,HIGH); 
      delay(200);
      digitalWrite(successLED_2,LOW); 
      p2_score = p2_score + 1; 
      return; 
    } 
 }
  Boolp2=0; 
  digitalWrite(p2_LED,LOW); 
  digitalWrite(failureLED_2,HIGH); 
  delay(350);
  digitalWrite(failureLED_2,LOW);}

// ISR function
void led_off_p1()
{if (digitalRead(pushButton_1) == LOW && Boolp1 == 0)
  {digitalWrite(failureLED_1,HIGH);
    delay(200);
    digitalWrite(failureLED_1,LOW);   
  } 
}

void led_off_p2()
{if(digitalRead(pushButton_2) == LOW && Boolp2 == 0);{
  digitalWrite(failureLED_2,HIGH);
  delay(200);
  digitalWrite(failureLED_2,LOW);
  }
}
// Servo points to the player that has a higher score
void scorecheck(){
  if(p1_score > p2_score){
    myservo.write(180);}
  else if( p2_score > p1_score){
    myservo.write(0);
  }
  else{
    myservo.write(90);
  }
    
}

