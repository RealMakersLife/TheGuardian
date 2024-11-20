#include <Servo.h>

#define stepPinX 2
#define dirPinX 5
#define stepPinY 3
#define dirPinY 6
#define enablePin 8

#define joyLeft 10
#define joyRight 11
#define joyUp 12
#define joyDown 13

#define potPin A0
#define buttonPin 4
#define servoPin 7

Servo myServo;

void setup() {
  // Set the pins as outputs for X and Y axes
  pinMode(stepPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Set joystick pins as inputs
  pinMode(joyLeft, INPUT_PULLUP);
  pinMode(joyRight, INPUT_PULLUP);
  pinMode(joyUp, INPUT_PULLUP);
  pinMode(joyDown, INPUT_PULLUP);

  // Set button pin as input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach the servo to the specified pin
  myServo.attach(servoPin);
  myServo.write(0);  // Initialize the servo position to 0 degrees

  // Enable the drivers
  digitalWrite(enablePin, LOW);
}

void loop() {
  // Read the potentiometer value
  int potValue = analogRead(potPin);
  
  // Map the potentiometer value to a delay value
  int speedDelay = map(potValue, 0, 1023, 1000, 100); // Adjust the range for faster speed and less noise

  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {  // Button is pressed
    myServo.write(90); // Move servo to 90 degrees
  } else {
    myServo.write(0);  // Move servo back to 0 degrees
  }

  // Control X-axis
  if (!digitalRead(joyLeft)) {
    digitalWrite(dirPinX, LOW);  // Counterclockwise
    stepMotor(stepPinX, speedDelay);
  } else if (!digitalRead(joyRight)) {
    digitalWrite(dirPinX, HIGH);  // Clockwise
    stepMotor(stepPinX, speedDelay);
  }

  // Control Y-axis
  if (!digitalRead(joyUp)) {
    digitalWrite(dirPinY, HIGH);  // Up
    stepMotor(stepPinY, speedDelay);
  } else if (!digitalRead(joyDown)) {
    digitalWrite(dirPinY, LOW);  // Down
    stepMotor(stepPinY, speedDelay);
  }

  delay(1);  // Short delay for smoother movement
}

void stepMotor(int stepPin, int delayTime) {
  // Step the motor with a constant speed
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(delayTime / 4);  // Reduced delay for faster speed
  digitalWrite(stepPin, LOW);
  delayMicroseconds(delayTime / 4);  // Reduced delay for faster speed
}
