#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display dsp(CLK, DIO);

unsigned long cTime;
unsigned long rTime = 0;
unsigned long bTime = 0;
int second = 0;
int minute = 0;
int timeData = 0;
bool blinkToggle = false;

bool state = true; // true면 시간이 흘러가고, false면 시간이 멈춰 있는다.

void setup()
{
  pinMode(6, INPUT_PULLUP); // stop 버튼
  pinMode(7, INPUT_PULLUP); // reset 버튼
  dsp.setBrightness(7); // 밝기 설정
  dsp.showNumberDecEx(0, 0x40, true);
}

void loop()
{
  if (digitalRead(6) == LOW)
  {
    state = !state;
    while (!digitalRead(6));
  }
  if (digitalRead(7) == LOW)
  {
    second = minute = timeData = 0; // 시간 초기화
    while (!digitalRead(7));
  }
  if (state)
  {
    cTime = millis(); // 현재 시간 측정
    if (cTime - rTime > 999)
    {
      second++;
      if (second > 59)
      {
        second = 0;
        minute++;
        if (minute > 59)
        {
          minute = 0;
        }
      }
      timeData = minute * 100 + second;
      rTime = cTime;
    }
  }

  if (cTime - bTime > 499) // 깜빡이기
  {
    if (blinkToggle)
    {
      dsp.showNumberDecEx(timeData, 0x40, true);
      blinkToggle = false;
    }
    else
    {
      dsp.showNumberDecEx(timeData, 0, true);
      blinkToggle = true;
    }
    bTime = cTime;
  }
}
