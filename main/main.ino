//mainboard
#define reading_sensor true
#define  s_dpos  96
#define  l_dpos  0
#include <Servo.h>

//pin info 
int left2 = 19;
int left1 = 2;
int center = 4;
int right1 = 7;
int right2 = 8;
int left3 = 12;
int right3 = 13;
int control_servo = 5;
int lance_servo = 6;

int dpos = 0;
int Threshold = 0;

Servo Control_servo;
Servo Lance_servo; 

int lfm = 9;
int rfm = 10;
int lbm = 3;
int rbm = 11;

//sensors read to store value
int s[5];
int ss[2];
int j = 0;
int i = 0;


void setup() {
  //init pinmode
  
  pinMode(center,INPUT_PULLUP);
  pinMode(left1,INPUT_PULLUP);
  pinMode(right1,INPUT_PULLUP);
  pinMode(left2,INPUT_PULLUP);
  pinMode(right2,INPUT_PULLUP);
  pinMode(left3,INPUT_PULLUP);
  pinMode(right3,INPUT_PULLUP);
  pinMode(control_servo,OUTPUT);
  pinMode(lance_servo,OUTPUT);
 


  digitalWrite(10, HIGH);
 // digitalWrite(9, HIGH);
  
   digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  
 Control_servo.attach(control_servo);
 Lance_servo.attach(lance_servo);
  
 chk_pos(0); 
   //serial open
  Serial.begin(9600);
}

void loop() {

  read_sensor();
 
  value_pos();
  value_lance();

  
}




void chk_pos(int test){
  control_sarvo(s_dpos + test); 
}


void chk_lance(int test) {
  lance_sarvo(l_dpos + test); 
}


void lance_sarvo(int pos){
    Lance_servo.write(pos);
} 

void control_sarvo(int pos){

    Control_servo.write(s_dpos + pos);
   
} 


void value_pos(){

//大きな条件から細かな条件へ
  if((s[2] == Threshold)&&(s[3] == Threshold)&&(s[4] == Threshold)){
    //ちょい左
     chk_pos(-3);
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)&&(s[3] == Threshold)){
    //真ん中
     chk_pos(0);
  }else if ((s[1] == Threshold)&&(s[2] == 1)&&(s[3] == Threshold)){
    //ちょい右
    chk_pos(3);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
       chk_pos(3);
  }else if ((s[2] == Threshold)&&(s[3] == 0)&&(s[2] == Threshold)){
    //やや左
      chk_pos(-5);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)){
    //やや右
     chk_pos(5);
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)){
    //やや左
     chk_pos(-5);
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
    chk_pos(5);
  }else if ((s[2] == Threshold)&&(s[3] == Threshold)){
    //ちょい左
    chk_pos(-5);
  }else if ((s[0] == Threshold)&&(s[1] == 1)&&(s[2] == 1)){
    //左
    chk_pos(-35);
  }else if ((s[4] == Threshold)&&(s[3] == 1)&&(s[2] == 1)){
    //左
    chk_pos(25);
  }
  
 
}

void value_lance(){
  if ((ss[0] == 0) && (ss[1]==1)){
    chk_lance(0);
  }else if  ((ss[0] == 1) && (ss[1]==0)){
    chk_lance(1);
  }
}



void sensor_array_reset(){
    for(i=0;i<5;i++){
        s[i] = 1; 
    } 
    for(i=0;i<2;i++){
        ss[i] = 1; 
    }
} 

void read_sensor(){
    //sensor_array_reset();
    s[0] = digitalRead(left2);
    s[1] = digitalRead(left1);
    s[2] = digitalRead(center); 
    s[3] = digitalRead(right1);
    s[4] = digitalRead(right2);
    ss[0] = digitalRead(right3);
    ss[1] = digitalRead(left3);

//aaa
//    s[0] = PIND & _BV(left2);
//    s[1] = PIND & _BV(left1);
//    s[2] = PIND & _BV(center);
//    s[3] = PINB & _BV(right1);
//    s[4] = PINB & _BV(right2);
//    side_s[0] = PINB & _BV(right3);
//    side_s[1] = PINB & _BV(left3);
    if (reading_sensor){
      sensor_print(); 
    }
}



void sensor_print(){
  Serial.print(ss[0]);
  Serial.print(s[0]);
  Serial.print(s[1]);
  Serial.print(s[2]);
  Serial.print(s[3]);
  Serial.print(s[4]);
  Serial.println(ss[1]);
}





//
//
// 大きな条件から細かな条件へ
//  if((s[2] == Threshold)&&(s[3] == Threshold)&&(s[4] == Threshold)){
//    //ちょい左
//     control_sarvo(-3);
//  }else if ((s[1] == Threshold)&&(s[2] == Threshold)&&(s[3] == Threshold)){
//    //真ん中
//     control_sarvo(0);
//  }else if ((s[1] == Threshold)&&(s[2] == 1)&&(s[3] == Threshold)){
//    //ちょい右
//    control_sarvo(3);
//  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&(s[2] == Threshold)){
//    //ちょい右
//       control_sarvo(3);
//  }else if ((s[2] == Threshold)&&(s[3] == 0)&&(s[2] == Threshold)){
//    //やや左
//      control_sarvo(-5);
//  }else if ((s[0] == Threshold)&&(s[1] == Threshold)){
//    //やや右
//     control_sarvo(5);
//  }else if ((s[3] == Threshold)&&(s[4] == Threshold)){
//    //やや左
//     control_sarvo(-5);
//  }else if ((s[1] == Threshold)&&(s[2] == Threshold)){
//    //ちょい右
//    control_sarvo(5);
//  }else if ((s[2] == Threshold)&&(s[3] == Threshold)){
//    //ちょい左
//    control_sarvo(-5);
//  }else if ((s[0] == Threshold)&&(s[1] == 1)&&(s[2] == 1)){
//    //左
//    control_sarvo(-35);
//  }else if ((s[4] == Threshold)&&(s[3] == 1)&&(s[2] == 1)){
//    //左
//    control_sarvo(25);
//  }

