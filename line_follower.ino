#define PWMA 3
#define AIN1 10
#define AIN2 11

#define PWMB 6
#define BIN1 8
#define BIN2 7

#define STBY 9

#define S1 A1
#define S2 A2
#define S4 A4
#define S5 A5

int lowSpeed = 50;
int baseSpeed = 90;
int turnSpeed = 140;
int maxTurnSpeed = 255;

void setup()
{
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}

void loop()
{
  int s1 = !digitalRead(S1);
  int s2 = !digitalRead(S2);
  int s4 = !digitalRead(S4);
  int s5 = !digitalRead(S5);

  if (!s1 && !s2 && !s4 && !s5)
  {
    setMotor(baseSpeed, baseSpeed); 
    return;
  }

  if (s1 && s2 && s4 && s5)
  {
    return;
  }


  if (s1)
  {
    setMotor(-maxTurnSpeed, maxTurnSpeed);
    return;
  }

  if (s2)
  {
    setMotor(-turnSpeed, turnSpeed);
    return;
  }

  if (s5)
  {
    setMotor(maxTurnSpeed, -maxTurnSpeed);
    return;
  }

  if (s4)
  {
    setMotor(turnSpeed, -turnSpeed);
    return;
  }
  delay(10);

}


void setMotor(int left, int right)
{
  if (left >= 0)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  else
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    left = -left;
  }

  if (right >= 0)
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    right = -right;
  }

  analogWrite(PWMA, left);
  analogWrite(PWMB, right);
}