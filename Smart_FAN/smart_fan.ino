#include <Servo.h>
Servo servo; // 서보모터 객체 설정

int number[4][7] = {
  {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0}, {1,1,0,1,1,0,1}, {0,0,0,0,0,0,0}}; // 0~2, NULL 캐소드형

int echo = 12;
int trig = 13;
int servopin = 10;

void segment_number(int n) // 세그먼트 숫자 출력
{
  for(i=0; i<7; i++)
    digitalWrite(i+3, number[n][i]);
}
float read_distance() // 초음파센서 거리 읽기
{
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  return (((float)(340 * duration) / 10000) / 2); // 거리 반환
}
float read_temperature() // 온도 값 읽기
{
  int value = analogRead(A0);
  float temp = float(value)*5.0/1023.0
  return (temp*100-50.0);
}
//////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  for(i=3; i<=9; i++) // 세그먼트 LED
    pinMode(i, OUTPUT);
  
  pinMode(trig, OUTPUT); // 초음파 센서
  pinMode(echo, INPUT);
  
  servo.attach(servopin); // 서보모터 시작
  servo.write(0);
}
void loop() 
{
  float temp = read_temperature();
  Serial.print("temp - ");
  Serial.println(temp);
  
  if(temp >= 28.0) // 28도 이상
  {
    float distance = read_distance(); // 거리 읽어오기
    Serial.print("distance - ");
    Serial.print(distance);
    
    int state;
    if(distance <= 50.0) state = 2;
    else if(distance <= 100.0) state = 1;
    else state = 0;
      
    
  }
  
  Serial.println("");
  delay(100);
}