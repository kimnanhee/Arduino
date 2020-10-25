/*
위로 한번 올라갔다 내려오는 동작 측정하기
위로 올라가면 z값이 작아지고, 내려올 경우 z값이 커진다.
*/

#include <Wire.h>
#define I2C_Add 0x53
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define X_Axis 0x32
#define Y_Axis 0x34
#define Z_Axis 0x36
#define RANGE_2g 0
#define RANGE_4g 1
#define RANGE_8g 2
#define RANGE_16g 3

int basic_z = 0; // 기본 위치 설정
int cnt = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Init_ADXL345(RANGE_2g);
  Init_basic();
}

void loop()
{
  Serial.print("basic Z : ");
  Serial.print(basic_z);
  Serial.print(" X: ");
  Serial.print(Read_Axis(X_Axis));
  Serial.print(" Y: ");
  Serial.print(Read_Axis(Y_Axis));
  Serial.print(" Z: ");
  int z_value = Read_Axis(Z_Axis);
  Serial.println(z_value);
  delay(100);
  
  if (z_value < basic_z - 50) cnt++;
  else cnt = 0;

  if(cnt > 5) 
  {
    while(basic_z - 5 <= Read_Axis(Z_Axis) && Read_Axis(Z_Axis) <= basic_z + 5);
    cnt = 0;
    Serial.println("6050 1 cycle");
  }
}

int Read_Axis(byte axis)
{
  int Data;

  Wire.beginTransmission(I2C_Add);
  Wire.write(axis);
  Wire.endTransmission();

  Wire.beginTransmission(I2C_Add);
  Wire.requestFrom(I2C_Add, 2);

  /* If data is available then read it (2 bytes) */
  if (Wire.available())
  {
    Data = (int)Wire.read();
    Data = Data  | (Wire.read() << 8);
  }
  else
  {
    Data = 0;
  }

  Wire.endTransmission();
  return Data;
}


void Init_ADXL345(byte range)
{
  Wire.beginTransmission(I2C_Add);

  /* Set the sensitivity of the module */
  Wire.write(DATA_FORMAT);
  Wire.write(range);
  Wire.endTransmission();

  /* Put the module into measurement mode to start taking measurements */
  Wire.beginTransmission(I2C_Add);
  Wire.write(POWER_CTL);
  Wire.write(0x08);

  Wire.endTransmission();
}

void Init_basic()
{
  int i;
  for (i = 0; i < 20; i++)
  {
    int z_value = Read_Axis(Z_Axis);
    basic_z += z_value;
    delay(50);
  }
  basic_z = (basic_z / 20);
}
