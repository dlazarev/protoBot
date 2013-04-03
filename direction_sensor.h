//
//  direction_sensor.h
//  
//
//  Created by Dmitry Lazarev on 02.04.13.
//
//

#ifndef _direct_sensor_h
#define _direct_sensor_h

#include <Arduino.h>

#define MAX_DISTANCE 200

static unsigned int angles[] = {0, 45, 90, 135, 180};

class ServoDriver : public Servo {
public:
    ServoDriver(int _attachPin) : Servo(), attachPin(_attachPin) {}
    
    virtual void init() {
      attach(attachPin);
    }
    
    virtual void setDirection(unsigned int angle) {
        angle = constrain(angle, 15, 175);
        write(angle);
        delay(200);
    }
private:
    int attachPin;
};

class DistanceSensorDriver {
public:
    DistanceSensorDriver(int triggerPin, int echoPin) : sonar(triggerPin, echoPin, MAX_DISTANCE) {}

    virtual unsigned int getDistance() {
        int distance = sonar.ping_cm();
        if (distance < 0) return MAX_DISTANCE;
        return distance;
    }
private:
    NewPing sonar;
};

class DirectionSensor : public ServoDriver, DistanceSensorDriver {
public:
    DirectionSensor(int triggerPin, int echoPin, int servoPin) : ServoDriver(servoPin), DistanceSensorDriver(triggerPin, echoPin), currentIndex(0) {
 //       angles[0] = 0; angles[1] = 45; angles[2] = 90; angles[3] = 135; angles[4] = 180;
        
 //       setDirection(angles[currentIndex]);
 //       Serial.println("DirectionSensor init completed.");
    }
    
    virtual unsigned int getDirection() {
        int delta = currentIndex > 0 ? -1 : 1;
        unsigned int currentDistance, maxDistance = 0;
        unsigned int direction = -1;
        
        currentIndex = currentIndex > 4 ? 4 : currentIndex;
        currentIndex = currentIndex < 0 ? 0 : currentIndex;
        
        for (; currentIndex < 5 && currentIndex >= 0; currentIndex += delta) {
            setDirection(angles[currentIndex]);
            currentDistance = getDistance();
            if (currentDistance > maxDistance) {
                maxDistance = currentDistance;
                direction = angles[currentIndex];
            }
        }
        return direction;
    }
private:
//    unsigned int angles[5];
    int currentIndex;
};

#endif
