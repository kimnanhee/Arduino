#define buzzer A1

#define ultra_trig A2
#define ultra_echo A3

#define motorA 2
#define motorB 13

int buttons[3] = {3, 4, 5};

int segments[7] = {6, 7, 8, 9, 10, 11, 12};
int matrix[3][7] = {
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}  // 3
};

int state = 1; // 층수 표시

void setup()
{
  Serial.begin(9600);
  Serial.println("Elevator Start");

  pinMode(buzzer, OUTPUT);

  pinMode(ultra_trig, OUTPUT);
  pinMode(ultra_echo, INPUT);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  for (int i = 0; i < 3; i++)
    pinMode(buttons[i], INPUT);
  for (int i = 0; i < 7; i++)
    pinMode(segments[i], OUTPUT);

  display_segment();
}

void loop()
{
  for (int i = 0; i < 3; i++)
    if (digitalRead(buttons[i]) == HIGH)
    {
      state = i + 1;

      display_segment();
      move_elevator();
    }

  delay(10);
}

// ------------------------------------------------------------

void display_segment()
{
  for (int i = 0; i < 7; i++)
    digitalWrite(segments[i], matrix[state - 1][i]);
}

float ultrasonic()
{
  digitalWrite(ultra_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, LOW);

  long duration = pulseIn(ultra_echo, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void move_elevator()
{
  float min_distance = (state - 1) * 10;
  float max_dixtance = state * 10;

  if (ultrasonic() > max_dixtance)
    while (ultrasonic() > max_dixtance) {
      digitalWrite(motorA, HIGH); // 모터 정회전
      digitalWrite(motorB, LOW);
    }

  else if (ultrasonic() < min_distance)
    while (ultrasonic() < min_distance) {
      digitalWrite(motorA, LOW); // 모터 역회전
      digitalWrite(motorB, HIGH);
    }

  digitalWrite(motorA, LOW); // 모터 정지
  digitalWrite(motorB, LOW);

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}
