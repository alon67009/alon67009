//from:  https://www.youtube.com/watch?v=IdU6eCJ9Rh0&ab_channel=ElectronicsandProgramming


#define LDR_PIN  A2
#define LED_PIN 3
#define THRESHOLD 170                  // 1.325 V 
#define PERIOD 20

bool previous_state;
bool current_state;

//
//int R2 = 1000;
//int R1_LDR = 2880;
//float A2_Volt = R2*4.7/(R1_LDR+R2);     //4.7 is "5 volt" as input
//float TEMP_THRESHOLD = A2_Volt*(255/4.7);
//
//float THRESHOLD = 255*R2/R1_LDR;       //now is arond: 65.72

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
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN); 
 // Serial.println(voltage);
 //THRESHOLD = min(voltage, 255) + 10;
 // Serial.println(voltage);
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
