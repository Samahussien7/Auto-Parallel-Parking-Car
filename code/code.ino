//Ulra Sonic Pins (3 ultra sonic sensors)
//Back sensor
#define trigPin1 13
#define echoPin1 12
//Right sensor
#define trigPin2 11 
#define echoPin2 10 
//Front sensor
#define trigPin3 2 
#define echoPin3 6 
// Motors Speed 
#define S 75


// Motor A

#define enA 9
#define in1  8
#define in2  7

// Motor B

#define enB 3
#define in3  5
#define in4 4
//parking space
int space=0;
//Move Functions Prototype
void Stop();
void MoveForward();
void MoveLeft();
void MoveBack();
void MoveRight();
//ultra Sonic Function prototype
int UFun(int triger,int echo);
//functions prototypes
void Park();
int Check();

void setup() {
//ultra sonic pins
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(trigPin3,OUTPUT);
  pinMode(echoPin3,INPUT);
  
// Set all the motor control pins to outputs

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {

 delay(3000);
 MoveForward();
 delay(300);

 if (Check()==1&& space>27)
 {//space is measured by trial and error to check the right value ,it's varied by the speed
  space=0;
  Stop();
  delay(1000);
  Park();
  exit(0);
 }
 else {
   if(UFun(trigPin1,echoPin1)>4&&UFun(trigPin3,echoPin3)>4){
     MoveForward();
    }
   else{
     Stop();
    }
 }
}
void Park(){//Parking algorithm
  MoveBack();
  delay(300);
  Stop();
  delay(1000);
  MoveLeft();
  delay(450);
  Stop();
  delay(1000);
  while(UFun(trigPin1,echoPin1)>10){
  MoveBack();
  }
  Stop();
  delay(1000);
  MoveRight();
  delay(350);
  Stop();
  delay(400);
  MoveForward();
  delay(500);
  Stop();
  delay(1000);
 //the delay after each instruction varies depending on our car speed

}
int Check(){//Chicking the sutable parking space for the car width
  int Flag =0;
  while(UFun(trigPin2,echoPin2)>10){
    MoveForward();
    space++;
    Flag =1;
  }
  return Flag;
}
 int UFun(int triger , int echo){//ultrasonic reading 
   long duration ;
   int distance;
        digitalWrite(triger,LOW);
        delayMicroseconds(2);
        digitalWrite(triger, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger,LOW);
    
        duration = pulseIn(echo,HIGH);
        distance = duration * 0.0343 / 2 ; // 331.5 m/s ===> 0 C.....331.5 +0.6*temp....343.5*100/1000000=.03435cm/us
  return distance; 
  
  }
void MoveBack(){
  // Turn on motor A
      
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      
        // Set speed to 200 out of possible range 0~255
      
        analogWrite(enA, S-3);
      
        // Turn on motor B
      
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      
        // Set speed to 200 out of possible range 0~255
      
       analogWrite(enB, S);
  
  
  }
void MoveRight(){

  // Turn on motor A

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, S-3);

  // Turn on motor B

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enB, S);

  

  }
void MoveLeft(){
      
    // Turn on motor A

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, S-3);

  // Turn on motor B

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enB, S);


     }
void Stop(){
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  }
void MoveForward() {
    // Turn on motor A

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enA, S-3);

  // Turn on motor B

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Set speed to 200 out of possible range 0~255

  analogWrite(enB, S);


}