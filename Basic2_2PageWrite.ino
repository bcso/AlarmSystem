#include <Arduino.h>


void void setup()
{
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, INPUT);
	pinMode(11, INPUT);
	Serial.begin(9600);
}

void loop(){
	for (int i = 8; i<10; i++){
		currtime = millis();
		while (millis() - currtime) < 1000{
			digitalWrite(i, HIGH);
			if digitalRead(10) == HIGH{
				Serial.println("High registered on WRITE: " + std::to_string(i) + " READ: 10");
			}
			if digitalRead(11) == HIGH{
				Serial.println("High registered on WRITE: " +  std::to_string(i) + " READ: 11");
			}
		}
	}
}