// Column locations.
//3456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456
//       1         2         3         4         5         6         7         8         9     9
//const unsigned long FAKE_LONG     =          10000UL; // Fake variable for column positions.

/*
 *  Simple HTTP get webclient test
 */

#ifndef LED_BUILTIN
#define LED_BUILTIN   27
#endif // LED_BUILTIN

const byte            VER_MAJOR     =                1; // Major version.
const byte            VER_MINOR     =                1; // Minor version.
const int             BAT_PIN       =              A13; // Battery Voltage / 2.
const float           CPU_VOLTS     =              3.3; // ADC Reference Voltage.
const int             ADC_MAX       =             4095; // Maximum ADC value.
const char            *ssid         = "KQRR_AC1900";
const char            *password     = "0140,athens,record,SUIT,WRITTEN,promise,THIN,8604,FRED,2763";
const char            *host         = "wifitest.adafruit.com";

int                   batRaw        =                0; // Raw battery Voltage / 2.
float                 batCooked     =              0.0; // Calculated battery Voltage.

#include <WiFi.h>


void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.printf(PSTR("Starting Client_AdaFruit_ESP32 version %d.%d, Build date %s %s\n"),
                                                                          VER_MAJOR,
                                                                          VER_MINOR,
                                                                          __DATE__,
                                                                          __TIME__);
  Serial.printf(PSTR("File %s\n__LINE__ %d\n"), __FILE__, __LINE__);
  
  pinMode(LED_BUILTIN, OUTPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

unsigned int value = 0;

void loop() {
  delay(5000);
  ++value;

  digitalWrite(LED_BUILTIN, HIGH); // Turn on LED.

  Serial.print("Starting connection attempt ");
  Serial.println(value);
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/testwifi/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  Serial.println();
  Serial.println("Data read back");
  Serial.println("----------------------------------------------------");
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }  
  Serial.println();
  Serial.println("----------------------------------------------------");
  Serial.println();
  
  Serial.println("closing connection");
  Serial.println();

  digitalWrite(LED_BUILTIN, LOW); // Turn off LED.
  batRaw = analogRead(BAT_PIN);
  //batCooked = float( (ADC_MAX / batRaw) * 2) / CPU_VOLTS;
  batCooked = (float(batRaw * 2) / float(ADC_MAX)) * CPU_VOLTS;
  Serial.print("batRaw = ");
  Serial.print(batRaw);
  Serial.print(", batCooked = ");
  Serial.println(batCooked);
  Serial.println();
}
