#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

// Initialize DS3231 RTC
DS3231 myRTC;

// Initialize I2C LCD (address 0x27 or 0x3F, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool century = false;
bool h12Flag;
bool pmFlag;

void setup() {
    // Start I2C communication
    Wire.begin();

    // Initialize Serial Monitor for debugging
    Serial.begin(57600);

    // Initialize LCD
    lcd.begin(16,2);
    lcd.backlight(); // Turn on the backlight

    // Display welcome message
    lcd.setCursor(0, 0);
    lcd.print("RTC Clock");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000); // Pause for 2 seconds
    lcd.clear();
}

void loop() {
    // Get time from DS3231
    int year = myRTC.getYear() + 2000; // Add 2000 for full year
    int month = myRTC.getMonth(century);
    int date = myRTC.getDate();
    int hour = myRTC.getHour(h12Flag, pmFlag); // 24-hour mode
    int minute = myRTC.getMinute();
    int second = myRTC.getSecond();

    // Print time on Serial Monitor
    Serial.print(year);
    Serial.print("-");
    Serial.print(month);
    Serial.print("-");
    Serial.print(date);
    Serial.print(" ");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);

    // Display time on LCD
    lcd.setCursor(0, 0); // Top row
    lcd.print("Time: ");
    if (hour < 10) lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
    if (minute < 10) lcd.print("0");
    lcd.print(minute);
    lcd.print(":");
    if (second < 10) lcd.print("0");
    lcd.print(second);

    lcd.setCursor(0, 1); // Bottom row
    lcd.print("Date: ");
    if (date < 10) lcd.print("0");
    lcd.print(date);
    lcd.print("/");
    if (month < 10) lcd.print("0");
    lcd.print(month);
    lcd.print("/");
    lcd.print(year);

    delay(1000); // Update every second
}
