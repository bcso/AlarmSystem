const int interrupt = 2;
const int speaker_pin = 8;              //***speakerConnectionNumber***
const int led_pin = 9;                  //***LEDConnectionNumber***
float duration = 0;
volatile float start_time = 0;
volatile float end_time = 0;
volatile boolean false_alarm_count = 0;

boolean unlock = 0;

long current_time = 0;
int led_state = LOW;
long previous_time = 0;
long interval = 500;


void setup()
{
  pinMode(interrupt, INPUT);
  pinMode(speaker_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, interrupted, FALLING);
  attachInterrupt(0, back_to_usual, RISING);
  Serial.println("No interruptions");
}

void loop()
{
  duration = start_time - end_time;                  //************
  
  if (duration >= 2000){
    
    while(unlock == 0){
      
      false_alarm_count = 0;
      
      current_time = millis();                      //************
      if (current_time - previous_time >= interval){                //***************
      
      previous_time = current_time;                    //*************
      if (led_state == LOW){
        led_state = HIGH;
        tone(speaker_pin,500);
      }
      else {
        led_state = LOW;
        noTone(speaker_pin);
      }
        
      digitalWrite(led_pin, led_state);
    }
      Serial.println("Intruder Alert!!");
      
      //unlock = button_sequence();
    }
    noTone(speaker_pin);
    digitalWrite(led_pin, LOW);
  }
  else {
    if (false_alarm_count == 0){
      Serial.println("Interrupted but no intruder");
      Serial.println("No interruptions");
      false_alarm_count = 1;
    }
  }
  
  //duration = 0;
}

void interrupted()
{
  start_time = millis();
}

void back_to_usual()
{
  end_time = millis();
  false_alarm_count = 0;
}
