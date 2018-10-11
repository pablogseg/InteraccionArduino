#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;


int16_t ax, ay, az;
int16_t gx, gy, gz;
float dt;
long tiempo_prev;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;


#define LED_PIN 13
bool blinkState = false;


int16_t count = 1000;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(9600);
    accelgyro.initialize();

    pinMode(LED_PIN, OUTPUT);

}
 
 void loop() {

    accelgyro.getAcceleration(&ax, &ay, &az);

    accelgyro.getRotation(&gx, &gy, &gz);

    dt = (millis()-tiempo_prev)/1000.0;
    tiempo_prev=millis();
     

    float accel_ang_x=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);
    float accel_ang_y=atan(-ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);

    ang_x = 0.3*(ang_x_prev+(gx/131)*dt) + 0.7*accel_ang_x;
    ang_y = 0.3*(ang_y_prev+(gy/131)*dt) + 0.7*accel_ang_y;
  
  
    ang_x_prev=ang_x;
    ang_y_prev=ang_y;


    Serial.print(ang_x); Serial.print("\t");
    Serial.println(ang_y);
    delay(100);

 }
