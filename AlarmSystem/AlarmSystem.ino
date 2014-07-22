int sensorValSwitch = 0;
int debugLight = 5;
int passCode [] = {1,1,2,3};
int userGuess[4];
int digitCounter = 0; //Counter to keep track of how many input digits have been inputted
int sensorVal;
long currTime;
volatile int state=LOW;
float trip_duration = 0;
float start_time = 0;
boolean alarm_deactivated = false;

void setup(){
	// parameter1 - interrupt (0 or 1)
	// parameter2 - name of the interrupt handler function 
	// parameter3 - trigger(CHANGE,LOW,RISING or FALLING)
	attachInterrupt(0,button_press,CHANGE);	

	pinMode(debugLight, OUTPUT);
	Serial.begin(9600);		
}

void loop(){
	//start_count = true;
	start_time = millis();
	trip_duration = 0;
	alarm_deactivated = false;
	Serial.print("Waiting for push...: ");
	Serial.print("State: ");
	Serial.print(state);
	Serial.print(" alarm_: ");
	Serial.print(alarm_deactivated);
	Serial.print(" trip dur: ");
	Serial.println(trip_duration);
	while((state == HIGH) && (alarm_deactivated == false)){
		Serial.print("pushed! ");
		/*if (start_count == true){
		  start_time = millis();
		  start_count = false;
		}*/
		trip_duration = millis() - start_time;
		if(trip_duration > 2000){
		    //trigger alarm		    
		    Serial.println("Alarm has been tripped");
			//Return boolean result after all testing.
			alarm_deactivated = runCheck(); 
			//Pretty print statments and run me again! (Can ommit this)
			if (alarm_deactivated != false){
				Serial.println("Yay got it!");
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

	digitCounter = 0;
}

//Run the combination accepting and checking
boolean runCheck(){
	// Serial.println("Running Check...");
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
	for (int i = 0; i<4; i++){
		if (passCode[i] != userGuess[i]){
			digitCheck = false;
		}
	}
	return digitCheck;
}

//Delay creator
void resetSensor(){
	currTime = millis();
	while ((millis() - currTime) <1000){
		sensorVal = 0;
		digitalWrite(debugLight, HIGH);
	}
	digitalWrite(debugLight, LOW);	
}

void matchSensorVal(int sensorVal){
	Serial.println("Matching Value...");
	Serial.println(sensorVal);
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

		Serial.print("User guess is: ");
		Serial.print(userGuess[digitCounter]);
		Serial.print(" at sensorVal: ");
		Serial.println(sensorVal);
		Serial.println(digitCounter);
		digitCounter ++; //Increment digit guess				
}

// interrupt handler function 
void button_press(){
state = !state;
}

