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
        endTime = millis() + RUN_TIME * 1000;
        sonar.init();
        leftMotor.init();
        rightMotor.init();
        pinMode(13, OUTPUT);
        move();
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
        
    void stop() {
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(0);
        state = stateStopped;
    }
    
    void pause() {
        colorLed.off();
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(0);
        state = statePaused;
    }
    void move() {
        colorLed.blue();
        leftMotor.setSpeed(85);
      rightMotor.setSpeed(70);
      state = stateMoving;
    }
    
    bool obstacleAhead(unsigned int distance)
    {
        return (distance <= TOO_CLOSE);
    }
    
    void turnLeft(unsigned long currentTime, unsigned long delta) {
        colorLed.green();
        leftMotor.setSpeed(-200);
        rightMotor.setSpeed(-50);
        endStateTime = currentTime + delta;
        state = stateTurning;
    }
    
    void turnRight(unsigned long currentTime, unsigned long delta) {
        colorLed.red();
        leftMotor.setSpeed(-50);
        rightMotor.setSpeed(-200);
        endStateTime = currentTime + delta;
        state = stateTurning;
    }
    
    bool doneTurning(unsigned long currentTime, unsigned int distance)
    {
        if (currentTime >= endStateTime)
            return (distance > TOO_CLOSE);
        return false;
    }
    
    void run() {
        Serial.print("state=");
        Serial.println(state);
        checkBattery();
        
        if (stopped())
            return;
        
        unsigned long currentTime = millis();
        int distance = sonar.getDistance();
        Serial.print("distance=");
        Serial.println(distance);
        if (doneRunning(currentTime))
            stop();
        else if (moving()) {
            if (obstacleAhead(distance)) {
                pause();
                int direction = sonar.getDirection() - 90;
                Serial.print("direction=");
                Serial.println(direction);
                if (direction < 0)
                    turnLeft(currentTime, -direction);
                else if (direction > 0)
                    turnRight(currentTime, direction);
            }
        }
        else if (turning()) {
            if (doneTurning(currentTime, distance))
                move();
        }
        else if (paused()) move();
    }
    
private:
    void checkBattery() {
      if (battery() < 6.0) digitalWrite(13, HIGH);
      else digitalWrite(13, LOW);
    }
    
    bool moving() { return (state == stateMoving); }
    bool turning() { return (state == stateTurning); }
    bool stopped() { return (state == stateStopped); }
    bool paused() { return (state == statePaused); }
    
    bool doneRunning(unsigned long currentTime) { return (currentTime >= endTime); }
    
    DirectionSensor sonar;
    Motor leftMotor;
    Motor rightMotor;
    Led_3color colorLed;
    unsigned long endTime;
    unsigned long endStateTime;
    enum state_t { stateStopped, stateMoving, stateTurning, statePaused };
    state_t state;
};
#endif
