/*
  Mr Wong
  The purpose of this program is to assist in the simulation of a robot that utilizes a LDR sensor to traverse and return through a maze.
*/
/* This variable stores the analog port to get the LDR reading from. */
int LDRclose = A1;
int LDRfar = A0;

boolean hitBlack = false;


/* The follow are the pins. m1 is motor one, m2 is motor 2. Pin1 and Pin2 represent forward / backwards respectively. */
int motorL = 10;   // pin 2 on L293D
int motorR = 7;   // pin 15 on L293D
int motorRback = 6; 

/* This method sets up all of the inputs and outputs f  or the Arduino. */
void setup(){
  Serial.begin (9600); //turns on the Serial
  pinMode(LDRclose, INPUT);
  pinMode(LDRfar, INPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
}

/* The purpose of this method is to output the reading for the LDR.*/
void outputReading(){
  int readingFar = analogRead(LDRfar);
  Serial.print("LDR far Reading: ");
  Serial.print(readingFar); 
  int readingClose = analogRead(LDRclose);
  Serial.print("    LDR close Reading: ");
  Serial.println(readingClose ); 
}


/* This method identifies if there is black detected. */
boolean isBlack(){
  int lightFar = analogRead(LDRfar);
  int lightClose = analogRead(LDRclose);
  return lightFar < 750 || lightClose < 800;
  
}

void goRight(){
   analogWrite(motorL, 1000); 
   analogWrite(motorR, 0); 
   analogWrite(motorRback, 0);
}
void goLeft(){
   analogWrite(motorL, 0); 
   analogWrite(motorR, 1000);
   analogWrite(motorRback, 0); 
}
void goRightFast(){
   analogWrite(motorL, 1000); 
   analogWrite(motorR, 0);
   analogWrite(motorRback, 700); 
}


/* This method executes continually in a loop. 
   Target logic: Turn left while on black, and turn right while on white.*/
void loop(){
  while(isBlack()){
    goLeft();
    //outputReading(); 
    delay(10);  
  }
  int timeOnWhite = 0;
  while (!isBlack()){
    if (timeOnWhite < 500 || timeOnWhite > 3000)
      goRight ();
    else
      goRightFast();
    //outputReading();
    Serial.print("Time on white:  ");
    Serial.println(timeOnWhite); 
    delay(10);
    timeOnWhite+= 10;
  }
}
