// Adapted from https://docs.arduino.cc/tutorials/nano-33-iot/imu-accelerometer/
// and https://docs.arduino.cc/learn/electronics/servo-motors/

#include <Arduino_LSM6DS3.h>
#include <Servo.h>

Servo myservo_x;  // create servo object to control a servo
Servo myservo_y;

int x_val;
int y_val;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  myservo_x.attach(2);  // attaches the servo on pin 9 to the servo object
  myservo_y.attach(3);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.print('\t');

    x_val = 180 - int((x + 1.0)/2 * 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo_x.write(x_val);

    y_val = int((y + 1.0)/2 * 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo_y.write(y_val);
  }

  // delay(50);
}
