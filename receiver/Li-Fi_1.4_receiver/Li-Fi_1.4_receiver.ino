

#define LDR_PIN  A2
#define LED_PIN 3
#define PERIOD 6
#define THRESHOLD 250

#define voltage_flag 0
#define led_flag 1

bool previous_state;
bool current_state;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
}

void loop()
{
  current_state = get_ldr();
  if(!current_state && previous_state)
  {
      print_byte(get_byte());
      //digitalWrite(LED_PIN, HIGH);
  }
  if(led_flag)
  {
    digitalWrite(LED_PIN, LOW);
  }
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  if (voltage_flag)
  {
    Serial.print("voltage is: ");
    Serial.println(voltage);
  }
  return voltage > THRESHOLD ? true : false;
}

char get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for( int i=0; i<8; i++ )
  {
   ret = ret | get_ldr() << i ;
   if(led_flag)
   {
      digitalWrite(LED_PIN, HIGH);
   }
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
