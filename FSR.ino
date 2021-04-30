#include <Servo.h> // 서보모터 라이브러리 추가하기
Servo ser1; // 서보모터 객체 설정
Servo ser2;

int FSR_pin = A0; // 압력센서가 연결된 핀
int Servo1_pin = 9; // 1번 서보모터가 연결된 핀
int Servo2_pin = 10; // 2번 서보모터가 연결된 핀

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도 설정
  ser1.attach(Servo1_pin);
  ser2.attach(Servo2_pin);
  ser1.write(0); // 서보모터 초깃값 설정
  ser2.write(0);
}

void loop() {
  int i;
  long long int sum = 0;
  for (i = 0; i < 100; i++) { // 데이터 100회 수집하기
    sum += analogRead(FSR_pin); // 압력 센서 값 읽어오기
    delay(5);
  }
  int average = sum / 100; // 데이터의 평균값 구하기
  Serial.print("FSR sensor data average : ");
  Serial.println(average); // 시리얼 모니터로 데이터 확인하기

  if (average > 700) { // 데이터의 평균값이 700 이상이면
    ser1.write(90); // 서보모터 움직이기
    ser2.write(90);
  }
  delay(1000);
}
