int R_led = 9, G_led = 10, B_led = 11;
int set_button = 5, cancel_button = 6;
int poten = A0;

int state = -1; // -1:cancle, 0:r, 1:g, 2:b
int value[3]; // RGB LED에 출력할 값을 저장

void setup() {
  pinMode(set_button, INPUT_PULLUP); // 버튼 입력 핀 설정
  pinMode(cancel_button, INPUT_PULLUP);
  pinMode(R_led, OUTPUT); // RGB LED 출력 핀 설정
  pinMode(G_led, OUTPUT);
  pinMode(B_led, OUTPUT);
  Serial.begin(9600); // 시리얼 통신 속도 설정
}

void loop() {
  int set_value = digitalRead(set_button); // 버튼의 상태 값 읽어오기
  int cancle_value = digitalRead(cancel_button);
  
  if(set_value == LOW) { // 설정 버튼이 눌렸을 때
    state += 1;
    state %= 3;
    delay(500);
  }
  if(cancle_value == LOW) { // 섵정 취소 버튼이 눌렸을 때
    state = -1;
    value[0] = value[1] = value[2] = 0;
    delay(500);
  }
  int poten_value = analogRead(A0); // 아날로그 입력받기
  poten_value = map(poten_value, 0, 1023, 0, 255); // 값의 범위를 바꾸기
  
  if(state == 0) value[0] = poten_value;
  else if(state == 1) value[1] = poten_value;
  else if(state == 2) value[2] = poten_value;

  Serial.print("RED: "); // 시리얼 모니터에 출력하기
  Serial.print(value[0]);
  Serial.print(" GREEN: ");
  Serial.print(value[1]);
  Serial.print(" BLUE: ");
  Serial.println(value[2]);
  
  analogWrite(R_led, value[0]); // RGB LED 출력하기
  analogWrite(G_led, value[1]);
  analogWrite(B_led, value[2]);
  delay(100);
}
