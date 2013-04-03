//
//  robot.h
//  
//
//  Created by Dmitry Lazarev on 02.04.13.
//
//

#ifndef _robot_h
#define _robot_h

#include <Arduino.h>

class Robot {
public:
    Robot(int _triggerPin, int _echoPin, int _servoPin,
          int _leftForward, int _leftBack, int _rightForward, int _rightBack)
    : sonar(_triggerPin, _echoPin, _servoPin),
    leftMotor(_leftForward, _leftBack),
    rightMotor(_rightForward, _rightBack) {}
    
    void init() {
        sonar.init();
        leftMotor.init();
        rightMotor.init();
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
    }
    
    unsigned int review() {
        unsigned int dir = sonar.getDirection();
        return dir;
    }
    
    void run() {
        leftMotor.setSpeed(-1);
        rightMotor.setSpeed(-1);
    }
private:
    DirectionSensor sonar;
    Motor leftMotor;
    Motor rightMotor;
};
#endif
