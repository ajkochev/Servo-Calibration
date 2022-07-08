#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Set PCA9685 board address below if needed.  0x40 is the default.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

/*
Below SERVONUM is the address of servo to be calibrated 0 is Port 0 on PCA9685 board
change to 1 for Port 1 and so on.
POS is the starting position of the servo to be calibrated, usually the middle positon 
is near 1000 when using writeMicroseconds in the code.  Change as needed.
*/
int servonum = 0;
int pos = 1000;
// -----------------------------------------------------

String readString;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(25000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  Serial.println("Servo calibration");
  Serial.println("Use this to calibrate your servo to find the range of movement required");
  Serial.println("The servo should start close to the centre of the range");
  Serial.println("Type a value followed by a + to move in one direction or a valu followed by a - to move in the other direction");
  Serial.println("For example 100+ to 200-");  
  Serial.println("To move to a specific location use strings like 900x or 1800x for new servo position");
  Serial.println("Move the servo to find the required range for whatever you're operating.");
  Serial.println("Servos min and max can vary, try the 100 - 1900 range to start with.");
  Serial.println("WARNING: Exceeding the max range could damage the servo.");
  Serial.println();
  pwm.writeMicroseconds(servonum, pos);
  Serial.println("Centre point:");  
  Serial.println(pos);  
  delay(10);
}

void loop()
{
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }
  if (readString.length() > 0) {

    if(readString.indexOf('x') > 0) {
      pos = readString.toInt();
    }

    if(readString.indexOf('+') > 0) {
      pos = pos + readString.toInt();
    }

    if(readString.indexOf('-') > 0) {
      pos = pos - readString.toInt();
    }

    pwm.writeMicroseconds(servonum, pos);
    Serial.println(pos);
    readString = ""; //empty for next input
  }
}
