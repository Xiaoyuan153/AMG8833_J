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
  //Serial.println(amg.readThermistor());
  amg.readAllPixels();
  print_double_matrix(AMG8833_PIXEL_ARRAY_SIZE,amg.realRect);
  delay(500);
}

void print_double_matrix(uint16_t size,double *_matrix){
    for (int i = 1; i <= size; i++)
	{
		Serial.print(_matrix[i - 1]);
		Serial.print(", ");
		if (i % 8 == 0) Serial.println();
	}
}