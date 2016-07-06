//subboard
#define  s_dpos  94
#define  l_dpos  90
#include <Servo.h>

//pin info
int control_servo = 5;
int lance_servo = 6;
int leftm = 9;
int leftm1 = 10;
int rightm = 3;
int rightm1 = 11;
int f_left = 7;
int f_right = 8;

//variable
int lance_pos = 0;
int control_pos = 0;
boolean frontm = true;
Servo Lance_servo; 
Servo Control_servo;

void setup() {
  //init pinmode
  pinMode(control_servo,OUTPUT);
  pinMode(lance_servo,OUTPUT);
  pinMode(leftm,OUTPUT);
  pinMode(rightm,OUTPUT);
  pinMode(leftm1,OUTPUT);
  pinMode(rightm1,OUTPUT);
  pinMode(f_left,OUTPUT);
  pinMode(f_right,OUTPUT);
  
  Lance_servo.attach(lance_servo);
  Control_servo.attach(control_servo);

  digitalWrite(leftm, HIGH);
  digitalWrite(leftm1, HIGH);
  
   digitalWrite(f_left, HIGH);
  digitalWrite(f_right, HIGH);
  
  
  
 control_sarvo(s_dpos + 0); 
 
  //serial open
  Serial.begin(9600);
  
 
}

void loop() {
   
   
//    // Receive buffer cheak 
  if ( Serial.available() >= sizeof(char)) {
    // check header
       char chk =  Serial.read();
       if (chk == 'A'){
         chk_pos(0);
       }else if(chk == 'B' ){
        chk_pos(3);
       }else if (chk == 'C'){
        chk_pos(-3);
       }else if  (chk == 'D'){
        chk_pos(-5);
       }else if  (chk == 'E'){
        chk_pos(5);
       }else if  (chk == 'F'){
        //chk_pos(-30);
       }else if  (chk == 'G'){
        //chk_pos(15);
       }           
  }
}
void chk_pos(int test){
  control_sarvo(s_dpos + test); 
}


void chk_lance(){
  lance_sarvo(l_dpos + lance_pos); 
}


void control_sarvo(int pos){

    Control_servo.write(pos);
   
} 

void lance_sarvo(int pos){
    Lance_servo.write(pos);
} 

//    chk_pos();
//    }else if ( Serial.read() == 'L' ) {
//       int low = Serial.read();
//       int high = Serial.read();
//       lance_pos = makeWord(high,low);
//       chk_lance(); 
//    } 

