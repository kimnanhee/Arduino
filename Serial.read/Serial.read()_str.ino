String str;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    char data = Serial.read();
    
    if(data == '\n') 
    // 개행 문자가 입력이 되면 문자열을 출력하고, 문자열 초기화
    {
      Serial.println(str);
      str = "";
    }
    else str += data; // 문자열 더하기
  }
} 
