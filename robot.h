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

#define R1  97600L   // measure the value of the Resitors to be exact as possible
#define R2  99300L    // add an L for Long values

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
    }
    
    float battery() {
      int raw = analogRead(A0);
      float val = 5.0 * raw/1024.0;  // convert to voltage halfway
      return val * (R1 + R2)/R2;       //calculate the  battery voltage;  if you don;t need to be exact just:  return val * 2; 
  }

  unsigned int review() {
        unsigned int dir = sonar.getDirection();
        return dir;
    }
    
    void run() {
      checkBattery();  

      int dir = review();
      
      switch(dir) {
        case 0:
          turnLeft90();
          break;
        case 45:
          turnLeft45();
          break;
        case 90:
          break;
        case 135:
          turnRight45();
          break;
        case 180:
          turnRight90();  
      }
      leftMotor.setSpeed(50);
      rightMotor.setSpeed(50);
      delay(600);
    }
    
    void stop() {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
    }
    
    void turnLeft90() {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      delay(20);
      leftMotor.setSpeed(-70);
      rightMotor.setSpeed(70);
      delay(340);
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
    }
      
    void turnLeft45() {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      delay(20);
      leftMotor.setSpeed(-70);
      rightMotor.setSpeed(70);
      delay(180);
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
    }
      
    void turnRight45() {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      delay(20);
      leftMotor.setSpeed(70);
      rightMotor.setSpeed(-70);
      delay(180);
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
    }

    void turnRight90() {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      delay(20);
      leftMotor.setSpeed(70);
      rightMotor.setSpeed(-70);
      delay(340);
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
    }
      
      
private:
    void checkBattery() {
      if (battery() < 6.0) digitalWrite(13, HIGH);
      else digitalWrite(13, LOW);
    }
    
    DirectionSensor sonar;
    Motor leftMotor;
    Motor rightMotor;
};
#endif
