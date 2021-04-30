/*
시리얼 모니터로 읽어온 값에 따라서,
10번 핀에 연결된 LED제어하기
*/
void setup() 
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() 
{
  if(Serial.available())
  {
    char data = Serial.read();
    if(data == '1') digitalWrite(10, HIGH);
    else if(data == '0') digitalWrite(10, LOW);
  }
}
