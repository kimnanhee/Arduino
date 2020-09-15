#include <core_build_options.h>
#include <swRTC.h>
swRTC rtc; // rtc 객체 설정

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // lcd 객체 설정

int blue = 4; // blue 스위치 핀 
int black = 5; // black 스위치 핀 
int white = 6; // white 스위치 핀
int piezo = 8; // 부저 핀
int temp; // 날짜 저장 변수 
int cnt = 0; // 문제 맞춘 횟수를 저장하는 변수 
int btn = 0; // 눌러야 하는 버튼을 저장하는 변수 
int flag = 0; // 알람이 울리는 중인지 저장하는 변수
char* colors[] = {"green     ", "yellow    ", "white    "};
// 출력에 사용 할 문자열 배열

String lcdString = "";     

//AM PM을 구분해 주는 함수
void Set_AMPM(int hour) 
{
  if(hour >=12) // 12시 보다 크면 
    lcd.print("PM "); // PM출력 
  else lcd.print("AM "); // 아니면 AM 출력

  lcd.print(hour%12, DEC);     //시간 출력, hour를 12로 나눈 나머지를 10진수로 출력.
}

//10보다 작은수를 출력할때 앞에 0을 출력하게 하는 함수
void Set_lowThanTen(int time) 
{
  if(time < 10) // 10보다 작으면
  {
    lcd.print("0"); // 0 출력 
    lcd.print(time%10); // 10으로 나눈 나머지 출력
  }
  else // 10보다 크면 
    lcd.print(time); // 그냥 출력
}

//유효한 알람시간인지 체크하는 함수
int checkTheAlarmClock(int time) {
  if(time/100 < 24 && time %100 < 60) // 시간이 24시간 미만이고 분이 60분 미만이라면 
  {
    Serial.println("Success"); // 성공 출력 
    return time; // 시간 반환 
  }
  else { // 아니면 
    Serial.println("Failed"); // 실패 출력 
    return 0; // 0 반환
  }  
}

//알람이 울릴시간인지 체크하는 함수
void checkTheAlarmTime(int alarmHour, int alarmMinute) 
{
  // 알람이 꺼져 있을때만 검사 (flag == 0)
  if(flag == 0 && alarmHour == rtc.getHours() && alarmMinute == rtc.getMinutes()) 
  {
    digitalWrite(piezo, 1); // 부저 울리기 
    flag = 1; // 알람이 울린다는 플래그 1로 설정
    btn = random(3); // 문제 랜덤 출제
    lcd.setCursor(19, 2); 
    lcd.print("0"); // 문제 맞춘 횟수 출력, 아직 아무것도 안했으니 0
  }
}

void setup() 
{
  Serial.begin(9600); // 속도 9600bps로 시리얼 통신시작
  randomSeed(analogRead(0));
  pinMode(blue, INPUT_PULLUP); // 모든 버튼 PULLUP 스위치 사용
  pinMode(black, INPUT_PULLUP);
  pinMode(white, INPUT_PULLUP);
  pinMode(piezo, 8); 
  
  lcd.init(); // lcd 시작
  lcd.backlight(); // lcd 백라이트 on

  rtc.stopRTC(); // RTC 정지
  rtc.setTime(23, 15, 40); //시간, 분, 초
  rtc.setDate(11, 6, 2020); //일, 월, 년
  rtc.startRTC(); //시작
}

void loop() 
{ 
  if (flag) // 알람이 울린다면
  {
        lcd.setCursor(0, 2);
        lcd.print(colors[btn]); // 색깔 문자열 출력
        if (digitalRead(btn + 4) == LOW) // 맞는 버튼이 눌렸다면
        {
          cnt++; // 맞춘 횟수 증가 
          lcd.setCursor(19, 2);
          lcd.print(cnt); // 총 맞춘 문제 갯수 출력
          btn = random(3); // 다음 문제 출제
        }

        if (cnt > 4) // 5번 다 맞췄으면 
        {
          flag = 0; // 알람 OFF
          cnt = 0; // cnt 초기화 
          digitalWrite(piezo, 0); // 부저 OFF
          lcd.clear(); // lcd 클리어 
          lcd.setCursor(0, 2);
          lcd.print("Alarm OFF"); // 알람 꺼졌다는 내용 출력 
          temp = 0; // 알람 시간 초기화
        }
  }
  int day;
  lcd.setCursor(0,0); //커서를 0,0에 지정 
  
  //1초 단위로 갱신하며 현재시간을 LCD에 출력
  Set_AMPM(rtc.getHours()); 
  lcd.print(":");
  Set_lowThanTen(rtc.getMinutes());
  lcd.print(":");
  Set_lowThanTen(rtc.getSeconds());
  //날짜를 LCD에 출력
  lcd.print("[");
  Set_lowThanTen(rtc.getMonth());
  lcd.print("/");
  Set_lowThanTen(rtc.getDay());
  lcd.print("]");
  //세팅된 알람시간을 LCD에 출력
  lcd.setCursor(0,1);
  lcd.print("Alarm ");
  Set_AMPM(temp/100);
  lcd.print(":");
  Set_lowThanTen(temp%100); 
  
  //1초마다 LCD갱신
  lcdString = "";                      //문자열 초기화
  lcd.print("               ");        //전 글씨 삭제
  delay(1000);
  //알람이 울릴 시간인지 체크
  checkTheAlarmTime(temp/100, temp%100);
   
  //시리얼 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력 
  char theDay[4];
  int i = 0;
  if(Serial.available()) 
  {
    while(Serial.available()) {
      theDay[i] = Serial.read();
      i++;
  }
    day = atoi(theDay);
    if(day/100 >= 12) {
      Serial.print("PM");
      Serial.print((day/100)-12);
    }
    else {
      Serial.print("AM");
      Serial.print(day/100);
    }
    Serial.print(":");
    if(day%100 < 10)
      Serial.print("0");
    Serial.println(day%100);
    temp = checkTheAlarmClock(day);
  }
}
