#include <HardwareSerial.h>

/* ================= UART PINS ================= */
#define A9G_RX 6
#define A9G_TX 7

/* ================= SOS BUTTON ================= */
#define SOS_BUTTON 2

/* ================= SOS NUMBER ================= */
String SOS_NUMBER = "+917397708803";

/* ================= SERIAL ================= */
HardwareSerial A9G(0);

/* ================= GPS VARIABLES ================= */
float latitude = 0.0;
float longitude = 0.0;
bool gpsFix = false;

/* ================= TIMING ================= */
unsigned long lastPress = 0;
const unsigned long debounceTime = 3000;

/* ================================================= */
/*                     SETUP                         */
/* ================================================= */

void setup() {

  Serial.begin(115200);

  A9G.begin(115200, SERIAL_8N1, A9G_RX, A9G_TX);

  pinMode(SOS_BUTTON, INPUT_PULLUP);

  Serial.println("\nBOOTING SYSTEM...");
  
  delay(12000);

  initA9G();

  Serial.println("SOS SYSTEM READY");
}

/* ================================================= */
/*                      LOOP                         */
/* ================================================= */

void loop() {

  readA9G();

  if (millis() - lastPress < debounceTime)
    return;

  if (digitalRead(SOS_BUTTON) == LOW) {

    delay(50);

    if (digitalRead(SOS_BUTTON) == LOW) {

      lastPress = millis();

      triggerSOS();
    }
  }
}

/* ================================================= */
/*                INITIALIZE MODULE                  */
/* ================================================= */

void initA9G() {

  sendAT("AT");
  sendAT("ATE0");

  sendAT("AT+CMGF=1");

  sendAT("AT+CNMI=2,2,0,0,0");

  sendAT("AT+GPS=1");

  sendAT("AT+GPSRD=1");

  sendAT("AT+CREG?");
}

/* ================================================= */
/*                  READ SERIAL DATA                 */
/* ================================================= */

void readA9G() {

  while (A9G.available()) {

    String line = A9G.readStringUntil('\n');

    line.trim();

    if (line.length() == 0)
      continue;

    Serial.println(line);

    /* ---------- GPS DATA ---------- */

    if (line.startsWith("$GNRMC")) {

      parseGPS(line);
    }

    /* ---------- SMS COMMAND ---------- */

    if (line.indexOf("+CMT:") >= 0) {

      delay(500);

      String sms = A9G.readString();

      sms.trim();

      sms.toUpperCase();

      Serial.println("SMS RECEIVED:");
      Serial.println(sms);

      if (sms.indexOf("SEND LOCATION") >= 0) {

        sendLocation();
      }

      else if (sms.indexOf("STATUS") >= 0) {

        sendSMS("SYSTEM ACTIVE");
      }
    }
  }
}

/* ================================================= */
/*                  TRIGGER SOS                      */
/* ================================================= */

void triggerSOS() {

  Serial.println("\nSOS TRIGGERED");

  sendSMS("EMERGENCY! I NEED HELP!");

  delay(5000);

  sendLocation();

  delay(5000);

  makeCall();
}

/* ================================================= */
/*                    MAKE CALL                      */
/* ================================================= */

void makeCall() {

  bool connected = false;

  for (int attempt = 1; attempt <= 3; attempt++) {

    Serial.println("CALL ATTEMPT: " + String(attempt));

    A9G.print("ATD");
    A9G.print(SOS_NUMBER);
    A9G.println(";");

    unsigned long startTime = millis();

    while (millis() - startTime < 25000) {

      if (A9G.available()) {

        String response = A9G.readStringUntil('\n');

        response.trim();

        if (response.length() == 0)
          continue;

        Serial.println(response);

        if (response.indexOf("CONNECT") >= 0) {

          Serial.println("CALL CONNECTED");

          connected = true;

          return;
        }

        if (response.indexOf("BUSY") >= 0 ||
            response.indexOf("NO ANSWER") >= 0 ||
            response.indexOf("NO CARRIER") >= 0) {

          Serial.println("CALL FAILED");

          break;
        }
      }
    }

    A9G.println("ATH");

    delay(3000);
  }

  if (!connected) {

    sendSMS("EMERGENCY CALL NOT ANSWERED!");
  }
}

/* ================================================= */
/*                  SEND LOCATION                    */
/* ================================================= */

void sendLocation() {

  String msg;

  if (gpsFix) {

    msg = "MY LOCATION:\n";

    msg += "https://maps.google.com/?q=";

    msg += String(latitude, 6);

    msg += ",";

    msg += String(longitude, 6);
  }

  else {

    msg = "GPS NOT FIXED YET";
  }

  sendSMS(msg);
}

/* ================================================= */
/*                    PARSE GPS                      */
/* ================================================= */

void parseGPS(String data) {

  String part[20];

  int index = 0;

  while (data.length() > 0 && index < 20) {

    int comma = data.indexOf(',');

    if (comma == -1) {

      part[index++] = data;

      break;
    }

    part[index++] = data.substring(0, comma);

    data = data.substring(comma + 1);
  }

  if (part[2] == "A") {

    if (part[3] != "" && part[5] != "") {

      latitude = convertCoordinate(part[3], true);

      longitude = convertCoordinate(part[5], false);

      if (part[4] == "S")
        latitude *= -1;

      if (part[6] == "W")
        longitude *= -1;

      gpsFix = true;

      Serial.println("GPS FIXED");

      Serial.print("LAT: ");
      Serial.println(latitude, 6);

      Serial.print("LON: ");
      Serial.println(longitude, 6);
    }
  }

  else {

    gpsFix = false;
  }
}

/* ================================================= */
/*              CONVERT GPS COORDINATE               */
/* ================================================= */

float convertCoordinate(String raw, bool isLatitude) {

  int degreeLength = isLatitude ? 2 : 3;

  float degrees = raw.substring(0, degreeLength).toFloat();

  float minutes = raw.substring(degreeLength).toFloat();

  return degrees + (minutes / 60.0);
}

/* ================================================= */
/*                     SEND SMS                      */
/* ================================================= */

void sendSMS(String message) {

  Serial.println("SENDING SMS...");

  A9G.print("AT+CMGS=\"");

  A9G.print(SOS_NUMBER);

  A9G.println("\"");

  delay(1000);

  A9G.print(message);

  delay(500);

  A9G.write(26);

  delay(5000);

  Serial.println("SMS SENT");
}

/* ================================================= */
/*                  SEND AT COMMAND                  */
/* ================================================= */

void sendAT(String command) {

  Serial.println("CMD: " + command);

  A9G.println(command);

  delay(1000);

  while (A9G.available()) {

    Serial.write(A9G.read());
  }
}