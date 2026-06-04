// Motor Pins
const int AIN1 = 4;
const int AIN2 = 3;
const int BIN1 = 6;
const int BIN2 = 7;
const int PWMA = 9;
const int PWMB = 10;

// Sensor Pins
int sensorPins[] = {A0, A1, A2, A3, A4};
int sensorValues[5];

// PID Constants
float Kp = 25.0;  // Adjust these starting values
float Ki = 0.0;
float Kd = 12.0;

int lastError = 0;
float integral = 0;

// Speed Settings
int baseSpeed = 180; // Base speed (0-255)
int maxSpeed = 250;  // Maximum limit

void setup() {
  Serial.begin(115200);
  
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.println("System Initialized. Starting in 2 seconds...");
  delay(2000);
}

void loop() {
  int position = readSensors();
  int error = position - 2000; // 2000 is the center for 5 sensors

  // PID Calculation
  float P = error;
  integral += error;
  float D = error - lastError;
  float motorSpeed = (Kp * P) + (Ki * integral) + (Kd * D);
  
  lastError = error;

  int leftMotorSpeed = baseSpeed + motorSpeed;
  int rightMotorSpeed = baseSpeed - motorSpeed;

  // Constrain speeds to PWM limits
  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  driveMotors(leftMotorSpeed, rightMotorSpeed);

  // Serial Monitor Output
  Serial.print("S:"); 
  for(int i=0; i<5; i++) Serial.print(sensorValues[i] > 500 ? "1" : "0");
  Serial.print(" | Err: "); Serial.print(error);
  Serial.print(" | L: "); Serial.print(leftMotorSpeed);
  Serial.print(" | R: "); Serial.println(rightMotorSpeed);
}

int readSensors() {
  long avg = 0;
  int sum = 0;
  bool onLine = false;

  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    // Assuming dark line (high value) on light surface
    if (sensorValues[i] > 500) onLine = true;
    
    avg += (long)sensorValues[i] * (i * 1000);
    sum += sensorValues[i];
  }

  if (!onLine) {
    // If no line is detected, use the last known error to stay on course
    return (lastError > 0) ? 4000 : 0;
  }

  return avg / sum;
}

void driveMotors(int left, int right) {
  // Motor A
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, left);

  // Motor B
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, right);
}