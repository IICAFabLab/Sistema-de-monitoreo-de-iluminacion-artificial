#define DHTPIN 15    // modify to the pin we connected
#define DHTTYPE DHT21   // AM2301

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include "Adafruit_SI1145.h"
#include "DHT.h"
#include <HTTPClient.h>
#include "time.h"
#include <BlynkSimpleEsp32.h>
DHT dht(DHTPIN, DHTTYPE);
//char auth[] = BLYNK_AUTH_TOKEN;
const char* ssid = "FABLAB";         // change SSID
const char* password = "#$IICA2019$#";
// Example for demonstrating the TSL2591 library - public domain!
String GOOGLE_SCRIPT_ID = "AKfycbwnKRHBtrnwlPS4XBEHaxfp2VujXD30atyPz_BnY5Glz3r6Y2h4Wad-WcvMjjZLgnCZ";
long interval = 10000;
//long tiempos [2] ={0,0};
long tiempo;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)
Adafruit_SI1145 uv = Adafruit_SI1145();
uint16_t ir, full;
float lux,visible;
/**************************************************************************/
/*
   Configures the gain and integration time for the TSL2591
*/
/**************************************************************************/
void configureSensor(void)
{
 // You can change the gain on the fly, to adapt to brighter/dimmer light situations
 //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
 tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
 //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
 tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);

 /* Display the gain and integration time for reference sake */ 
 Serial.println(F("------------------------------------"));
 Serial.print  (F("Gain:         "));
 tsl2591Gain_t gain = tsl.getGain();
 switch(gain)
 {
   case TSL2591_GAIN_LOW:
     Serial.println(F("1x (Low)"));
     break;
   case TSL2591_GAIN_MED:
     Serial.println(F("25x (Medium)"));
     break;
   case TSL2591_GAIN_HIGH:
     Serial.println(F("428x (High)"));
     break;
   case TSL2591_GAIN_MAX:
     Serial.println(F("9876x (Max)"));
     break;
 }
 Serial.print  (F("Timing:       "));
 Serial.print((tsl.getTiming() + 1) * 100, DEC);
 Serial.println(F(" ms"));
 Serial.println(F("------------------------------------"));
 Serial.println(F(""));
}
void setup(void)
{
 Serial.begin(115200);
 //Blynk.begin(auth, ssid, password);
 Serial.println(F("Starting Adafruit TSL2591 Test!"));
 if (tsl.begin())
 {
   Serial.println(F("Found a TSL2591 sensor"));
 }
 else
 {
   Serial.println(F("No sensor found ... check your wiring?"));
   while (1);
 }
Serial.println("Adafruit SI1145 test");
 if (! uv.begin()) {
   Serial.println("Didn't find Si1145");
   while (1);
 }
 Serial.println("OK!");
 /* Configure the sensor */
 configureSensor();
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 tiempo = millis();
}
/**************************************************************************/
/*
   Shows how to perform a basic read on visible, full spectrum or
   infrared light (returns raw 16-bit ADC values)
*/
/**************************************************************************/
void simpleRead(void)
{
 // Simple data read example. Just read the infrared, fullspecrtrum diode
 // or 'visible' (difference between the two) channels.
 // This can take 100-600 milliseconds! Uncomment whichever of the following you want to read
 uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
 //uint16_t x = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
 //uint16_t x = tsl.getLuminosity(TSL2591_INFRARED);
 Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
 Serial.print(F("Luminosity: "));
 Serial.println(x, DEC);
}
/**************************************************************************/
/*
   Show how to read IR and Full Spectrum at once and convert to lux
*/
/**************************************************************************/
void advancedRead(void)
{
 // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
 // That way you can do whatever math and comparisons you want!
 uint32_t lum = tsl.getFullLuminosity();
  ir = lum >> 16;
 full = lum & 0xFFFF;
 lux = tsl.calculateLux(full, ir);
 visible = full - ir;
 Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
 Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
 Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
 Serial.print(F("Visible: ")); Serial.print(visible); Serial.print(F("  "));
 Serial.print(F("Lux: ")); Serial.println(lux, 6);
}
/**************************************************************************/
/*
   Performs a read using the Adafruit Unified Sensor API.
*/
/**************************************************************************/
void unifiedSensorAPIRead(void)
{
 /* Get a new sensor event */
 sensors_event_t event;
 tsl.getEvent(&event);
 /* Display the results (light is measured in lux) */
 Serial.print(F("[ ")); Serial.print(event.timestamp); Serial.print(F(" ms ] "));
 if ((event.light == 0) |
     (event.light > 4294966000.0) |
     (event.light <-4294966000.0))
 {
   /* If event.light = 0 lux the sensor is probably saturated */
   /* and no reliable data could be generated! */
   /* if event.light is +/- 4294967040 there was a float over/underflow */
   Serial.println(F("Invalid data (adjust gain or timing)"));
 }
 else
 {
   Serial.print(event.light); Serial.println(F(" lux"));
 }
}
/**************************************************************************/
/*
   Arduino loop function, called once 'setup' is complete (your own code
   should go here)
*/
/**************************************************************************/
void loop()
{
 //simpleRead();
 advancedRead();
 // unifiedSensorAPIRead();
 float visibleL = uv.readVisible();
 float irL =uv.readIR();
 float humS= analogRead(2);
 Serial.println("===================");
 Serial.print("Vis: "); Serial.println( visibleL);
 Serial.print("IR: "); Serial.println( irL);
 // Uncomment if you have an IR LED attached to LED pin!
 //Serial.print("Prox: "); Serial.println(uv.readProx());
 float UVindex = uv.readUV();
 // the index is multiplied by 100 so to get the
 // integer index, divide by 100!
 UVindex /= 100.0; 
 Serial.print("UV: ");  Serial.println(UVindex);
 Serial.print("Humedad suelo: "); Serial.println(humS);
Serial.begin(115200);
Serial.println("DHTxx test!");
dht.begin();
float h = dht.readHumidity();
float t = dht.readTemperature();
// check if returns are valid, if they are NaN (not a number) then something went wrong!
if (isnan(t) || isnan(h))
{
  Serial.println("Failed to read from DHT");
}
else
{
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
 
}
if (WiFi.status() == WL_CONNECTED && millis()-tiempo>interval) {
   static bool flag = false;   
   String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+"humedadA=" + String(h) + "&temperatura=" + String(t)+ "&luz=" + String( visible)+ "&lux=" + String(lux)+ "&ir=" + String(ir)+"&luzUV=" + String(UVindex)+"&inext=" + String(0);
  
   Serial.print("POST data to spreadsheet:");
   Serial.println(urlFinal);
   HTTPClient http;
   http.begin(urlFinal.c_str());
   http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
   int httpCode = http.GET();
   Serial.print("HTTP Status Code: ");
   Serial.println(httpCode);
   //---------------------------------------------------------------------
   //getting response from google sheet
   String payload;
   if (httpCode > 0) {
       payload = http.getString();
       Serial.println("Payload: "+payload);   
   }
   //---------------------------------------------------------------------
   http.end();
   tiempo = millis();
}
  delay(1000);
}

