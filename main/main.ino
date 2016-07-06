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
  pinMode(center,INPUT);
  pinMode(left1,INPUT);
  pinMode(right1,INPUT);
  pinMode(left2,INPUT);
  pinMode(right2,INPUT);
  pinMode(left3,INPUT);
  pinMode(right3,INPUT);
 
   //serial open
  Serial.begin(9600);
}

void loop() {
  read_sensor();
 
  chk_pos();
  chk_lance();

  
}


void chk_pos(){
  //大きな条件から細かな条件へ
  if((s[2] == Threshold)&&(s[3] == Threshold)&&(s[4] == Threshold)){
    //ちょい左
    senddata('C');
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)&&(s[3] == Threshold)){
    //真ん中
     senddata('A');
  }else if ((s[1] == Threshold)&&(s[2] == 1)&&(s[3] == Threshold)){
    //ちょい右
    senddata('B');
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
     senddata('B');
  }else if ((s[2] == Threshold)&&(s[3] == 0)&&(s[2] == Threshold)){
    //やや左
     senddata('D');
  }else if ((s[0] == Threshold)&&(s[1] == Threshold)){
    //やや右
     senddata('E');
  }else if ((s[3] == Threshold)&&(s[4] == Threshold)){
    //やや左
     senddata('D');
  }else if ((s[1] == Threshold)&&(s[2] == Threshold)){
    //ちょい右
    senddata('B');
  }else if ((s[2] == Threshold)&&(s[3] == Threshold)){
    //ちょい左
    senddata('C');
  }else if ((s[0] == Threshold)&&(s[1] == 1)&&(s[2] == 1)){
    //左
    senddata('F');
  }else if ((s[4] == Threshold)&&(s[3] == 1)&&(s[2] == 1)){
    //左
    senddata('G');
  }

  
  if (( side_s[0]== Threshold)&&(side_s[1]== Threshold)){
    senddata('H'); ///15
     delay(1500);
  }
  
}

void chk_lance(){
  
}

void senddata(char value){
  Serial.write(value);
}

void sensor_array_reset(){
    for(i=0;i<5;i++){
        s[i] = 1; 
    } 
    for(i=0;i<2;i++){
        side_s[i] = 1; 
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

//

