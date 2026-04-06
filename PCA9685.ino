#include <Wire.h>

#define PCA9685_ADDR 0x60   // Default for Adafruit Motor Shield V2

// PCA9685 registers
#define MODE1   0x00
#define MODE2   0x01

// Writes a byte to PCA9685
void write8(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(PCA9685_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void setupPCA9685() {
  Wire.begin();
  write8(MODE1, 0x20); // MODE1: auto-increment enabled
  write8(MODE2, 0x04); // MODE2: totem-pole outputs
}

// Set PWM on a channel (0–4095)
void setPWM(uint8_t channel, uint16_t on, uint16_t off) {
  Wire.beginTransmission(PCA9685_ADDR);
  Wire.write(0x06 + 4 * channel); // LEDn_ON_L
  Wire.write(on & 0xFF);
  Wire.write(on >> 8);
  Wire.write(off & 0xFF);
  Wire.write(off >> 8);
  Wire.endTransmission();
}

// Motor control wrapper: abstracts PCA9685 channel mapping and direction logic
// dir  : true = clockwise (CW), false = counter-clockwise (CCW)
void Motor(uint8_t motor, bool dir, uint16_t pwm) { 
  if (pwm > 4095) pwm = 4095;
  switch(motor){
    case 1:
    if (dir) {setPWM(10,0,4095);setPWM(9,0,0);setPWM(8,0,pwm);}
    else {setPWM(10,0,0);setPWM(9,0,4095);setPWM(8,0,pwm);}
    break;

    case 2:
    if (dir) {setPWM(11,0,4095);setPWM(12,0,0);setPWM(13,0,pwm);}
    else {setPWM(11,0,0);setPWM(12,0,4095);setPWM(13,0,pwm);}
    break;

    case 3:
    if (dir) {setPWM(4,0,4095);setPWM(3,0,0);setPWM(2,0,pwm);}
    else {setPWM(4,0,0);setPWM(3,0,4095);setPWM(2,0,pwm);}
    break;
    
    case 4:
    if (dir) {setPWM(5,0,4095);setPWM(6,0,0);setPWM(7,0,pwm);}
    else {setPWM(5,0,0);setPWM(6,0,4095);setPWM(7,0,pwm);}
    break;

    default:
    break;
  }
}

void Move(bool dir, uint16_t pwm){
  Motor(3,dir,pwm);
  Motor(4,dir,pwm);
}

void Stop(){
  Motor(3,1,0);
  Motor(4,1,0);
}
void Brake(){
  setPWM(4,0,0);setPWM(3,0,0);setPWM(2,0,4095);
  setPWM(5,0,0);setPWM(6,0,0);setPWM(7,0,4095);
}
void setup() {
  setupPCA9685();
}

void loop() {
  Move(1,4095);
  delay(1000);
  Stop();
  Motor(3,0,4095);
  Motor(4,1,4095);
  delay(83);
  Stop();
  Move(1,4095);
  delay(1000);
  Stop();
  Motor(3,1,4095);
  Motor(4,0,4095);
  delay(167);
  Stop();
  Move(1,4095);
  delay(1000);
  Stop();
  Motor(3,0,4095);
  Motor(4,1,4095);
  delay(83);
  Stop();
  Move(1,4095);
  delay(1000);

}