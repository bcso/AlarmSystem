#include <Arduino.h>
float currtime = 0;
boolean printed = false;
void setup()
{
	pinMode(7, INPUT);
	pinMode(8, INPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	for (int i = 7; i<9; i++){
		currtime = millis();
		digitalWrite(i, HIGH);
		Serial.print("set pin ");
        Serial.print(i);
        Serial.print(" to high is ");                        			
        Serial.println(digitalRead(i));
        printed = false;
		while ((millis() - currtime) < 1000){
			if (digitalRead(11) == HIGH){
				if (printed == false){
					Serial.println("High registered on ");
					Serial.print("WRITE: ");
	          		Serial.println(i);
	          		Serial.println("READ: 11");
	          		// printed = true;
          		}
			}
			// if (digitalRead(11) == LOW){
			// 	if (printed == false){
			// 	Serial.println("Low registered on ");
			// 	Serial.print("WRITE: ");
   //        		Serial.println(i);
   //        		Serial.println("READ: 11");
	  //         		// printed = true;
   //        		}          		
			// }			
			if (digitalRead(12) == HIGH){
				if (printed == false){
				Serial.println("High registered on ");
				Serial.print("WRITE: ");
          		Serial.println(i);
          		Serial.println("READ: 12");
	          		// printed = true;
          		}            		
			}
			// if (digitalRead(12) == LOW){
			// 	if (printed == false){
			// 	Serial.println("Low registered on ");
			// 	Serial.print("WRITE: ");
   //        		Serial.println(i);
   //        		Serial.println("READ: 12");
	  //         		// printed = true;
   //        		}            		
			// }

		}
		digitalWrite(i, LOW);
	}
}