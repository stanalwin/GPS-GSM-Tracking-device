# GPS-GSM-Tracking-device
📡 ESP32 A9G Real-Time GPS/GSM Tracker
A real-time IoT location tracking system built with an ESP32 microcontroller and an A9G module (integrated GSM/GPRS + GPS). The device continuously parses GPS NMEA data, formats coordinates as a clickable Google Maps link, and delivers it to a registered mobile number via SMS — all within 5 seconds of a location fix.
Key features

Live location tracking — periodic GPS polling with NMEA sentence parsing over UART
SMS alerts — GSM-based SMS delivery of Google Maps links to a registered number
Geofence detection — automatic alert triggered when the device exits a defined boundary
AT command interface — full GSM registration, GPS control, and SMS dispatch via AT commands from ESP32
Outdoor validated — tested across multiple environments with consistent satellite fix and GPRS connectivity

Hardware
ComponentRoleESP32Main controller, logic & UART communicationA9G ModuleGSM/GPRS (SMS delivery) + GPS (NMEA data)
Recognition
This project was submitted as a research paper on real-time IoT tracking systems and received the Best Paper Award at an International Conference hosted by SRM Ramapuram University.
