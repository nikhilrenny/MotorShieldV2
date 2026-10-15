# MotorShieldV2

Bare-metal PCA9685/TB6612 driver for the Adafruit Motor Shield V2. A single sketch (`PCA9685.ino`) that uses only the Arduino `Wire` library, with no Adafruit libraries.

## What it does

- Talks to the PCA9685 directly over I²C (default shield address `0x60`).
- Drives DC motors M1–M4 through the TB6612 H-bridges with 12-bit PWM (0–4095).
- Small API: `Motor(motor, dir, pwm)`, `Move(dir, pwm)` (motors 3 and 4 together), `Stop()`, `Brake()`.

## Channel map

| Motor | PWM | IN1 | IN2 |
|---|---|---|---|
| M1 | 8 | 10 | 9 |
| M2 | 13 | 11 | 12 |
| M3 | 2 | 4 | 3 |
| M4 | 7 | 5 | 6 |

## Usage

Open `PCA9685.ino` in the Arduino IDE, select your board and upload. `loop()` contains a demo drive sequence on motors 3 and 4, so edit it for your setup.

## Why

Adafruit's library supports steppers and servos as well and is correspondingly larger. This sketch does DC motors only, in a few dozen lines, as a minimal reference for the PCA9685 register interface.

## Licence

MIT. See `LICENSE`.
