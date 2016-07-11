//mainboard
#define reading_sensor true
#define  s_dpos  93
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


int Threshold = 0;

Servo Control_servo;
Servo Lance_servo; 

unsigned long time;
unsigned long chktime;
unsigned long chkline;
unsigned long curvetime;
unsigned long st_time;
 
int lfm = 9;
int rfm = 10;
int lbm = 3;
int rbm = 11;

boolean chk_mark = false;
boolean first = true;
boolean first_line = true;

int total_value = 0;

//sensors read to store value
int s[5];
int ss[2];
int j = 0;
int i = 0;

int p = 0;
int chk = 0;

int linecount = 0;

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

  pinMode(lfm,OUTPUT);
  pinMode(rfm,OUTPUT);
  pinMode(lbm,OUTPUT);
  pinMode(rbm,OUTPUT);

  digitalWrite(lfm,HIGH);
  digitalWrite(rfm,HIGH);
  analogWrite(lbm,255);
  analogWrite(rbm,255);
  
  Control_servo.attach(control_servo);
  Lance_servo.attach(lance_servo);
  
  chk_lance(90);
  chk_pos(0); 

  Serial.begin(9600);
}

void loop() {
  time = millis();
  read_sensor();
  value_pos();
  value_lance();
  pwm_chk();

}




void chk_pos(int test){
  
  total_value += test; 
  Control_servo.write(s_dpos + test);
   
}


void chk_lance(int test) {
  Lance_servo.write(l_dpos + test);
}



void value_pos(){

  if((s[1] == Threshold)&&(s[2] == Threshold)&&(s[3] == Threshold)){
    //真ん中
     chk_pos(0);
  }else if ((s[2] == Threshold)&&(s[3] == Threshold)&&(s[4] == Threshold)){
    ////ちょい左
     chk_pos(-2);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&(s[2] == Threshold)){
    ////ちょい左
     chk_pos(2);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&chk_mark){
    //やや右
     chk_pos(8);
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)&&chk_mark){
    //やや左
     chk_pos(-8);
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
    chk_pos(3);
  }else if ((s[2] == Threshold)&&(s[3] == Threshold)){
    //ちょい左
    chk_pos(-3);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)){
    //やや右
     chk_pos(3);
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)){
    //やや左
     chk_pos(-3);
  }else if ((s[4] == Threshold)&&chk_mark){
    //左
    curve_line();
  }else if ((s[0] == Threshold)&&chk_mark){
    //右
    chk_pos(15);
  }
  
  
}

void curve_line(){
    analogWrite(lbm,155);
    analogWrite(rbm,225);
 if ((time - curvetime) > 1200){
    chk_pos(-20);
 }else if((time - curvetime) > 1000){
    chk_pos(-23);
 }else if((time - curvetime) > 800){
    chk_pos(-28);
 }else if((time - curvetime) > 500){
    chk_pos(-35);
  
 }else{
   chk_pos(-20);
 }
}

void value_lance(){
  if ((ss[0] == 0) && (ss[1]==1)){
     chk_lance(0);
     
  }else if  ((ss[0] == 1) && (ss[1]==0)){
    chk_lance(180);
    if(((time - chkline) > 1000)||first_line){ 
         chkline = time;
         firstline = false;
         linecount += 1; 
      }
  }
}


void pwm_chk(){
   if ((ss[0] == 0) && (ss[1]==0)){
      if(!chk_mark&&((time - chktime) > 1500)||first){     
        digitalWrite(lfm,LOW);
        digitalWrite(rfm,LOW);
        analogWrite(lbm,0);
        analogWrite(rbm,0);   
        delay(200);
        analogWrite(lbm,170);
        analogWrite(rbm,210);
        chk_mark = true;
        first = false;
        curvetime = time;
        chktime = time;
        st_time = time;
        linecount = 0; 
      }else if (chk_mark&&((time - chktime) > 1500)){
        digitalWrite(lfm,HIGH);
        digitalWrite(rfm,HIGH);
        chk_mark = false;
        analogWrite(lbm,255);
        analogWrite(rbm,255);
        chktime = time;
        curvetime = 0;
      }
   }

   if(chk_mark&&(time - st_time) > 4000){
        digitalWrite(lfm,HIGH);
        digitalWrite(rfm,HIGH);
        chk_mark = false;
        analogWrite(lbm,255);
        analogWrite(rbm,255);
        chktime = time;
        curvetime = 0;
   }

   if (linecount => 2){
      digitalWrite(lfm,LOW);
      digitalWrite(rfm,LOW);
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



