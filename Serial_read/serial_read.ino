// 1
// 시리얼 모니터로 읽어온 값을 한줄씩 출력하기
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    char data = Serial.read();
    Serial.println(data);
  }
}
