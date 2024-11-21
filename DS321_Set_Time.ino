#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second) {
    char inString[20] = {0};
    byte j = 0;

    // Wait for the input string ending with 'x'
    while (true) {
        if (Serial.available()) {
            char inChar = Serial.read();
            inString[j++] = inChar;
            if (inChar == 'x' || j >= 20) { // Exit if 'x' received or overflow
                break;
            }
        }
    }

    // Debugging: print the received string
    Serial.print("Received: ");
    Serial.println(inString);

    // Parse the string: YYMMDDwHHMMSSx
    if (j >= 13) {  // Ensure minimum length
        year = ((inString[0] - '0') * 10) + (inString[1] - '0');
        month = ((inString[2] - '0') * 10) + (inString[3] - '0');
        date = ((inString[4] - '0') * 10) + (inString[5] - '0');
        dOW = (inString[6] - '0');
        hour = ((inString[7] - '0') * 10) + (inString[8] - '0');
        minute = ((inString[9] - '0') * 10) + (inString[10] - '0');
        second = ((inString[11] - '0') * 10) + (inString[12] - '0');
    } else {
        Serial.println("Error: Input too short!");
    }
}

void setup() {
    // Start the serial port
    Serial.begin(57600);

    // Start the I2C interface
    Wire.begin();

    Serial.println("DS3231 Time Setting Program");
    Serial.println("Enter time as YYMMDDwHHMMSSx (e.g., 2411204221630x for 20th Nov 2024, 10:16:30 PM)");
}

void loop() {
    // If something is coming in on the serial line, it's a time correction
    if (Serial.available()) {
        getDateStuff(year, month, date, dOW, hour, minute, second);

        // Set the clock mode to 24-hour format
        myRTC.setClockMode(false); // Set to 24-hour mode

        // Set the time on the DS3231
        myRTC.setYear(year);
        Serial.print("Year set to: "); Serial.println(year);

        myRTC.setMonth(month);
        Serial.print("Month set to: "); Serial.println(month);

        myRTC.setDate(date);
        Serial.print("Date set to: "); Serial.println(date);

        myRTC.setDoW(dOW);
        Serial.print("Day of week set to: "); Serial.println(dOW);

        myRTC.setHour(hour);
        Serial.print("Hour set to: "); Serial.println(hour);

        myRTC.setMinute(minute);
        Serial.print("Minute set to: "); Serial.println(minute);

        myRTC.setSecond(second);
        Serial.print("Second set to: "); Serial.println(second);

        Serial.println("Time successfully updated!");
    }

    delay(1000); // Prevent flooding
}
