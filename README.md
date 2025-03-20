# SmartDog
This is a Smart Dog project which can follow it's user and understand voice commands for controlling it.

Main microcontroller is Arduino for controlling basic hardware getting data from sensors and does the main logic in Arduino. Sensors are Ultrasonic sensor for sensing close objects/humans & It uses a PIR sensor for sensing the humans around the SmartDog. There is a second microcontroller for handling the speech recognition since speech recognition requires higher processing power using a Raspberry Pi 4 Model B for this would be a better approach. Python language is used for coding speech recognition and data from speech recognition is sent to Arduino using serial UART communication.

This product can understand voice commands from the user using a USB Microphone that connects to the Raspberry PI

All plastic parts of this product was 3-D modelled and printed.

![smartdog_portfolio](https://github.com/onurkankanli/SmartDog/assets/81397559/0d2e1692-5de0-4235-b3d3-2a1ff91e5152)

**During development phase:**
![car_front_top](https://github.com/user-attachments/assets/866525f3-909f-4b13-b532-e95d9913e508)
![{E161419E-68A9-490E-81C5-CDFEFC2761A3}](https://github.com/user-attachments/assets/811f30c5-de2b-48fa-ac48-7e5c6d3486ae)

**Hardware schematic:**
![SmartDog_schematic](https://github.com/user-attachments/assets/2b661dd8-e501-42ba-a137-3f36a5ea565f)

**Power consumption**
| Name           | Quantity  | Operating voltage | Operating current |
| -------------- | --------- | ---------------   | ----------------- |
| HC-SR04        | 1         |        5V         |       15mA        |  
| PIR Sensor     | 1         |        5V         |       23mA        |
| SG90 Servo     | 1         |       4.8V        |       400mA       |
| DC Motor       | 4         |     3V to 9V      |    (200mA) * 4    |
| Rotary encoder | 1         |                   |                   |
|                |           |                   |   Total: 1338mA   |

**Final product:**
![dog_front](https://github.com/user-attachments/assets/a7a70898-8565-4927-a0f3-ee1c6ef55125)
![dog_side](https://github.com/user-attachments/assets/621af241-ec59-40ee-a459-493b7456ad90)
