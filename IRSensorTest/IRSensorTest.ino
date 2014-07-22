volatile int state = LOW;

void setup(){
	Serial.begin(9600);
	attachInterrupt(0, interrupt, CHANGE);
}

void loop(){
	while(state == HIGH){
		Serial.println("interrupted"); 
	}
        Serial.println("bla");
}

void interrupt(){
	state =! HIGH;
}
