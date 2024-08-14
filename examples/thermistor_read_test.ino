#include <AMG8833.h>
AMG8833 amg;
void setup(){
  Serial.begin(9600);
  Wire.begin();
  Serial.print("Connecting");
  while(amg.begin()!=1){}
  Serial.println();
  Serial.println("AMG8833 device setup successfully!");
  delay(2000);
}
void loop(){
  Serial.print("Temperature:");
  Serial.println(amg.readThermistor());
  
  delay(500);
}
