//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

//modor pin 
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

#define cmd 13
int stat;
int Distance;

#define carSpeed 100
// ultrasonic sensor pin 
int Echo = A4;
int Trig = A5;


void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
     //accelerate
    for(int i = 0; i <= 255; i++){
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(20);
    }
}

  

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
     //accelerate
    for(int i = 0; i <= 255; i++){
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(20);
  
}}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
 
  
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
 
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 
//-------------------Ultrasonic distance measurement -------------------------------------
int getDistance() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    return (int)pulseIn(Echo, HIGH) / 58;
}


///-------------------------------setup---------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(cmd, INPUT);

   Serial.print("Starting...\n");
}


///-------------------------------loop---------------------------------------------------------


void loop() {
  
int obstacle =0;
String readString;
String command;


 while (Serial.available()) {
      delay(1);
    if (Serial.available() >0) {
      char c = Serial.read();         //gets one byte from serial buffer
    if (isControl(c)) {               // che king wether its a control command
      break;
    }
      readString += c;                  //makes the string readString    
    }
 }   

 command = readString;

  if (command == 'go'){  
     stat = 1;
  }
  

if (stat == 1){     //forward command
  Distance = getDistance();
  if (Distance <= 20){
  obstacle = 1 ;
  Serial.print("Obstucle found...");
  Serial.write('o');
  }
  }
if (obstacle == 0){                   // if there is no obstucles go forward by following line
         if(LT_M){
        forward();
        }
        else if(LT_R) {
        right();
        while(LT_R);
        }
        else if(LT_L) {
        left();
        while(LT_L);
        }
    }
  
if (command == 'gp'){            //gp -- once get pallet command recieved 
        Distance = getDistance();
        if (Distance >= 3){     // will go tiil 3 cm
        forward();
        if (Distance <= 3){ 
        digitalWrite(13,HIGH);
        delay(2000);
        digitalWrite(13,HIGH);  }
      
        }}


if (command == 'turn' ){    ///turn almost 180 degree and keep line
  right();
  for(int i = 0; i <= 255; i++){
    analogWrite(ENB, i);
    analogWrite(ENA, i);
  delay(3000);
}
}

if (command == 'stop' ){          // stop command
 
  Serial.println("stopping");
  digitalWrite(ENB, LOW); 
  digitalWrite(ENA, LOW);
  delay(2000);

}
}
