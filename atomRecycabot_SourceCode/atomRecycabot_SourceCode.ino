#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <BluetoothSerial.h>

// Ultrasonic
#define trigPin 12
#define echoPin 14

// Right Motor
#define enableRightMotor 32
#define rightMotorPin1 26
#define rightMotorPin2 27

// Left Motor
#define enableLeftMotor 4
#define leftMotorPin1 25
#define leftMotorPin2 33

// Buttons
#define buttonAuto 18
#define buttonManual 13

// LEDs
#define ledAuto 21
#define ledManual 22

bool autoMode = false;
bool manualMode = false;

long duration;
int distance;

void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Buttons
  pinMode(buttonAuto, INPUT_PULLUP);
  pinMode(buttonManual, INPUT_PULLUP);

  // LEDs
  pinMode(ledAuto, OUTPUT);
  pinMode(ledManual, OUTPUT);

  // Bluetooth
  Dabble.begin("SumoBot_Manual");

  Serial.println(" SumoBot Ready! Use buttons to select mode.");
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  digitalWrite(rightMotorPin1, rightMotorSpeed > 0);
  digitalWrite(rightMotorPin2, rightMotorSpeed < 0);
  digitalWrite(leftMotorPin1, leftMotorSpeed > 0);
  digitalWrite(leftMotorPin2, leftMotorSpeed < 0);

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void runAutomaticMode() {
  int dist = getDistance();
  Serial.print("Distance: ");
  Serial.println(dist);

  if (dist <= 62 && dist > 0) {
    rotateMotor(200, 200); // Move forward
  } else {
    rotateMotor(0, 0); // Stop
  }
}

void runManualMode() {
  Dabble.processInput();

  int rightMotorSpeed = 0;
  int leftMotorSpeed = 0;

  if (GamePad.isUpPressed()) {
    rightMotorSpeed = 255;
    leftMotorSpeed = 255;
  } else if (GamePad.isDownPressed()) {
    rightMotorSpeed = -255;
    leftMotorSpeed = -255;
  } else if (GamePad.isLeftPressed()) {
    rightMotorSpeed = 255;
    leftMotorSpeed = -255;
  } else if (GamePad.isRightPressed()) {
    rightMotorSpeed = -255;
    leftMotorSpeed = 255;
  } else {
    rightMotorSpeed = 0;
    leftMotorSpeed = 0;
  }
  
  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}

void loop() {
   Dabble.processInput();
  // Read buttons (LOW = pressed)
  bool buttonAutoState = !digitalRead(buttonAuto);
  bool buttonManualState = !digitalRead(buttonManual);

  // Mode switching
  if (buttonAutoState) {
    autoMode = true;
    manualMode = false;
    digitalWrite(ledAuto, HIGH);
    digitalWrite(ledManual, LOW);
    Serial.println("Auto Mode Activated");
    delay(500);
  } else if (buttonManualState) {
    manualMode = true;
    autoMode = false;
    digitalWrite(ledAuto, LOW);
    digitalWrite(ledManual, HIGH);
    Serial.println("Manual Mode Activated");
    delay(500);
  }

  // Run active mode
  if (autoMode && !manualMode) {
    runAutomaticMode();
  } else if (manualMode && !autoMode) {
    runManualMode();
  } else {
    rotateMotor(0, 0);
  }
}