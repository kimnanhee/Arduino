### SMART FAN

---

온도 센서, 초음파 센서, 서보 모터, DC 모터, 7segment(FND)



선풍기의 역할을 하는 DC모터는 28`C 이상에서 동작합니다.

초음파 센서로 읽어온 거리에 따라서 선풍기의 단계를 제어합니다.
선풍기가 동작할 때, 서보 모터는 0~180도로 반복 회전합니다.

FND에 현재 선풍기의 단계를 표시합니다.

| 거리    | 단계 | DC 모터 | FND  |
| ------- | ---- | ------- | ---- |
| <=50cm  | 0    | STOP    | 0    |
| <=100cm | 1    | 1단계   | 1    |
| 100cm<  | 2    | 2단계   | 2    |

