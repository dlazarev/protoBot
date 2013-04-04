#include <Servo.h>
#include <NewPing.h>
#include "direction_sensor.h"
#include "motor.h"
#include "robot.h"

#define SERVO_PIN 10
#define ECHO_PIN 8
#define TRIG_PIN 4

#define MOTOR_LEFT_BACK 5
#define MOTOR_LEFT_FORWARD 6
#define MOTOR_RIGHT_BACK 11
#define MOTOR_RIGHT_FORWARD 3

Robot protoBot(TRIG_PIN, ECHO_PIN, SERVO_PIN,
               MOTOR_LEFT_FORWARD, MOTOR_LEFT_BACK,
               MOTOR_RIGHT_FORWARD, MOTOR_RIGHT_BACK);

void setup()
{
    Serial.begin(115200);
    protoBot.init();
    Serial.println("Robot init completed.");
}

void loop()
{
  protoBot.run();
}

