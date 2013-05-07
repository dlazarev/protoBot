//
//  led_3color.h
//  
//
//  Created by Dmitry Lazarev on 06.05.13.
//
//

#ifndef _led_3color_h
#define _led_3color_h
#include <Arduino.h>

#define LED_3COLOR_BLUE 7
#define LED_3COLOR_RED 9
#define LED_3COLOR_GREEN 12

class Led_3color {
public:
    Led_3color()
    {
        blue_pin = LED_3COLOR_BLUE;
        green_pin = LED_3COLOR_GREEN;
        red_pin = LED_3COLOR_RED;
        
        pinMode(blue_pin, OUTPUT);
        pinMode(green_pin, OUTPUT);
        pinMode(red_pin, OUTPUT);
    }
    
    void red() {
        digitalWrite(red_pin, 255);
        digitalWrite(green_pin, 0);
        digitalWrite(blue_pin, 0);
    }

    void green() {
        digitalWrite(red_pin, 0);
        digitalWrite(green_pin, 255);
        digitalWrite(blue_pin, 0);
    }

    void blue() {
        digitalWrite(red_pin, 0);
        digitalWrite(green_pin, 0);
        digitalWrite(blue_pin, 255);
    }

    void purple() {
        digitalWrite(red_pin, 255);
        digitalWrite(green_pin, 0);
        digitalWrite(blue_pin, 255);
    }
    
    void off() {
        digitalWrite(red_pin, 0);
        digitalWrite(green_pin, 0);
        digitalWrite(blue_pin, 0);
    }
    
private:
    int blue_pin, green_pin, red_pin;
};

#endif
