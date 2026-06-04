// ===== MOTOR PINS =====
#define AIN1 4
#define AIN2 3
#define BIN1 6
#define BIN2 7
#define PWMA 9
#define PWMB 10
#define STBY 5

void setup()
{
  Serial.begin(9600);

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(STBY,OUTPUT);

  digitalWrite(STBY,HIGH);   // Enable motor driver

  Serial.println("Motor Driver Test Starting...");
}

void loop()
{

  // ===== LEFT MOTOR FORWARD =====
  Serial.println("Left Motor Forward");
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  analogWrite(PWMA,180);
  delay(2000);

  stopMotors();
  delay(1000);


  // ===== LEFT MOTOR REVERSE =====
  Serial.println("Left Motor Reverse");
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  analogWrite(PWMA,180);
  delay(2000);

  stopMotors();
  delay(1000);


  // ===== RIGHT MOTOR FORWARD =====
  Serial.println("Right Motor Forward");
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMB,180);
  delay(2000);

  stopMotors();
  delay(1000);


  // ===== RIGHT MOTOR REVERSE =====
  Serial.println("Right Motor Reverse");
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  analogWrite(PWMB,180);
  delay(2000);

  stopMotors();
  delay(2000);


  // ===== BOTH MOTORS FORWARD =====
  Serial.println("Both Motors Forward");
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  analogWrite(PWMA,200);
  analogWrite(PWMB,200);
  delay(3000);

  stopMotors();
  delay(3000);

}


void stopMotors()
{
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}