// Column locations.
//3456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456
//       1         2         3         4         5         6         7         8         9     9
//

const byte            VER_MAJOR     =                1; // Major version.
const byte            VER_MINOR     =                1; // Minor version.
const int             BAT_PIN       =              A13; // Battery Voltage / 2.
const float           CPU_VOLTS     =              3.3; // ADC Reference Voltage.
const int             ADC_MAX       =             4095; // Maximum ADC value.
const int             LED_PIN       =               21;

int                   batRaw        =                0; // Raw battery Voltage / 2.
float                 batCooked     =              0.0; // Calculated battery Voltage.

void setup()
{
  Serial.begin(115200);
     
  Serial.printf(PSTR("Starting Bat_Check_ESP32 version %d.%d, Build date %s %s\n"),
                                                                          VER_MAJOR,
                                                                          VER_MINOR,
                                                                          __DATE__,
                                                                          __TIME__);
  Serial.printf(PSTR("File %s\n__LINE__ %d\n"), __FILE__, __LINE__);
  
  pinMode(LED_PIN, OUTPUT);
  Serial.printf(PSTR("LED_PIN = %d\n"), LED_PIN);
}

void loop()
{
  batRaw = analogRead(BAT_PIN);
  //batCooked = float( (ADC_MAX / batRaw) * 2) / CPU_VOLTS;
  batCooked = (float(batRaw * 2) / float(ADC_MAX)) * CPU_VOLTS;
  Serial.printf(PSTR("%10lu batRaw = %4d, batCooked = %5.3f\n"), millis(), batRaw, batCooked);

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(4500);
}
