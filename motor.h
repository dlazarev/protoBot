//
//  motor.h
//  
//
//  Created by Dmitry Lazarev on 02.04.13.
//
//

#ifndef _motor_h
#define _motor_h

#include <Arduino.h>

class MotorDriver {
public:
    MotorDriver(int _forwardPin, int _backPin) : forwardPin(_forwardPin), backPin(_backPin) {}
    
    virtual void setSpeed(int speed) = 0;
    
    virtual void init() {
      pinMode(forwardPin, OUTPUT);
      pinMode(backPin, OUTPUT);
    }
    
protected:
    int forwardPin;
    int backPin;
    int currentSpeed;
};

class Motor : public MotorDriver {
public:
    Motor(int _forwardPin, int _backPin) : MotorDriver(_forwardPin, _backPin) {}
    
    void setSpeed(int speed) {
      int forwardSpeed;
      int backSpeed;  
      
      currentSpeed = constrain(speed, -100, 100);
        
      forwardSpeed = map(currentSpeed, 0, 100, 120, 255);
      backSpeed = map(currentSpeed, -100, 0, 255, 120);
      if (currentSpeed <= 0) forwardSpeed = 0;
      if (currentSpeed >= 0) backSpeed = 0;
      
       analogWrite(backPin, backSpeed);
       analogWrite(forwardPin, forwardSpeed);
    }
};


#endif
