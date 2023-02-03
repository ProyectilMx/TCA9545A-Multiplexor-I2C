// --------------------------------------
// i2c_scanner
//TCA9545A 
/* 
 *  Misael Reyes
 *  16/AGO/2021
 */

#include <Wire.h>

#define ADD 0x70 

void setup() {
  Wire.begin();

  Serial.begin(115200);
  while (!Serial); // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
void tcaselect(uint8_t i) {
  if (i > 3) return;
 
  Wire.beginTransmission(ADD);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
void loop() {
  int nDevices = 0;

  Serial.println("Scanning...");
for(byte t = 0; t < 4;t++){
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);
      
  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    if (address == ADD) continue;
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
   }
 }
  
    Serial.println("done\n");
  
  delay(5000); // Wait 5 seconds for next scan
}
