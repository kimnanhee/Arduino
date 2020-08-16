// signal 입력 처리

void signal_1() // 시그널 1번
{
  Serial.println("signal 1 start");
  for (int i = 0; command[1][i]; i++)
  {
    if (command[1][i] == 'S') digitalWrite(SW, value[1][i]);
    else if (command[1][i] == 'B') digitalWrite(BUZZER, value[1][i]);
    else if (command[1][i] == 'D') delay(value[1][i]);
  }
  delay(1000);
}
void signal_2() // 시그널 2번
{
  Serial.println("signal 2 start");
  for (int i = 0; command[2][i]; i++)
  {
    if (command[2][i] == 'S') digitalWrite(SW, value[2][i]);
    else if (command[2][i] == 'B') digitalWrite(BUZZER, value[2][i]);
    else if (command[2][i] == 'D') delay(value[2][i]);
  }
  delay(1000);
}
