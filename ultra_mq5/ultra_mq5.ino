/*
  LED & (부저)
  ON - 녹색점등(삐소리3초)
  50cm - 황색점등(삐-삐-삐-반복)
  30cm - 황색점등(삐-삐-삐-반복,빠르게)
  10cm - 적색점등(삐-계속)

  가스검출시 - 녹+황+적 점멸반복(점멸주기와 비슷한 부저동작) / 또는 계속점등(삐-계속)
  가스검출이 더 안되면 거리측정모드로 돌아가기
  가스누출이 인지되면 블루투스 연결된 휴대폰으로 농도가 얼마인지 확인
*/

#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX, TX

#define GAS A0

#define RED 5
#define YELLOW 6
#define GREEN 7

#define BUZZER 12

void setup()
{
  pinMode(GAS, INPUT); // MQ 가스 센서 입력 모드로 설정
  pinMode(RED, OUTPUT); // LED 출력 모드로 설정
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT); // 부저 출력 모드로 설정

  BT.begin(9600); // 블루투스 통신 속도 설정
  Serial.begin(9600);

  digitalWrite(GREEN, HIGH); // 녹색점등(삐소리3초)
  digitalWrite(BUZZER, HIGH);
  delay(3000);
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZER, LOW);
}

void loop()
{
  int gas_value = analogRead(GAS); // MQ 가스 센서 값 읽어오기
  Serial.println(gas_value);

  if (gas_value >= 800) // 가스 검출 (기준값 800 이상)
  {
    Serial.println("gas active");
    digitalWrite(RED, HIGH); // 계속점등(삐-계속)
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(500);
    BT.print(gas_value); // 블루투스로 검출된 가스 값 보내기
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else // 가스 미검출 (기준값 800 미만)
  {
    Serial.println("gas deactive");
    float ultra1_value = ReadUltrasonic(11, 10); // 초음파 센서1 값 읽어오기
    float ultra2_value = ReadUltrasonic(9, 8); // 초음파 센서2 값 읽어오기

    float ultra_value = min(ultra1_value, ultra2_value); // 초음파 센서 작은 값 기준
    Serial.println(ultra_value);

    if (ultra_value <= 10.0) // 10cm 이하
    {
      digitalWrite(RED, HIGH); // 적색점등(삐-계속)
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      digitalWrite(BUZZER, LOW);

    }
    else if (ultra_value <= 30.0) // 30cm 이하
    {
      digitalWrite(YELLOW, HIGH); // 황색점등(삐-삐-삐-반복, 빠르게)
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(YELLOW, LOW);
      digitalWrite(BUZZER, LOW);
      delay(200);
    }
    else if (ultra_value <= 50.0) // 50cm 이하
    {
      digitalWrite(YELLOW, HIGH); // 황색점등(삐-삐-삐-반복)
      digitalWrite(BUZZER, HIGH);
      delay(500);
      digitalWrite(YELLOW, LOW);
      digitalWrite(BUZZER, LOW);
      delay(500);
    }
  }
  delay(10);
}


float ReadUltrasonic(int trig, int echo)
{
  pinMode(trig, OUTPUT);  // Clear the trigger
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);

  // Reads the echo pin, and returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(echo, HIGH);

  // measure the ping time in cm
  float distance = ((float)(340 * duration) / 10000) / 2;

  return distance;
}
