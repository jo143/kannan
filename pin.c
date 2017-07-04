//PWM Pins Defination
#define MOT1_EN 10
#define MOT2_EN 11

//Digital Pins for Motors
#define MOT1_IN1 7
#define MOT1_IN2 8

#define MOT2_IN1 12
#define MOT2_IN2 13

//Analog Pins for Sensors
#define SENSOR1 A0
#define SENSOR2 A1

int left_sensor_data = 0;
int right_sensor_data = 0;
int spd = 0;
int spdstr = 255;

void setup(){
  pinMode(MOT1_EN,OUTPUT);
  pinMode(MOT2_EN,OUTPUT);
  pinMode(MOT1_IN1,OUTPUT);
  pinMode(MOT1_IN2,OUTPUT);
  pinMode(MOT2_IN1,OUTPUT);
  pinMode(MOT2_IN2,OUTPUT);
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  digitalWrite(MOT1_IN1,LOW);
  digitalWrite(MOT1_IN2,HIGH);
  digitalWrite(MOT2_IN1,LOW);
  digitalWrite(MOT2_IN2,HIGH);
  Serial.begin(9600);
}

void loop(){
  
  left_sensor_data = get_sensor_left_data()*(5.0/1023.0);
  right_sensor_data = get_sensor_right_data()*(5.0/1023.0);
  
  if(left_sensor_data > 2 && right_sensor_data < 2){
    spd = map(left_sensor_data,0,3000,0,255);
    move_left(spd);
  }
  else{
    if(right_sensor_data > 2 && left_sensor_data < 2){
      spd = map(right_sensor_data,0,3000,0,255);
      move_right(spd);
    }
    else{
      if(right_sensor_data > 2 && left_sensor_data > 2){
        move_stop();
      }
      else
        move_straight(spdstr);
    }
  }
  delay(50);
  //Serial.println(sensor_data);
  //delay(1000);
  /*move_straight(255);
  delay(2000);
  move_straight(0);
  delay(1000);
  move_left(255); 
  delay(1000);
  move_straight(255);
  delay(2000);*/
}
int get_sensor_right_data(){
  int data = 0;
  data += analogRead(SENSOR2);
  return data;
  
}

int get_sensor_left_data(){
  int data = 0;
  data += analogRead(SENSOR1);
  return data;
}

void move_straight(int spd){
  analogWrite(MOT1_EN,spd);
  analogWrite(MOT2_EN,spd);
}

void move_left(int spd){
  analogWrite(MOT1_EN,spd);
  analogWrite(MOT2_EN,0);
}

void move_right(int spd){
  analogWrite(MOT1_EN,0);
  analogWrite(MOT2_EN,spd);
}

void move_stop(){
  analogWrite(MOT1_EN,0);
  analogWrite(MOT2_EN,0);
}
