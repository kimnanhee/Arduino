// command, value 배열에 들어있는 값을 확인하기 위한 함수
// S => 스위치, B => 부저, D => delay
// ON => 1, OFF => 0
// time => 0~무한대 [ms 단위]

void comval()
{
  int i, j;
  Serial.println("\n\ncommand");
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < MAX; j++)
    {
      Serial.print(command[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.println("\n\nvalue");
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < MAX; j++)
    {
      Serial.print(value[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.println();
}
