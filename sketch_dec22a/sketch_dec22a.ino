// Motor A
int enA = 10;
int in1 = 9;
int in2 = 8;

// Motor B
int enB = 11;
int in3 = 7;
int in4 = 6;

//DC Motor
int MaxSpeed = 250;
int LowSpeed = 100;

//Ultrasonic sensor Left
int trig=2;
int echo=3;

//Ultrasonic sensor Right
int trig_RIGHT=12;
int echo_RIGHT=13;

long timeInMicro;

long distanceInCm;

int distance_LEFT;
int distance_RIGHT;

////PIR Sensors
//the time i need to give the sensor to calibrate (10 to 60 secs according to datasheet)
int calibrationTime = 40;        

//PIR Sensor Right
int PIRPin_Left = 5;

//PIR Sensor Left
int PIRPin_Right = 4;

int PIRValue_LEFT;
int PIRValue_RIGHT;

boolean HumanLEFT=false;
boolean HumanRIGHT=false;

String speechData;

void setup()
{
  Serial.begin(9600);

  //Ultrasonic sensor Left
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);

  //Ultrasonic sensor Right
  pinMode(12,OUTPUT);
  pinMode(13,INPUT);

  // I am setting all motor pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //PIR Sensor pins setting them as inputs
  pinMode(PIRPin_Left, INPUT);
  pinMode(PIRPin_Right, INPUT);

  //PIR Sensor pins setting them to LOW at the beginning, according to the datasheet of the sensor
  digitalWrite(PIRPin_Left, LOW);
  digitalWrite(PIRPin_Right, LOW);
  
  
  Serial.print("Calibrating sensor ");
  //I am waiting to calibrate the sensors
  for(int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println(" Done!");
  Serial.println("SENSOR ACTIVE");
  delay(50);
  
}

void loop()
{
  //calls the function to calculate the distance with passing in the parameters of sensors
  distance_LEFT = CalculateDistance(trig, echo);
  distance_RIGHT = CalculateDistance(trig_RIGHT, echo_RIGHT);
  
  //reads the value from the digital pin of PIR sensors
  PIRValue_LEFT = digitalRead(PIRPin_Left);
  PIRValue_RIGHT = digitalRead(PIRPin_Right);

  //For printing the sensor values
  //Serial.println(distance_LEFT);
  //Serial.println(distance_RIGHT);

  //Serial.println(PIRValue_LEFT);
  //Serial.println(PIRValue_RIGHT);

  //check if the serial is received from speech recognition
  if(Serial.available() >0)
  {
    //reads the data from serial as a string and stores in the speechData string variable
    speechData = Serial.readString();

    //conditions of commands if "left" then turn left etc...
    if(speechData == "left")
    {
      Serial.println("I was told to go to the left!");
      turnLeft();
      delay(1000);
      Stop();
    }
    else if(speechData == "right")
    {
      Serial.println("I was told to go to the right!");
      turnRight();
      delay(1000);
      Stop();
    }
    else if(speechData == "drive")
    {
      Serial.println("I was told to go to the forward!");
      Forward();
      delay(1000);
      Stop();
    }
    else if(speechData == "back")
    {
      Serial.println("I was told to go back!");
      Reverse();
      delay(1000);
      Stop();
    }
    else if(speechData == "stop")
    {
      Serial.println("I was told to stop!");
      Stop();
    }
  }
  else
  {
    //if data is not received from serial then it will follow the user according to the sensor data it senses
    if(distance_LEFT < 10 && PIRValue_LEFT == 1)
    {
      Serial.println("My Human is on the Left side!");
      HumanLEFT=true;
      turnLeft();
      delay(1000);
      Stop();
    }
    else
    {
      HumanLEFT=false;
    }

    if(distance_RIGHT < 10 && PIRValue_RIGHT == 1)
    {
      Serial.println("My Human is on the Right side!");
      HumanRIGHT=true;
      turnRight();
      delay(1000);
      Stop();
    }
    else
    {
      HumanRIGHT=false;
    }

    /*if(HumanLEFT == true && HumanRIGHT == true)
    {
      Serial.println("My Human is on both sides, go back!");
      Reverse();
      delay(1000);
      Stop();
    }*/

  }

}

long CalculateDistance(int triq_, int echo_)
{
  digitalWrite(triq_, LOW);
  delayMicroseconds(2);
  digitalWrite(triq_, HIGH);
  delayMicroseconds(10);
  digitalWrite(triq_, LOW);

  timeInMicro= pulseIn(echo_, HIGH);

  distanceInCm = ((timeInMicro/29)/2);

  //Serial.println(distanceInCm);
  delay(100);

  return distanceInCm;
}

void Forward()
{
  //set speed of motor A to Max speed
  analogWrite(enA, MaxSpeed);

  //turn on Motor A in anticlockwise
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  //set speed of motor B to Max speed
  analogWrite(enB, MaxSpeed);

  //turn on Motor B in anticlockwise
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft()
{
  //set speed of motor A to Low speed
  analogWrite(enA, LowSpeed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnRight()
{
  //set speed of motor B to Low speed
  analogWrite(enB, LowSpeed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void Reverse()
{
  //set speed of motor A to Max speed
  analogWrite(enA, MaxSpeed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  //set speed of motor B to Max speed
  analogWrite(enB, MaxSpeed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Stop()
{
  //set everything to low to not run any motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}