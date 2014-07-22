int pin=10;
volatile int state=LOW;
float trip_duration = 0;
float start_time = 0;
boolean alarm_deactivated = false;
//boolean start_count = true;
//counts how long the system has been tripped for
//if it is tripped for a sufficiently short amount of time, 

void setup(){
pinMode(pin,OUTPUT);
// parameter1 - interrupt (0 or 1)
// parameter2 - name of the interrupt handler function 
// parameter3 - trigger(CHANGE,LOW,RISING or FALLING)
attachInterrupt(0,button_press,CHANGE);
Serial.begin(9600);
}

void loop(){
  //start_count = true;
  start_time = millis();
  trip_duration = 0;
  alarm_deactivated = false;
  
  while((state == HIGH) && (alarm_deactivated == false)){
    /*if (start_count == true){
      start_time = millis();
      start_count = false;
    }*/
    trip_duration = millis() - start_time;
    if(trip_duration > 2000){
        //trigger alarm
        //Rest of code goes
        Serial.println("Alarm has been tripped");
    }
    
    
  }
}
// interrupt handler function 
void button_press(){
state = !state;
}

