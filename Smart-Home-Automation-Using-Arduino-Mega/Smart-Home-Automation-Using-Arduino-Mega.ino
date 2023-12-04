int ldrPin = A0;
int tempPin = A1;
int trigPin = 28;
int echoPin = 29;
int buzzerPin = 31;
int ledPin1 = 3;
int ledPin2 = 4;
int ledPin3 = 5;
int ledPin4 = 6;
int relayPin = 7;
int nodePin1 = 8;
int nodePin2 = 9;
int nodePin3 = 10;
int nodePin4 = 11;
int nodePin5 = 12;
int nodePin6 = 13;

int ldrVal = 0;
int tempVal = 0;
int ultrasonicVal = 0;
long duration;
int distance;
int cm;
int inches;

int nodeVal1 = 0;
int nodeVal2 = 0;
int nodeVal3 = 0;
int nodeVal4 = 0;
int nodeVal5 = 0;
int nodeVal6 = 0;

int ultrasonicState = LOW;
int nodeState1 = LOW;
int nodeState2 = LOW;
int nodeState3 = LOW;
int nodeState4 = LOW;
int nodeState5 = LOW;
int nodeState6 = LOW;

void setup(){
  pinMode(ldrPin,INPUT);
  pinMode(tempPin,INPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(relayPin,OUTPUT);
  pinMode(nodePin1,INPUT);
  pinMode(nodePin2,INPUT);
  pinMode(nodePin3,INPUT);
  pinMode(nodePin4,INPUT);
  pinMode(nodePin5,INPUT);
  pinMode(nodePin6,INPUT);
  
  analogReference(INTERNAL1V1);
  Serial.begin(9600);
}


void loop(){
  
  
  nodeVal1 = digitalRead(nodePin1);
  nodeVal2 = digitalRead(nodePin2);
  nodeVal3 = digitalRead(nodePin3);
  nodeVal4 = digitalRead(nodePin4);
  nodeVal5 = digitalRead(nodePin5);
  nodeVal6 = digitalRead(nodePin6);

  //NODEPIN1
  if(nodeVal1 == HIGH){
    
  ldrVal = analogRead(ldrPin);
  tempVal = analogRead(tempPin);

   digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  cm = (duration/2) / 29.1;     
  inches = (duration/2) / 74;
  ultrasonicVal = cm; 
  
  Serial.print("LIGHT: ");
  Serial.println(ldrVal); 
  
  float cel = tempVal/9.31;
  float far = (cel*9)/5+32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C ");
  Serial.println();
  Serial.print("MOTION: ");
  Serial.println(ultrasonicVal);


  
  
  //LDR
  
  if(ldrVal < 700){
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,HIGH);
    digitalWrite(ledPin3,HIGH);
    digitalWrite(ledPin4,HIGH);
  }
  else if(ldrVal >= 700){
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW);
    digitalWrite(ledPin4,LOW);
  }

  //LM35
  if(cel >= 30.0){
      digitalWrite(relayPin,HIGH);
      Serial.println("FAN: ON");
      Serial.println();
    }
  else if(cel < 30.0){
      digitalWrite(relayPin,LOW);
      Serial.println("FAN: OFF");
      Serial.println();
    }

  if(cm >=1 && cm <= 50){
    tone(buzzerPin,1000,400);
    delay(400);
    tone(buzzerPin,2500,200);
    delay(200);
    tone(buzzerPin,1000,200);
    delay(200);
    tone(buzzerPin,2500,200);
    delay(200);
    tone(buzzerPin,1000,200);
    delay(200);
    if(ultrasonicState == HIGH){
      Serial.println("Motion Detected!");
      Serial.println(distance);
      ultrasonicState = LOW;
    }
  }
  
  else if(cm > 50){
    digitalWrite(buzzerPin,LOW);
    if(ultrasonicState == LOW){
      Serial.println("Motion Ended!");
      Serial.println(distance);
      ultrasonicState = HIGH;
    }
  }

   delay(1000);
  nodeState1 = HIGH;
}

else if(nodeVal1 == LOW && nodeState1 == HIGH){
  digitalWrite(buzzerPin,LOW);
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);
  digitalWrite(relayPin,LOW);
  nodeState1 = LOW;
}


  //NODEPIN2
  if(nodeVal2 == HIGH){
    digitalWrite(ledPin1,HIGH);
    delay(100);
    nodeState2 = HIGH;
  }
    else if(nodeVal2 == LOW && nodeState2 == HIGH){
    digitalWrite(ledPin1,LOW);
    delay(100);
    nodeState2 = LOW;
  }


  //NODEPIN3
  if(nodeVal3 == HIGH){
    digitalWrite(ledPin2,HIGH);
    delay(100);
    nodeState3 = HIGH;
  }
  else if(nodeVal3 == LOW && nodeState3 == HIGH){
    digitalWrite(ledPin2,LOW);
    delay(100);
    nodeState3 = LOW;
  }


  //NODEPIN4
  if(nodeVal4 == HIGH){
    digitalWrite(ledPin3,HIGH);
    delay(100);
    nodeState4 = HIGH;
  }
   else if(nodeVal4 == LOW && nodeState4 == HIGH){
    digitalWrite(ledPin3,LOW);
    delay(100);
    nodeState4 = LOW;
  }


  //NODEPIN5
  if(nodeVal5 == HIGH){
    digitalWrite(ledPin4,HIGH);
    delay(100);
    nodeState5 = HIGH;
  }
    else if(nodeVal5 == LOW && nodeState5 == HIGH){
    digitalWrite(ledPin4,LOW);
    delay(100);
    nodeState5 = LOW;
  }


  //NODEPIN6
  if(nodeVal6 == HIGH){
    digitalWrite(relayPin,HIGH);
    delay(100);
    nodeState6 = HIGH;
  }
    else if(nodeVal6 == LOW && nodeState6 == HIGH){
    digitalWrite(relayPin,LOW);
    delay(100);
    nodeState6 = LOW;
  }
}
