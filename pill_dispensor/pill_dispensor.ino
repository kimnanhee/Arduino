#include <Servo.h>
Servo servo0, servo1, servo2, servo3, servo4; // Servo, servo0~4 객체 설정

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // LiquidCrystal_I2C, lcd 객체 설정

#define NUM 5 // 서보 모터 연결 개수

int reset_btn = A0, led = 2, buzzer = 13; // reset button, led, buzzer 연결 핀 설정

int buttons[NUM] = {12, 8, 7, 4, 3}; // button 연결 핀 배열 설정
int counts[NUM]  = {0, 0, 0, 0, 0}; // count 횟수 배열 설정

void lcd_screen()
{
  lcd.clear(); // lcd 초기화
  lcd.setCursor(0, 0); // lcd 커서 0행 0열 설정
  for (int i = 0; i < NUM; i++)
  {
    lcd.print(counts[i]); // lcd에 count 출력
    lcd.print(" ");

    Serial.print(counts[i]); // Serial 모니터에 count 출력
    Serial.print("  ");
  }
  Serial.println("");
}

void led_buzzer_write(int ms) // led와 buzzer 연결 핀에 ms동안 HIGH 상태 출력
{
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(ms);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(ms);
}

void servo_write(int i, int ms) // i번째 모터 연결 핀에 90도 출력 후 ms동안 상태 유지, 0도 출력
{
  if (i == 0) {
    servo0.write(90); // 90도 회전
    delay(ms); // 딜레이
    servo0.write(0); // 0도 회전
  }
  else if (i == 1) {
    servo1.write(90);
    delay(ms);
    servo1.write(0);
  }
  else if (i == 2) {
    servo2.write(90);
    delay(ms);
    servo2.write(0);
  }
  else if (i == 3) {
    servo3.write(90);
    delay(ms);
    servo3.write(0);
  }
  else if (i == 4) {
    servo4.write(90);
    delay(ms);
    servo4.write(0);
  }
}
////////////////////////////////////////////////////////////

void setup()
{
  pinMode(reset_btn, INPUT_PULLUP); // reset 핀 input_pullup 설정
  pinMode(led, OUTPUT); // led 핀 출력 설정
  digitalWrite(led, LOW);

  for (int i = 0; i < NUM; i++)
    pinMode(buttons[i], INPUT_PULLUP); // button[i] 핀 input_pullup 설정

  pinMode(buzzer, OUTPUT); // buzzer 핀 출력 설정
  digitalWrite(buzzer, LOW);

  servo0.attach(11); // servo0~5 핀 설정, 0도 초기 출력
  servo0.write(0);
  servo1.attach(10);
  servo1.write(0);
  servo2.attach(9);
  servo2.write(0);
  servo3.attach(6);
  servo3.write(0);
  servo4.attach(5);
  servo4.write(0);

  Serial.begin(9600); // serial 통신 초기화

  lcd.init(); // lcd 시작
  lcd.backlight(); // lcd 백라이트 설정
  lcd_screen(); // lcd 초기 출력
}

void loop()
{
  if (analogRead(reset_btn) == LOW) // reset에 연결된 버튼이 눌렸을 경우
  {
    while (analogRead(reset_btn) == LOW); // 버튼이 눌려있는 상태 동안 유지

    for (int i = 0; i < NUM; i++) // count 배열 0 초기화
      counts[i] = 0;

    for (int i = 0; i < 3; i++)
      led_buzzer_write(200); // 200ms 동안 led, buzzer 출력
  }

  for (int i = 0; i < NUM; i++)
  {
    if (digitalRead(buttons[i]) == LOW) // button[i]에 연결된 버튼이 눌렸을 경우
    {
      while (digitalRead(buttons[i]) == LOW); // 버튼이 눌려있는 상태 동안 유지

      counts[i]++; // count 배열에 i번째 값 1 증가
      lcd_screen(); // lcd 출력

      led_buzzer_write(200); // 200ms 동안 led, buzzer 출력
      servo_write(i, 2000); // i번째 서보모터 90 회전 후 상태 2000ms 유지, 원래 각도로 복귀
    }
  }
  delay(1); // 1ms 지연
}
