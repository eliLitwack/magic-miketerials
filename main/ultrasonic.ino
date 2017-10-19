// defines functions which read from the ultrasonic
const int usTrigger = 4; //ultrasonic trigger pin
const int usEcho = 2; //ultrasonic echo pin
float distanceFromObstacle;
bool echoOngoing = false;
unsigned long echoStart;

void setupUs(){
  pinMode(usTrigger, OUTPUT);
  pinMode(usEcho, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(usEcho), handleEcho, CHANGE);
  
  //write low so that the ultrasonic is ready to recieve a trigger
  digitalWrite(usTrigger, LOW); 
}

void updateDistance(){
  digitalWrite(usTrigger, HIGH);
  delayMicroseconds(10); // Is this long enough?
  digitalWrite(usTrigger, LOW);
}

void handleEcho(){
  if(!echoOngoing){
    echoStart = micros();
  } else{
    unsigned long echoLength = micros() - echoStart;
    digitalWrite(usTrigger, LOW);
    distanceFromObstacle = echoLength/58.0;
  }
  echoOngoing = !echoOngoing;
}

