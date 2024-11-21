/* everything u need to control the servo motor*/

#include <ServoController.h>

ServoController::ServoController(int servoPin) : servoPin(servoPin) {
    servo.attach(servoPin);
    resetPosition();
}

void ServoController::setPosition(int angle) {
    if (angle >= 0 && angle <= 180) {
        servo.write(angle);
    }
}

void ServoController::resetPosition() {
    servo.write(0);
}
