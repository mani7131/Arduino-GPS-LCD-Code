/*Connection:
GPS TX : Digital Pin 8(RX
)## LCD Connection with Arduino ##    
RS => digital pin 3    
RW => GND    
E  => digital pin 2     
D0-D3 => NC(Not Connected)     
D4 => digital pin 4     
D5 => digital pin 5    
D6 => digital pin 6     
D7 => digital pin 7
*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal lcd(3, 2, 4, 5, 6, 7);
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);
  ss.begin(GPSBaud);
    
  lcd.print("www.githu.com/mani7131"); 
  delay(1000);
  lcd.clear(); 
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    lcd.print(F("No GPS detected"));
    while(true);
  }
}

void displayInfo()
{   
  if (gps.location.isValid())
  {
    lcd.setCursor(0,0);
    lcd.print("Lat=");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0,1);
    lcd.print("Lng=");
    lcd.print(gps.location.lng(), 6);    
  }
  else
  {
   lcd.print("INVALID");
  }   
}
