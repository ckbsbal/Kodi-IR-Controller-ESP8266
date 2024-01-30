# Kodi-IR-Controller-ESP8266
Convert an IR remote into a smart Kodi controller with ESP8266. Control channels seamlessly using WiFi. Revive the charm of old-school remotes in modern home automation!

## Overview

This project centers around using the ESP8266 microcontroller and Arduino to convert an IR remote into a smart Kodi controller. It is specifically tailored for seamlessly opening PVR channels by entering channel numbers using an inexpensive IR remote. This setup combines the simplicity of an old-school remote with the advanced features of Kodi.
## Demo

Watch the project in action: [![Project Demo Video](https://img.youtube.com/vi/5jyfP5IJLSQ/0.jpg)](https://youtube.com/watch?v=5jyfP5IJLSQ&si=xKSJFhQx0Yml8SYH)
## Features

- **IR Signal Processing:** Decode IR signals from a cheap IR remote.
- **WiFi Connectivity:** Establish a connection with your local WiFi network for communication with Kodi.
- **Kodi API Integration:** Send commands to Kodi using HTTP requests based on decoded IR signals.
- **Channel Control:** Seamlessly open PVR channels by entering channel numbers on your IR remote.

## Getting Started

### Prerequisites

- [IRremoteESP8266 Library](https://github.com/crankyoldgit/IRremoteESP8266)
- [ESP8266HTTPClient Library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient)
- [WiFi Library](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)

### ESP8266 NodeMCU with IR Receiver Connection

| ESP8266 NodeMCU | IR Receiver   |
|------------------|---------------|
| D5               | Signal        |
| GND              | GND           |
| 3V               | VCC           |

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/ESP8266-Kodi-IR-Remote.git
    ```

2. Open the Arduino IDE and load the project.

3. Install the required libraries using the Library Manager.

4. Update the WiFi credentials and Kodi details in the code.

5. Upload the code to your ESP8266 board.

## Usage

1. Power up your ESP8266 board with the IR remote connected.

2. Point your IR remote towards the IR receiver and press the channel numbers.

3. Enjoy effortlessly opening PVR channels on Kodi using the old-school IR remote!

## Kodi API Commands

- Fetch all channels:
    ```bash
    curl -X POST -H "Content-Type: application/json" -H "Accept: application/json" -H "Authorization: Basic $(echo -n 'kodi:kodi' | base64)" -d '{"jsonrpc": "2.0", "method": "PVR.GetChannels", "params": {"channelgroupid": 1}, "id": 1}' http://192.168.1.20:8080/jsonrpc
    ```

- Open a specific channel (replace `1045` with the desired channel ID):
    ```bash
    curl -X POST -H "Content-Type: application/json" -H "Accept: application/json" -H "Authorization: Basic $(echo -n 'kodi:kodi' | base64)" -d '{"jsonrpc": "2.0", "method": "Player.Open", "params": {"item": {"channelid": 1045}}, "id": 1}' http://192.168.1.7:8080/jsonrpc
    ```

## Contributing

Contributions are welcome! Feel free to open issues, submit pull requests, or provide suggestions to enhance this project.

## License

This project is licensed under the [MIT License](LICENSE).
