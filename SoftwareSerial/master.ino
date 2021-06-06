#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(2400);
}

void loop()
{
  Serial.write('1');
  mySerial.write('1');
  delay(1000);
}
