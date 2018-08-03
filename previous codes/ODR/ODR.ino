int triggerPin = 10;
int echoPin = 11;

int RightDC = 6;
int LeftDC = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RightDC, OUTPUT);
  pinMode(LeftDC, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float duration;
  int distance;
  
  //digitalWrite(triggerPin, ); //triggering the wave(like blinking an LED)
 // delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  
  duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
  distance = (duration/2) / 29.1; //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number
  
  Serial.println(distance);
  if(distance<35 )
  {
    
    Serial.println("********* Obstacle ************ ");
    digitalWrite(RightDC,LOW);
    digitalWrite(LeftDC, LOW);
    delay(1000);
    if (distance<35)
    {
    digitalWrite(RightDC, HIGH);
    delay(2000);
    digitalWrite(RightDC,LOW);
    delay(1000); 
    }
  }

  else
  {
    
  digitalWrite(RightDC, HIGH);
  digitalWrite(LeftDC, HIGH);
  }
  
  
  

}
