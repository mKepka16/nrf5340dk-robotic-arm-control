# Robotic Arm Control Project for nRF5340DK

This project demonstrates how to control a robotic arm using the Nordic nRF5340 Development Kit (nRF5340DK) and Zephyr RTOS. It provides code to control servo motors via PWM, manage Bluetooth connections, and handle LED indicators for status updates.

![Project photo](assets/photo.jpg)

## Hardware Setup

- **MCU Board:** Nordic nRF5340DK
- **Servo Motors:**
  - 3 × TowerPro MG-995 (Base rotation, shoulder, and elbow)
  - 2 × TowerPro SG90 Micro (Grabber and wrist)
- **Connections:**
  - **PWM Pins:** Connect the servo signal wires to the appropriate PWM-capable pins on the nRF5340DK.
  - **Power Supply:** Ensure the servos are powered by a 5V external power source capable of providing up to 5A.
  - **GND:** Connect the ground of the external power supply to the nRF5340DK GND.
- **Optional:** LEDs for status indication connected to GPIO pins.

## Features
- Controls servo motors using PWM signals
- Bluetooth Low Energy (BLE) support for remote control
- LED indicators for system status
- Modular design for easy extension and customization

## Software
- **Zephyr RTOS** (see `prj.conf` for configuration)
- Device tree overlay for pin configuration (see `nrf5340dk_nrf5340_cpuapp_ns.overlay`)

## Usage
1. Connect the servo motors and LEDs to the nRF5340DK as described above.
2. Build and flash the firmware.
3. Use a Bluetooth-enabled device to connect to the robotic arm and send control commands.
4. Observe the servo movements and LED status updates.

## File Overview
- `src/main.c` – Main application logic
- `src/servo.c`, `src/servo.h` – Servo motor control
- `src/led.c`, `src/led.h` – LED status management
- `src/connection.c`, `src/connection.h` – Bluetooth connection handling
- `src/racs.c`, `src/racs.h` – Robotic Arm Control Service (BLE)
- `src/advert.c`, `src/advert.h` – Bluetooth advertising functionality
- `prj.conf` – Zephyr configuration
- `nrf5340dk_nrf5340_cpuapp_ns.overlay` – Device tree overlay for pin assignment

## Notes
- Ensure the servo motors are powered by an external power source to avoid overloading the nRF5340DK.
- If you encounter Bluetooth connection issues, verify the BLE configuration in `prj.conf`.
- The servo control logic can be customized in `servo.c` to suit your specific application.

## Documentation
- [nRF5340DK Product Page](https://www.nordicsemi.com/Products/Development-hardware/nRF5340-DK)
- [Zephyr RTOS Documentation](https://docs.zephyrproject.org/latest/)