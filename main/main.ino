#define portOfPin(P)\
(((P)>=0&&(P)<8)?&PORTD:(((P)>7&&(P)<14)?&PORTB:&PORTC))
#define ddrOfPin(P)\
(((P)>=0&&(P)<8)?&DDRD:(((P)>7&&(P)<14)?&DDRB:&DDRC))
#define pinOfPin(P)\
(((P)>=0&&(P)<8)?&PIND:(((P)>7&&(P)<14)?&PINB:&PINC))
#define pinIndex(P)((uint8_t)(P>13?P-14:P&7))
#define pinMask(P)((uint8_t)(1<<pinIndex(P)))

#define pinAsInput(P) *(ddrOfPin(P))&=~pinMask(P)
#define pinAsInputPullUp(P) *(ddrOfPin(P))&=~pinMask(P);digitalHigh(P)
#define pinAsOutput(P) *(ddrOfPin(P))|=pinMask(P)
#define digitalLow(P) *(portOfPin(P))&=~pinMask(P)
#define digitalHigh(P) *(portOfPin(P))|=pinMask(P)
#define isHigh(P)((*(pinOfPin(P))& pinMask(P))>0)
#define isLow(P)((*(pinOfPin(P))& pinMask(P))==0)
#define digitalState(P)((uint8_t)isHigh(P))

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

int lss[10];
int rss[10];
int scount = 0;
boolean sschk = false;
unsigned long sensor_count;


int p = 0;
int chk = 0;


int linecount = 0;

void setup() {
  //init pinmode
  
  pinAsInputPullUp(center);
  pinAsInputPullUp(left1);
  pinAsInputPullUp(right1);
  pinAsInputPullUp(left2);
  pinAsInputPullUp(right2);
  pinAsInputPullUp(left3);
  pinAsInputPullUp(right3);
 
  pinAsOutput(control_servo);
  pinAsOutput(lance_servo);

  pinAsOutput(lfm);
  pinAsOutput(rfm);
  pinAsOutput(lbm);
  pinAsOutput(rbm);

  digitalHigh(lfm);
  digitalHigh(rfm);
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
  chk_past_sensor();
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
     chk_pos(-1);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&(s[2] == Threshold)){
    ////ちょい左
     chk_pos(1);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&chk_mark){
    //やや右
     chk_pos(5);
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)&&chk_mark){
    //やや左
     chk_pos(-8);
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
    chk_pos(2);
  }else if ((s[2] == Threshold)&&(s[3] == Threshold)){
    //ちょい左
    chk_pos(-2);
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)){
    //やや右
     chk_pos(2);
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)){
    //やや左
     chk_pos(-2);
  }else if ((s[4] == Threshold)&&chk_mark){
    //左
    curve_line();
  }else if ((s[0] == Threshold)&&chk_mark){
    //右
    chk_pos(15);
  }
  
  
}

void curve_line(){
 if ((time - curvetime) > 1200){
    chk_pos(-18);
 }else if((time - curvetime) > 1000){
    chk_pos(-22);
 }else if((time - curvetime) > 800){
    chk_pos(-24);
 }else if((time - curvetime) > 500){
    chk_pos(-30);
  
 }else{
   chk_pos(-23);
 }
}

void value_lance(){
  if ((ss[0] == 0) && (ss[1]==1)){
     chk_lance(20);
     
  }else if  ((ss[0] == 1) && (ss[1]==0)){
    chk_lance(160);

  }
}


void chk_past_sensor(){

  
}

void pwm_chk(){
   if ((ss[0] == 0) && (ss[1]==0)){
      if(!chk_mark&&((time - chktime) > 1500)||first){     
        digitalLow(lfm);
        digitalLow(rfm);
        analogWrite(lbm,255);
        analogWrite(rbm,255);   
        chk_mark = true;
        first = false;
        curvetime = time;
        chktime = time;
        st_time = time;
        sschk = false;
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

   
   if(chk_mark&&(time - st_time) > 1800){
        digitalWrite(lfm,LOW);
        digitalWrite(rfm,LOW);
        analogWrite(lbm,222);
        analogWrite(rbm,255);
        chktime = time;
        curvetime = 0;
   }
    if(chk_mark&&(time - st_time) > 2200){
        digitalWrite(lfm,HIGH);
        digitalWrite(rfm,HIGH);
         analogWrite(lbm,255);
        analogWrite(rbm,255);
         chk_mark = false;
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
    s[0] = digitalState(left2);
    s[1] = digitalState(left1);
    s[2] = digitalState(center); 
    s[3] = digitalState(right1);
    s[4] = digitalState(right2);
    ss[0] = digitalState(right3);
    ss[1] = digitalState(left3);


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



