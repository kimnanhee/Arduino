void setup() 
{
  pinMode(7, INPUT); // SW
  pinMode(8, OUTPUT); // SW_led
  pinMode(9, OUTPUT); // pwm led
  pinMode(13, OUTPUT); // 내부 LED
}

void loop() 
{
  int pin = digitalRead(7); // 스위치 입력 받기
  if(pin == HIGH) {
    digitalWrite(8, HIGH); // 스위치가 눌리면 LED 점등
    delay(50);
  }
  else digitalWrite(8, LOW);
  
  int value = analogRead(A0); // 아날로그 입력 받기
  
  int a_value = map(value, 0, 1023, 0, 255); // PWM 밝기 조절
  analogWrite(9, a_value);
  
  if(value > 255) digitalWrite(13, HIGH); // 255 초과면 내부 LED 점등
  else digitalWrite(13, LOW);
  
  
}
