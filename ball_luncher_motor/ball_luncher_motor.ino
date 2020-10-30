#include <Servo.h>

int L_motor = 7; // DC 모터
int R_motor = 8;
int S_motor = 6; // pvc 모터
int LED = 2; // 솔레노이드
int servopin = 5;

int echo = 12;
int trig = 13;
int ir = 3;
Servo servo; // 서보모터 객체 선언

int cnt = 0; // 공을 던진 횟수

void m_front()
{
  Serial.println("motor front");
  digitalWrite(L_motor, HIGH);
  digitalWrite(R_motor, HIGH);
  delay(100);
}
void m_right()
{
  Serial.println("motor right");
  digitalWrite(L_motor, LOW);
  digitalWrite(R_motor, HIGH);
  delay(50);
}
void m_left()
{
  Serial.println("motor left");
  digitalWrite(L_motor, LOW);
  digitalWrite(R_motor, HIGH);
  delay(50);
}
void m_stop()
{
  Serial.println("motor stop");
  digitalWrite(L_motor, LOW);
  digitalWrite(R_motor, LOW);
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
void shoot() // 공 2개 발사하기
{
  int i;
  for (i = 0; i < 2; i++)
  {
    Serial.println("ball shoot");
    servo.write(10);
    delay(1000);
    servo.write(15);
    delay(1000);
    servo.write(135);
    delay(500);
    servo.write(15);
    delay(500);
  }
  cnt++;
}
void pvc_shoot()
{
  digitalWrite(S_motor, HIGH);
  delay(500);
  digitalWrite(S_motor, LOW);
}
void setup()
{
  pinMode(L_motor, OUTPUT);
  pinMode(R_motor, OUTPUT);
  pinMode(S_motor, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(trig, OUTPUT); // 초음파 센서
  pinMode(echo, INPUT);
  pinMode(ir, INPUT); // ir 센서

  Serial.begin(9600); // 시리얼 통신

  m_stop();
  digitalWrite(LED, LOW);
  servo.attach(servopin); // 서보모터 시작
  servo.write(15);
}

void loop()
{
  while (1)
  {
    float distance = read_distance(); // 거리 읽어오기
    int ir_value = digitalRead(ir); // ir 센서 값 읽어오기
    float value = 0;

    if (cnt == 3) value = 15.24; // 6inch
    else if (cnt == 4) value = 30.48; // 12inch
    else if (cnt == 5) value = 45.72; // 18inch

    if (distance > 182.8 + value && ir_value == 1) // 전방에 위치, 멀리 있을때
    {
      while (read_distance() > 182.8 + value) m_front(); // 72인치 + value 이내일 때까지 전진
      m_stop();
      shoot(); // 공 발사
    }
    else if (distance < 182.8 + value && ir_value == 1) // 전방에 위치, 가까이 있을때
    {
      shoot(); // 공 발사
    }
    if (ir_value == 0) // 물체가 인식이 되지 않을때
    {
      while (digitalRead(ir_value) == 1) m_right(); // 물체가 인식될 때까지 회전
      m_stop();
    }
    if (cnt >= 6) break; // 6곳에 공을 던지면 종료

    Serial.print("cnt : ");
    Serial.print(cnt);
    Serial.print(", ir : ");
    Serial.print(ir_value); // ir, 거리 값 Serial 출력
    Serial.print(", distance : ");
    Serial.println(distance);
  }
  while (1) // pvc 파이프위에 공까지 모터 돌리기
  {
    Serial.println("pvc");
    float distance = read_distance(); // 거리 읽어오기
    int ir_value = digitalRead(ir); // ir 센서 값 읽어오기

    if (distance > 182.8 && ir_value == 1) // 전방에 위치, 멀리 있을때
    {
      while (read_distance() > 182.8) m_front(); // 72인치 이내일 때까지 전진
      m_stop();
      pvc_shoot();
      break;
    }
    else if (distance < 182.8 && ir_value == 1) // 전방에 위치, 가까이 있을때
    {
      pvc_shoot();
      break;
    }
    if (ir_value == 0) // 물체가 인식이 되지 않을때
    {
      while (digitalRead(ir) == 1) m_right(); // 물체가 인식될 때까지 회전
      m_stop();
    }
  }
  Serial.println("finish");
  digitalWrite(LED, HIGH); // 솔레노이드 작동
  delay(1000);
  return; // 작업이 끝나면 종료
}
