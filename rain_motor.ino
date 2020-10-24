/*
빗물 감기 센서에 빗물이 인식되면 자동으로 창문을 닫고 빗물이 인식되지 않을 경우 창문을 연다.
창문을 닫는 중에 리미트 스위치에 닿을 경우 창문을 닫는 동작을 멈춘다.
*/
#define sensor A0
#define sw_left 2
#define sw_right 3

int state = 0; // 0 open / 1 close
int now_state = 0;

int m_step = 4;
int m_dir = 5;
int m_ena = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(sw_left, INPUT_PULLUP); // 리미트 스위치
  pinMode(sw_right, INPUT_PULLUP);

  pinMode(m_step, OUTPUT);
  pinMode(m_dir, OUTPUT);
  pinMode(m_ena, OUTPUT);

  digitalWrite(m_step, HIGH);
  digitalWrite(m_ena, HIGH);
}

void loop()
{
  int rain_value = analogRead(sensor); // 센서 값 읽어오기

  if (rain_value < 500) state = 1; // 빗물이 감지되면 저항 값이 500이하로 떨어진다
  else state = 0;

  if (now_state != state) // 전의 상태와 다를 경우
  {
    if (state == 0)
    {
      while (1) // 스위치에 감지될 때까지 스텝 모터 동작
      {
        digitalWrite(m_dir, HIGH);
        digitalWrite(m_step, LOW);
        delayMicroseconds(100);
        digitalWrite(m_step, HIGH);
        int sw_left_value = digitalRead(sw_left);
        if (sw_left_value == 1) break;
      }
    }
    else
    {
      while (1)
      {
        digitalWrite(m_dir, LOW);
        digitalWrite(m_step, LOW);
        delayMicroseconds(100);
        digitalWrite(m_step, HIGH);
        int sw_right_value = digitalRead(sw_right);
        if (sw_right_value == 1) break;
      }
    }
    delay(500);
    now_state = state; // 현재 상태 변경
  }
  delay(10);
}
