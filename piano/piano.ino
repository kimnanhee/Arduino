int freq[7] = {262, 294, 330, 349, 392, 440, 494}; // 도, 레, 미, 파, 솔, 라, 시
int sw[7] = {2, 3, 4, 5, 6, 7, 8}; // 도, 레, 미, 파, 솔, 라, 시
int record[3] = {10, 11, 12}; // 시작, 정지, 재생
int buzzer = 9;

bool record_state = false;
unsigned int start_time = 0;

unsigned int remember[2][200] = {};
int cnt = 0;

void setup()
{
  pinMode(buzzer, OUTPUT);

  for (int i = 0; i < 8; i++)
    pinMode(sw[i], INPUT_PULLUP); // 건반 버튼 입력받기
  for (int i = 0; i < 3; i++)
    pinMode(record[i], INPUT_PULLUP); // 녹음 시작/정지 버튼 입력받기

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(record[0]) == HIGH) // 녹음 시작 버튼
  {
    while (digitalRead(record[0]));
    if (record_state == false)
    {
      memset(remember, 0, sizeof(remember)); // remember 2차원 배열 초기화
      cnt = 0;

      record_state = true;
      digitalWrite(13, HIGH);

      start_time = millis() / 10; // 녹음 시작 버튼이 눌린 시간 기록

      Serial.println("record start");
      Serial.println(start_time);
    }
  }
  else if (digitalRead(record[1]) == HIGH) // 녹음 정지 버튼
  {
    while (digitalRead(record[1]));
    record_state = false;
    digitalWrite(13, LOW);

    remember[0][cnt] = 0;
    remember[1][cnt] = millis() / 10 - start_time; // 녹음 정지 버튼이 눌린 시간 기록

    Serial.println("record stop");
  }
  else if (digitalRead(record[2]) == HIGH)
  {
    while (digitalRead(record[2]));
    Serial.print("music start  cnt : ");
    Serial.println(cnt);

    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < cnt; j++)
      {
        Serial.print(remember[i][j]);
        Serial.print(" ");
      }
      Serial.println("");
    }

    for (int i = 0; i < cnt; i += 2)
    {
      Serial.print(remember[0][i]);
      Serial.print(" - ");
      Serial.print((remember[1][i + 1] - remember[1][i]) * 10);
      Serial.println("(10ms)");
      tone(buzzer, freq[remember[0][i]], (remember[1][i + 1] - remember[1][i]) * 0);

      Serial.print("delay - ");
      Serial.print((remember[1][i + 2] - remember[1][i + 1]) * 10);
      Serial.println("(10ms)");
      delay((remember[1][i + 2] - remember[1][i + 1]) * 10);
    }
    noTone(buzzer);

    Serial.println("music end");
  }

  for (int i = 0; i < 7; i++)
  {
    if (digitalRead(sw[i]) == HIGH)
    {
      if (record_state) // 녹음 중일 때만
      {
        remember[0][cnt] = i; // 눌린 건반 버튼 기록
        remember[1][cnt] = millis() / 10 - start_time; // 건반 버튼이 눌린 시간 기록

        while (digitalRead(sw[i])) tone(buzzer, freq[sw[i]]);
        noTone(buzzer);

        remember[0][cnt + 1] = i;
        remember[1][cnt + 1] = millis() / 10 - start_time; // 건반 버튼이 떼진 시간 기록
        cnt += 2;

        Serial.print(i);
        Serial.print(" - ");
        Serial.println(cnt);
      }
      else
      {
        while (digitalRead(sw[i])) tone(buzzer, freq[sw[i]]);
        noTone(buzzer);
      }
    }
  }
}
