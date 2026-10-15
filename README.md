# MotorShieldV2

Bare-metal PCA9685/TB6612 driver for the Adafruit Motor Shield V2. One sketch, `PCA9685.ino`, using only the Arduino `Wire` library.

## Purpose

Adafruit's [Motor Shield V2 library](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library) is full-featured (DC, stepper and servo, plus layered classes), and that costs flash, RAM and complexity. This sketch is the opposite: **ultra-lightweight, minimal footprint**, for projects that only need to spin DC motors.

- **No library dependencies** other than `Wire`.
- **Direct register access.** The PCA9685 is configured with two register writes, and each channel is one I²C burst.
- **Tiny code.** The whole sketch is under 100 lines, so you can read and modify it in a minute.
- **Good fit for:** small robots and other boards with little flash or RAM, or anyone who wants to see exactly what goes over I²C.

It does not drive steppers or servos, or set the PWM frequency (the PCA9685 runs at its default). For those, use Adafruit's library.

## How it works

The shield has a PCA9685 (16-channel, 12-bit PWM) driving two TB6612 dual H-bridges. Each motor uses three PCA9685 channels: one PWM for speed and two inputs (IN1, IN2) for direction.

| Motor | PWM | IN1 | IN2 |
|---|---|---|---|
| M1 | 8 | 10 | 9 |
| M2 | 13 | 11 | 12 |
| M3 | 2 | 4 | 3 |
| M4 | 7 | 5 | 6 |

## API

The whole API is five functions.

| Function | What it does |
|---|---|
| `setupPCA9685()` | Starts I²C, enables register auto-increment and totem-pole outputs. Call once in `setup()`. |
| `setPWM(channel, on, off)` | Raw write to one PCA9685 channel (0–15). `on` and `off` are 12-bit tick counts (0–4095). |
| `Motor(motor, dir, pwm)` | Run one motor. `motor` is 1–4, `dir` is `true` for clockwise or `false` for counter-clockwise, `pwm` is speed from 0 (stopped) to 4095 (full). |
| `Move(dir, pwm)` | Drive motors 3 and 4 together in the same direction, such as the two wheels of a robot. |
| `Stop()` | Set motors 3 and 4 to zero speed (PWM 0, direction inputs unchanged, which the TB6612 treats as a short brake). |
| `Brake()` | Set motors 3 and 4 inputs IN1 = IN2 = low with PWM high, which the TB6612 treats as output off (the motor freewheels). |

`write8(reg, val)` is the internal one-byte register write.

## Example

```cpp
void setup() {
  setupPCA9685();            // start the shield
}

void loop() {
  Motor(1, true, 4095);      // motor 1 clockwise, full speed
  delay(2000);
  Motor(1, false, 2048);     // motor 1 counter-clockwise, half speed
  delay(2000);
  Motor(1, true, 0);         // motor 1 stopped
  delay(1000);

  Move(true, 3000);          // motors 3 and 4 forward together
  delay(1000);
  Stop();
}
```

Speed is 12-bit, so 4095 is full speed, 2048 about half and 0 stopped.

## Usage

Copy the functions you need from `PCA9685.ino` into your sketch, or open it in the Arduino IDE, select your board and upload. The `loop()` in the sketch is a demo drive sequence on motors 3 and 4, so replace it with your own.

## I²C address

| | Address (7-bit) |
|---|---|
| **Shield default (used in this sketch)** | **`0x60`** (`#define PCA9685_ADDR 0x60`) |
| PCA9685 chip base address | `0x40` (all address pins low) |
| PCA9685 all-call address | `0x70` |

The shield's address-select solder jumpers change the address if you stack several shields. Update `PCA9685_ADDR` to match.

## Datasheets

- [PCA9685: 16-channel, 12-bit PWM Fm+ I²C-bus LED controller (NXP)](https://www.nxp.com/docs/en/data-sheet/PCA9685.pdf)
- [TB6612FNG: Driver IC for Dual DC motor (Toshiba)](https://cdn-shop.adafruit.com/datasheets/TB6612FNG_datasheet_en_20121101.pdf)

