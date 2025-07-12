
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define TRIGGER_PIN 10
#define ECHO_PIN 11
#define SERVO_PIN 9

Adafruit_BNO055 bno = Adafruit_BNO055();
Servo servo;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bno.begin();
  servo.attach(SERVO_PIN);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  float orientationX = event.orientation.x;
  float orientationY = event.orientation.y;
  float distance = readUltrasonicDistance();

  Serial.print((int)orientationX);
  Serial.print(",");
  Serial.print((int)orientationY);
  Serial.print(",");
  Serial.println((int)distance);

  delay(500);
}

float readUltrasonicDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2.0;
}
