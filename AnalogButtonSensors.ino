int sensorValSwitch = 0;
int proceedSwitch = 1;
float voltage = 0;
int interruptPin2 = 0;
int passCode [] = {1,1,2,3};
int userGuess[4];
int digitCounter = 0; //Counter to keep track of how many input digits have been inputted
boolean switchState = true;

void setup(){	
	attachInterrupt(interruptPin2,swtichInterrupt,RISING);
	Serial.begin(9600);
}

void swtichInterrupt(){
	switchState = true;
}

void loop(){
	runCheck();
	//Check against passCode
}

void runCheck(){
	// Serial.println("Running Check...");
	while(digitCounter != 3){		
		int sensorVal = analogRead(sensorValSwitch);		
		// Serial.println(sensorVal);		

		//Button is Pushed (sensorVal != 0) AND User wants to proceed (proceed != 0)
		if ((sensorVal != 0) && (switchState == true)){			

			//Get our Voltage to work with...
			voltage = sensorVal * (5/1023);
			// Serial.println(voltage);

			//Get the user input voltage
			matchVoltage(voltage);
			switchState = false;	
		}		
	}
}

void matchVoltage(float voltage){
	Serial.println("Matching Voltage...");
		if ((voltage >= 4.84) && (voltage <= 4.90)){
			userGuess[digitCounter] = 0;	
		}
		
		else if ((voltage >= 4.69) && (voltage <= 4.72)){
			userGuess[digitCounter] = 1;
		}	

		else if ((voltage >= 3.87) && (voltage <= 3.90)){
			userGuess[digitCounter] = 2;
		}			

		else if ((voltage >= 3.14) && (voltage <= 3.16)){
			userGuess[digitCounter] = 3;
		}

		else if ((voltage >= 4.95) && (voltage <= 4.98)){
			userGuess[digitCounter] = 4;
		}

		else if ((voltage >= 4.55) && (voltage <= 4.58)){
			userGuess[digitCounter] = 5;
		}

		Serial.print("User guess is: ");
		Serial.println(userGuess[digitCounter]);

		digitCounter ++; //Increment digit guess				
}