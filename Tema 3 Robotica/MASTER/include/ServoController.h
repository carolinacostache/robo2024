#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Servo.h>

class ServoController {
public:
    ServoController(int servoPin);
    void setPosition(int angle);
    void resetPosition();

private:
    Servo servo;
    int servoPin;
};

#endif
