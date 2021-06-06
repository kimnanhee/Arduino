#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

int led[4] = {8, 9, 10, 11};
int count = 0;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(2400);

  for (int i = 0; i < 4; i++)
    pinMode(led[i], OUTPUT);
}

void loop()
{
  if (mySerial.available())
  {
    char ch = mySerial.read();

    if (ch == '1') count++;
    Serial.println(count);

    if (count % 5 == 1) digitalWrite(led[0], HIGH);
    else if (count % 5 == 2) digitalWrite(led[1], HIGH);
    else if (count % 5 == 3) digitalWrite(led[2], HIGH);
    else if (count % 5 == 4) digitalWrite(led[3], HIGH);
    else if (count % 5 == 0)
    {
      for (int i = 0; i < 4; i++)
        digitalWrite(led[i], LOW);
    }
  }
}
