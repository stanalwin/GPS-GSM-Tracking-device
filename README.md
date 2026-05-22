# GPS-GSM-Tracking-device
# 📡 ESP32 A9G Real-Time GPS/GSM Tracker

A real-time IoT-based GPS tracking system developed using the Espressif Systems ESP32 microcontroller and the Ai-Thinker A9G GSM/GPS module.
The system continuously acquires GPS coordinates, parses NMEA data over UART, and sends live location updates as clickable Google Maps links through GSM-based SMS communication.

Designed for emergency monitoring, vehicle tracking, personal safety, and outdoor asset tracking applications, the device delivers location updates within seconds after obtaining a valid GPS fix.

---

## 🚀 Features

* 📍 **Real-Time GPS Tracking**
  Continuously reads and parses GPS NMEA sentences from the A9G module to obtain accurate latitude and longitude coordinates.

* 📲 **SMS-Based Location Sharing**
  Sends live Google Maps links directly to a registered mobile number using GSM SMS services.

* 🌐 **Google Maps Integration**
  Automatically formats GPS coordinates into a clickable Google Maps URL.

* 🚨 **Geofence Detection**
  Detects when the tracker exits a predefined geographical boundary and triggers automatic SMS alerts.

* 📡 **GSM + GPS Integration**
  Utilizes the A9G module for both cellular communication and GPS positioning in a compact IoT architecture.

* ⚡ **Fast Response Time**
  Delivers location updates within approximately 5 seconds after obtaining GPS lock.

* 🔧 **AT Command Control**
  Full control of GSM registration, SMS transmission, GPS initialization, and communication through AT commands.

* 🌍 **Outdoor Validated Performance**
  Tested across multiple outdoor environments with reliable GPS satellite acquisition and GSM connectivity.

---

# 🛠 Hardware Components

| Component    | Role                                   |
| ------------ | -------------------------------------- |
| ESP32        | Main controller and UART communication |
| A9G Module   | GSM/GPRS communication + GPS receiver  |
| SIM Card     | SMS and cellular connectivity          |
| Push Button  | SOS trigger / manual alert             |
| Power Supply | Portable device power source           |

---

# ⚙️ Working Principle

1. The ESP32 initializes the A9G GSM/GPS module using AT commands.
2. GPS NMEA data is continuously received over UART.
3. The system parses latitude and longitude coordinates from `$GNRMC` sentences.
4. Coordinates are converted into a Google Maps link.
5. The GSM module sends the live location via SMS to the registered mobile number.
6. If the device exits the predefined geofence region, an alert SMS is automatically triggered.

---

# 📌 Applications

* Women Safety Systems
* Vehicle Tracking
* Child & Elderly Monitoring
* Emergency Rescue Devices
* Asset Tracking
* Outdoor Navigation Systems
* Smart IoT Security Devices

---

# 🧠 Technologies Used

* Embedded C++
* UART Serial Communication
* GSM/GPRS Communication
* GPS NMEA Parsing
* AT Command Interface
* IoT Embedded Systems

---

# 🏆 Recognition

This project was presented as a research paper on real-time IoT tracking systems and received the **Best Paper Award** at an International Conference hosted by SRM Institute of Science and Technology.

---

# 📷 System Overview

* ESP32 communicates with the A9G module through UART.
* GPS coordinates are extracted in real time.
* GSM network is used for SMS-based location sharing.
* Users receive direct Google Maps navigation links on their mobile devices.

---

# 🔮 Future Improvements

* Mobile application integration
* Cloud-based live tracking dashboard
* Real-time web monitoring
* Low-power optimization
* SOS emergency button support
* Battery backup and solar charging

---

# 📄 License

This project is intended for academic, research, and educational purposes.

