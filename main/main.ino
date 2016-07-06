//mainboard
#define reading_sensor true
#include <Servo.h>

//pin info 
int left2 = 2;
int left1 = 4;
int center = 7;
int right1 = 8;
int right2 = 9;
int left3 = 13;
int right3 = 12;

int dpos = 0;
int Threshold = 0;
//sensors read to store value
int s[5];
int side_s[2];
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
 
   //serial open
  Serial.begin(9600);
}

void loop() {
  read_sensor();
 
  //chk_pos();
  //chk_lance();

  
}


void chk_pos(){
  if(s[1] == Threshold&&s[2] == Threshold &&s[3] == Threshold){
   senddata('A'); // 0
  }else if(s[2] == Threshold&&s[3] == Threshold&&s[4] == Threshold){
  senddata('B'); ///3
  }else if(s[0] == Threshold &&s[1] == Threshold&&s[2] == Threshold){
   senddata('C'); ///-3
  }else if(s[2] == Threshold&&s[3] == Threshold){
   senddata('B'); ///3
  }else if(s[1] == Threshold&&s[2] == Threshold){
   senddata('C'); ///-3
  }else if(s[3] == Threshold&&s[4] == Threshold){
  senddata('D'); ///5
  }else if(s[0] == Threshold&&s[1] == Threshold){
  senddata('E'); ///-8
  }else if(s[0] == Threshold){
  senddata('F'); ///-30
  }else if(s[4] == Threshold){
   senddata('G'); ///15
  }   

 
   
}

void chk_lance(){
  
}

void senddata(char value){
  Serial.write(value);
}

void sensor_array_reset(){
    for(i=0;i<5;i++){
        s[i] = 99; 
    } 
    for(i=0;i<2;i++){
        side_s[i] = 99; 
    }
} 

void read_sensor(){
    sensor_array_reset();
    s[0] = digitalRead(left2);
    s[1] = digitalRead(left1);
    s[2] = digitalRead(center); 
    s[3] = digitalRead(right1);
    s[4] = digitalRead(right2);
    side_s[0] = digitalRead(right3);
    side_s[1] = digitalRead(left3);

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
  Serial.print(side_s[0]);
  Serial.print(s[0]);
  Serial.print(s[1]);
  Serial.print(s[2]);
  Serial.print(s[3]);
  Serial.print(s[4]);
  Serial.println(side_s[1]);
}

