// servo_bt.ino
// Receives 1/2 over HC-05 Bluetooth and moves servo
// 1 = fork  → clockwise to 180°, holds, returns to 90°
// 2 = spoon → anticlockwise to 0°, holds, returns to 90°
// 3 = center → return to 90° (manual override)

#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);  // RX=10, TX=11
Servo myServo;

const int SERVO_PIN  = 9;
const int HOLD_MS    = 2000;  // ← change this to adjust hold time
const int SWEEP_MS   = 5;     // ← change this to adjust sweep speed (lower = faster)

int currentPos = 90;

void sweepTo(int target) {
  if (currentPos < target) {
    for (int pos = currentPos; pos <= target; pos++) {
      myServo.write(pos);
      delay(SWEEP_MS);
    }
  } else {
    for (int pos = currentPos; pos >= target; pos--) {
      myServo.write(pos);
      delay(SWEEP_MS);
    }
  }
  currentPos = target;
}

void setup() {
  BT.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(90);
  delay(500);
}

void loop() {
  if (BT.available() > 0) {
    char input = BT.read();

    if (input == '1') {
      sweepTo(180);
      delay(HOLD_MS);
      sweepTo(90);

    } else if (input == '2') {
      sweepTo(0);
      delay(HOLD_MS);
      sweepTo(90);

    } else if (input == '3') {
      sweepTo(90);
    }
  }
}
