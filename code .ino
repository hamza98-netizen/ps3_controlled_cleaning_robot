#include <Ps3Controller.h>

int motorLeft_PWM1 = 22;
int motorLeft_PWM2 = 19;
int motorRight_PWM1 = 18;
int motorRight_PWM2 = 23;

void notify() {
  int yAxis = Ps3.data.analog.stick.ly;
  int xAxis = Ps3.data.analog.stick.lx;

  yAxis = -yAxis; 

  int leftSpeed = yAxis + xAxis;
  int rightSpeed = yAxis - xAxis;

  if (leftSpeed > 10) {
    analogWrite(motorLeft_PWM1, map(leftSpeed, 0, 127, 0, 255));
    analogWrite(motorLeft_PWM2, 0);
  } else if (leftSpeed < -10) {
    analogWrite(motorLeft_PWM1, 0);
    analogWrite(motorLeft_PWM2, map(abs(leftSpeed), 0, 127, 0, 255));
  } else {
    analogWrite(motorLeft_PWM1, 0);
    analogWrite(motorLeft_PWM2, 0);
  }

  if (rightSpeed > 10) {
    analogWrite(motorRight_PWM1, map(rightSpeed, 0, 127, 0, 255));
    analogWrite(motorRight_PWM2, 0);
  } else if (rightSpeed < -10) {
    analogWrite(motorRight_PWM1, 0);
    analogWrite(motorRight_PWM2, map(abs(rightSpeed), 0, 127, 0, 255));
  } else {
    analogWrite(motorRight_PWM1, 0);
    analogWrite(motorRight_PWM2, 0);
  }
}

void onConnect() {
  Serial.println("Connected.");
}

void setup() {
  Serial.begin(115200);
  pinMode(motorLeft_PWM1, OUTPUT);
  pinMode(motorLeft_PWM2, OUTPUT);
  pinMode(motorRight_PWM1, OUTPUT);
  pinMode(motorRight_PWM2, OUTPUT);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("00:1a:7d:da:71:11");

  Serial.println("Ready.");
}

void loop() {
  if (!Ps3.isConnected()) return;
  delay(10);
}
