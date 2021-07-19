//from:  https://www.youtube.com/watch?v=IdU6eCJ9Rh0&ab_channel=ElectronicsandProgramming


#define LDR_PIN  A2
#define LED_PIN 3
#define THRESHOLD 66
#define PERIOD 50

bool previous_state;
bool current_state;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  
  current_state = get_ldr();
  if(!current_state && previous_state)
  {
      print_byte(get_byte());
      digitalWrite(LED_PIN, HIGH);
  }
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;     // what "? true : false" means?????
}

char get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for( int i=0; i<8; i++ )
  {
   ret = ret | get_ldr() << i ;         // "<<" mean shifted by i
   delay(PERIOD);
  }
  return ret;
}

void print_byte(char my_byte)
{
  char buff[2];
  sprintf(buff, "%c", my_byte);
  Serial.print(buff);
  
}
