// 들어온 코드를 공백을 기준으로 파싱해서 배열에 저장하는 함수

void code_set() 
{
  Serial.println("code setting");

  memset(command, 0, sizeof(command)); // 배열 초기화
  memset(value, 0, sizeof(value));
  str = "";

  int i, cnt; // 몇 번째 명령인지 저장
  int kind; // 어느 종류의 명령인지 저장 (loop, sig1, sig2, time)

  for (i = 0; i < blue_str.length(); i++)
  {
    if (blue_str[i] == ' ') // 단어 끝
    {
      if (str == "loop") kind = 0, cnt = 0;
      else if (str == "sig1") kind = 1, cnt = 0;
      else if (str == "sig2") kind = 2, cnt = 0;
      else if (str == "time") kind = 3, cnt = 0;

      else if (str == "son") command[kind][cnt] = 'S', value[kind][cnt] = 1, cnt++;
      else if (str == "soff") command[kind][cnt] = 'S', value[kind][cnt] = 0, cnt++;
      else if (str == "bon") command[kind][cnt] = 'B', value[kind][cnt] = 1, cnt++;
      else if (str == "boff") command[kind][cnt] = 'B', value[kind][cnt] = 0, cnt++;
      else if (str == "sleep") 
      {
        i++;
        str = "";
        str += blue_str[i++]; // 숫자 4자리수 저장
        str += blue_str[i++];
        str += blue_str[i++];
        str += blue_str[i++];
        int num = str.toInt(); // 문자열 정수로 변환

        str = "";
        str += blue_str[i++];
        str += blue_str[i++];
        if (str == "ms");
        else if (str == " s") num *= 1000;
        else if (str == " m") num *= 60000;
        else if (str == " h") num *= 3600000;

        command[kind][cnt] = 'D', value[kind][cnt] = num, cnt++;
      }
      str = "";
    }
    else str += blue_str[i]; // 문자열 더하기
    delay(1);
  }
}
