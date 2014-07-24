const int speaker_pin = 10; //the alarm speaker pin value is 10
const int sensorValSwitch = 0; //pin A0  analog input
const int debugLight = 5; //pin connected to the light for every button press
const int sensor_pin[] = {6,7,8,9}; //sets the pin numbers for pins that sense a break in 

int passCode [] = {0,2,4,4}; //the password to deactivate the alarm, can be changed at any time
int userGuess[4]; // the array holding the user's guesses

int digitCounter = 0; //Counter to keep track of how many input digits have been inputted
int sensorVal; //the value of the analog pin sensing the voltage

long currTime; //the current time variable used for timing
float trip_duration = 0; //the amount of time the sensor (interrupt) is tripped for
float start_time = 0; //the start time used for timing
boolean alarm_deactivated = false; //true when alarm is deactivated and false as soon as it is deactivated


volatile int state = LOW; //will turn high
volatile int activatedPin;

//these variable relate to the millis substitute
volatile unsigned long rollOver = 0; //will count the roll overs
volatile unsigned long mill = 0; //used as a millis that is not quite so accurate

void setup(){
	attachInterrupt(0,trip,CHANGE);

        //setting the pins that detect which interrupt is triggered to input pins
	pinMode(sensor_pin[0], INPUT); 
	pinMode(sensor_pin[1], INPUT);
	pinMode(sensor_pin[2], INPUT);
	pinMode(sensor_pin[3], INPUT);
        
        //the light and speaker pins are labelled as outputs
	pinMode(debugLight, OUTPUT);
	pinMode(speaker_pin, OUTPUT);
        
        //starts serial monitor with a speed of 9600 bits per second
	Serial.begin(9600);

	TCCR1A = 0; //setting Timer Register Control Counter 1 A to zero and setting the counter to the normal mode of operation
        TCCR1B = (_BV(CS11) | _BV(CS10)); // prescaler to 64 by setting the bit value of the bits CS11 and CS10 to 1 specifying these bits within the byte
        
        //interrupt triggered for every roll over of TCNT1
        //TIMSK1 is the timer/counter interrupt mask register
        //TOIE1 is the timer/counter overflow interupt enable
        TIMSK1 = (_BV(TOIE1));//
        //TIMSK1 = (1 << TOIE1);
        TCNT1 = 0;    //setting the counter to zero to clear any data that might remain from previous times
}

void loop(){	
	start_time = mill;
	trip_duration = 0;
	alarm_deactivated = false;
	Serial.print("Alarm deactivated...: ");
	Serial.print("State: ");
	Serial.print(state);
	Serial.print(" alarm_deactivated: ");
	Serial.print(alarm_deactivated);
	Serial.print(" trip dur: ");
	Serial.println(trip_duration);
	//Loop me when sensor is tripped

	while( (state == HIGH) && (alarm_deactivated == false)) {
		Serial.print("Sensor tripped at pin... ");
		Serial.print(activatedPin);		
		Serial.print(" Pin 6: ");
		Serial.print(digitalRead(6));
		Serial.print(" Pin 7: ");
		Serial.print(digitalRead(7));
		Serial.print(" Pin 8: ");
		Serial.print(digitalRead(8));
		Serial.print(" Pin 9: ");
		Serial.print(digitalRead(9));		
	    Serial.print(" checking for false alarm... ");
		Serial.print("State: ");
		Serial.print(state);
		Serial.print(" alarm_deactivated: ");
		Serial.print(alarm_deactivated);
		Serial.print(" trip dur: ");
		Serial.println(trip_duration);
		trip_duration = mill - start_time;

		//Loop me until the user enters the right code (alarm_deactivated will be true)
		while ((trip_duration > 2000) && (alarm_deactivated == false)){

		    //trigger alarm		    
		    tone(speaker_pin,500);
		    Serial.println("Alarm has been tripped! Enter the code!");
	
			//Return boolean result after all testing.
			alarm_deactivated = runCheck(); 

			//Pretty print statments and run me again!
			if (alarm_deactivated == true){

				Serial.println("Yay got it!");
				//Shut off the alarm
				noTone(speaker_pin);
				// Exit parent while loop
				state = LOW; 
			}
			else if (alarm_deactivated == false){
				
				Serial.print("Expected: ");
				printArray(passCode);		
				Serial.print("Got: ");
				printArray(userGuess);		
				Serial.println("Try again!");	
			}			  
		}
	}	
}

//Run the combination accepting and checking
boolean runCheck(){	
	digitCounter = 0; //Setup for user guess
	while(digitCounter != 4){
		sensorVal = analogRead(sensorValSwitch);
		//Check if sensor val (analog input) is not from interference.
		if ((sensorVal > 150) ){
			//Match	the analog sensor value to known list		
			matchSensorVal(sensorVal);		
			resetSensor(); //Allow time for the user to let go of their finger
		}		
	}
	return checkMatchResult();
}

//Print the provided array
void printArray(int array[]){
	for (int i = 0; i<4; i++){
		Serial.print(array[i]);
		Serial.print(" ,");
	}
	Serial.println("");
}

//Run a check on the userGuess to see if it is same as predefined key combination
boolean checkMatchResult(){
	boolean digitCheck = true;
	for (int i = 0; i<4; i++){ //Check each value in the array for a mismatch
		if (passCode[i] != userGuess[i]){
			digitCheck = false; //Mismatch!
		}
	}
	return digitCheck;
}

//Delay creator
void resetSensor(){
	currTime = mill;
	while ((mill - currTime) <1000){
		sensorVal = 0;
		digitalWrite(debugLight, HIGH);
	}
	digitalWrite(debugLight, LOW);	
}

void matchSensorVal(int sensorVal){
	Serial.println("Matching Value...");
	// Serial.println(sensorVal);
		if ((sensorVal >= 987) && (sensorVal <= 996)){
			userGuess[digitCounter] = 0;
		}
		
		else if ((sensorVal >= 949) && (sensorVal <= 958)){
			userGuess[digitCounter] = 1;
		}	

		else if ((sensorVal >= 789) && (sensorVal <= 801)){
			userGuess[digitCounter] = 2;
		}			

		else if ((sensorVal >= 639) && (sensorVal <= 650)){
			userGuess[digitCounter] = 3;
		}

		else if ((sensorVal >= 1009) && (sensorVal <= 1022)){
			userGuess[digitCounter] = 4;
		}

		else if ((sensorVal >= 552) && (sensorVal <= 563)){
			userGuess[digitCounter] = 5;
		}

		else if ((sensorVal >= 310) && (sensorVal <= 322)){
			userGuess[digitCounter] = 6;
		}

		else if ((sensorVal >= 876) && (sensorVal <= 886)){
			userGuess[digitCounter] = 7;
		}

		else if ((sensorVal >= 740) && (sensorVal <= 780)){
			userGuess[digitCounter] = 8;
		}

		else if ((sensorVal >= 400) && (sensorVal <= 410)){
			userGuess[digitCounter] = 9;
		}		

		Serial.print("User guess number ");
		Serial.print(digitCounter);
		Serial.print("is: ");
		Serial.println(userGuess[digitCounter]);
		// Serial.print(" at sensorVal: ");
		// Serial.println(sensorVal);
		
		digitCounter ++; //Increment digit guess				
}

// interrupt handler function 
void trip(){	
	state = !state;
	activatedPin=0;
	for (int i =6; i<10; i++)
		if (digitalRead(i) == HIGH){
			activatedPin = i;					
		}
}

ISR(TIMER1_OVF_vect){
  rollOver++;
  mill = ((rollOver*65536 + TCNT1)/250);
}

