#include "HuyangBody.h"

//Servo Parameters
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  595 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

#define pwm_body_pin_sideway_left     (byte)    14
#define pwm_body_pin_sideway_right    (byte)    15
#define pwm_body_pin_forward_left     (byte)    12
#define pwm_body_pin_forward_right    (byte)    13
#define pwm_body_pin_rotate           (byte)    11

HuyangBody::HuyangBody(Adafruit_PWMServoDriver pwm) {
	_pwm = pwm;
}

void HuyangBody::rotateServo(uint8_t servo, uint16_t degree) {
	uint16_t pulselength = map(degree, 0, 180, SERVOMIN, SERVOMAX);      //  Calibrate the positive range (see below)
	/*
	Serial.print(F("rotateServoToDegree Servo: "));
	Serial.print(servo);
	Serial.print(F(" to Degree: "));
	Serial.print(degree);
	Serial.print(F(" with Pulselength: "));
	Serial.println(pulselength);
	*/
	_pwm.setPWM(servo, 0, pulselength);
	// Serial.println(F("done"));
}

void HuyangBody::tiltSideways(int16_t degree) {
	rotateServo(pwm_body_pin_sideway_left, _centerTiltSideways + degree);
	rotateServo(pwm_body_pin_sideway_right, _centerTiltSideways + degree);
}
void HuyangBody::tiltForward(int16_t degree){
	rotateServo(pwm_body_pin_forward_left, _centerTiltFront_left + degree);
	rotateServo(pwm_body_pin_forward_right, _centerTiltFront_right - degree);
}
void HuyangBody::rotate(int16_t degree) {
	rotateServo(pwm_body_pin_rotate, _centerRotation + degree);
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
	_currentMillis = millis();

}