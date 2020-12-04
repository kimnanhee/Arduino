/*
  AT+RENEW
  AT+RESET
  AT+TYPE0
*/
#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX, TX

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  if(BT.available()) // 블루투스로 들어온 값을 시리얼로 전송
    Serial.write(BT.read());
    
  if(Serial.available()) // 시리얼로 들어온 값을 블루투스로 전송
    BT.write(Serial.read());
}
