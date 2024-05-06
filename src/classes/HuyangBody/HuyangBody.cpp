#include "HuyangBody.h"
#include <Adafruit_PWMServoDriver.h>

//Servo Parameters
#define HuyangBody_SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define HuyangBody_SERVOMAX  595 // This is the 'maximum' pulse length count (out of 4096)
#define HuyangBody_SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

#define pwm_pin_sideway_left     (uint8_t)    14
#define pwm_pin_sideway_right    (uint8_t)    15
#define pwm_pin_forward_left     (uint8_t)    12
#define pwm_pin_forward_right    (uint8_t)    13
#define pwm_pin_body_rotate      (uint8_t)    11

HuyangBody::HuyangBody(Adafruit_PWMServoDriver *pwm) {
	_pwm = pwm;
}

void HuyangBody::rotateServo(uint8_t servo, uint16_t degree) {
	uint16_t pulselength = map(degree, 0, 180, HuyangBody_SERVOMIN, HuyangBody_SERVOMAX);      //  Calibrate the positive range (see below)
	/*
	Serial.print("rotateServoToDegree Servo: ");
	Serial.print(servo);
	Serial.print(" to Degree: ");
	Serial.print(degree);
	Serial.print(" with Pulselength: ");
	Serial.println(pulselength);
	*/
	_pwm->setPWM(servo, 0, pulselength);
	// Serial.println("done");
}

void HuyangBody::tiltSideways(uint16_t degree) {
	rotateServo(pwm_pin_sideway_left, _centerTiltSideways + degree);
	rotateServo(pwm_pin_sideway_right, _centerTiltSideways + degree);
}
void HuyangBody::tiltForward(uint16_t degree){
	rotateServo(pwm_pin_forward_left, _centerTiltFront_left + degree);
	rotateServo(pwm_pin_forward_right, _centerTiltFront_right - degree);
}
void HuyangBody::rotate(uint16_t degree) {
	//center = 35
	uint16_t rotateDegree  = map(degree, -100, 100, 0, 70);
	rotateServo(pwm_pin_body_rotate, rotateDegree);
}

void HuyangBody::centerAll() {
	tiltSideways(0);
	tiltForward(0);
	rotate(0);
}

void HuyangBody::setup()
{
	
}

void HuyangBody::loop()
{
	// Serial.println("HuyangBody loop");

	_currentMillis = millis();

}