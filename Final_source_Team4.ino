#include <Servo.h>
#define MAX 45    //Max Degree of Horizontal Motor
#define MIN 5     //Min Degree of Horizontal Motor
#define MAX2 20   //Max Degree of Vertical Motor
#define MIN2 10   //Min Degree of Vertical Motor
#define DIST 33   //Threshold of the ultrasonic sensor
const int LED = 13;

Servo servoHori; //Initialize Horizontal Motor
Servo servoVert; //Initialize Vertical Motor

const int servoHoriPin = 9;  //Set Horizontal Motor Pin Number
int currentAngle = 25;      //Set Current Angle of Horizontal Motor
int angle = 25;
const int leftTrigPin = 5;    //Set left UltraSonic sensor
const int leftEchoPin = A2;
const int rightTrigPin = 4;  //Set right UltraSonic sensor
const int rightEchoPin = A3;
double leftDuration, rightDuration;
double leftDistance, rightDistance;
long defaultDistance = 20;    //Set Initial Distance
boolean left = false;
boolean right = false;

const int servoVertPin = 11;  //Set Vertical Motor Pin Number
const int upTrigPin = 6;    //Set up UltraSonic sensor
const int upEchoPin = A1;
const int downTrigPin = 7;   //Set down UltraSonic sensor
const int downEchoPin = A0;
double upDuration, downDuration;
double upDistance, downDistance;
boolean up = false;
boolean down = false;
int currentAngle2 = 15;    //Set Current Angle of Vertical\ Motor
int  angle2 = 15;
void setup() {
  pinMode(LED, OUTPUT);    
  
  pinMode(leftTrigPin, OUTPUT);    //Setup Sensors and Motors
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  servoHori.attach(servoHoriPin);
  servoHori.write(currentAngle);
  
  pinMode(upTrigPin, OUTPUT);
  pinMode(upEchoPin, INPUT);
  pinMode(downTrigPin, OUTPUT);
  pinMode(downEchoPin, INPUT);
  
  servoVert.attach(servoVertPin);    
  servoVert.write(currentAngle2);
  
  
}

void loop() {
  
  //Calculate upDuration and upDistance from up Sensor
  digitalWrite(upTrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(upTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(upTrigPin, LOW);
  upDuration = pulseIn(upEchoPin, HIGH);
  upDistance = upDuration / (29 * 2);

  //Calculate downDuration and downDistance from down Sensor
  digitalWrite(downTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(downTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(downTrigPin, LOW);
  downDuration = pulseIn(downEchoPin, HIGH);
  downDistance = downDuration / (29 * 2);
  
  //Set boolean arguements
  if (upDistance < DIST) 
    up = true;
  else
    up = false;
  if (downDistance < DIST)
    down = true;
  else
    down = false;

  //Algorithm for movement of motor (Described in PowerPoint)
  if ((up == true) && (down == true))
  {
    digitalWrite(LED, HIGH);
    if (currentAngle2 < MAX2)
      {
        angle2++;
        currentAngle2 = angle2;
        servoVert.write(currentAngle2);
      }
    /*
      if (currentAngle2 > MIN2)
      {
        angle2--;
       
        currentAngle2 = angle2;
        servoVert.write(currentAngle2);
      }
      */
  }
  else
  {
    if (up == true)
    {
      digitalWrite(LED, LOW);
      servoVert.write(currentAngle2);
    }
    else
    {
      digitalWrite(LED, LOW);
      //servoVert.write(currentAngle2);
      //delay(30);

    }
    if (down == true)
    {
      digitalWrite(LED, HIGH);
      if (currentAngle2 > MIN2)
      {
        angle2--;
        
        currentAngle2 = angle2;
        servoVert.write(currentAngle2);
      }
    }
    else
    {
      digitalWrite(LED, LOW);
      servoVert.write(currentAngle2);
      //delay(30);
    }
  }
  
  
  //Calculate leftDuration and leftDistance from left Sensor
  digitalWrite(leftTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrigPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftDistance = leftDuration / (29 * 2);

  //Calculate rightDuration and rightDistance from right Sensor
  digitalWrite(rightTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrigPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightDistance = rightDuration / (29 * 2);
  
  //Set boolean arguements
  if (leftDistance < DIST)
    left = true;
  else
    left = false;
  if (rightDistance < DIST)
    right = true;
  else
    right = false;

  //Algorithm for movement of motor (Described in PowerPoint)
  if ((left == true) && (right == true))
  {
    digitalWrite(LED, LOW);
    //servoHori.write(currentAngle);
  }
  else
  {
    if (left == true)
    {
      digitalWrite(LED, HIGH);
      if (currentAngle < MAX)
      {
        angle++;
        
        currentAngle = angle;
        servoHori.write(currentAngle);
      }
    }
    else
    {
      digitalWrite(LED, LOW);
      //servoHori.write(currentAngle);
      //delay(10);

    }
    if (right == true)
    {
      digitalWrite(LED, HIGH);
      if (currentAngle > MIN)
      {
        angle--;
        
        currentAngle = angle;
        servoHori.write(currentAngle);
      }
    }
    else
    {
      digitalWrite(LED, LOW);
      //servoHori.write(currentAngle);
      //delay(10);
    }
  }
        delay(10);
  
  //delay(30);
  /*
  if(leftDistance < 30)
  {
    digitalWrite(LED,HIGH);
    if(currentAngle < 135)
    {
      angle++;
      
      currentAngle = angle;
      servoHori.write(currentAngle);
      delay(30);
    }
  }
  else
  {
    digitalWrite(LED,LOW);

  }
  delay(50);
  */
}
