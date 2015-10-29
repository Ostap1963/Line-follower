#define lineLeft 2
#define lineRight 4
#define left1 5
#define left2 9
#define right1 3
#define right2 6

#define SPEED 5*254/8

void setup() {
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
}

void loop() {
  bool isLineLeft  = readLineDetector(lineLeft );
  bool isLineRight = readLineDetector(lineRight);

  if (isLineLeft && isLineRight)
    reverse();
  else if (isLineLeft)
    left();
  else if (isLineRight)
    right();
  else
    forward();
}

void forward()
{
  analogWrite(left2, LOW);
  analogWrite(left1, SPEED);

  analogWrite(right2, LOW);
  analogWrite(right1, SPEED);
}

void turnBackward()
{
  left();
  delay(50);
  while(!readLineDetector(lineLeft)) delay(10);
  stop();
}

void reverse()
{
  analogWrite(left1, LOW);
  analogWrite(left2, SPEED);

  analogWrite(right1, LOW);
  analogWrite(right2, SPEED);
}

void left()
{
  analogWrite(left2, LOW);
  analogWrite(left1, LOW);

  analogWrite(right2, LOW);
  analogWrite(right1, SPEED);
}

void right()
{
  analogWrite(left2, LOW);
  analogWrite(left1, SPEED);

  analogWrite(right1, LOW);
  analogWrite(right2, LOW);  
}

void stop()
{
  analogWrite(left2, LOW);
  analogWrite(left1, LOW);

  analogWrite(right1, LOW);
  analogWrite(right2, LOW); 
}

bool readLineDetector(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  pinMode(pin, INPUT);
  long time = micros();
  while(digitalRead(pin) == HIGH && micros() - time < 3000);
  int diff = micros() - time;
  return !(diff >= 3000);
}
