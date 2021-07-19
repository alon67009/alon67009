//from:  https://www.youtube.com/watch?v=IdU6eCJ9Rh0&ab_channel=ElectronicsandProgramming


#define LED_PIN  A1
#define BUTTON_PIN A0  
#define PERIOD 25

char* string = "This is a test transmission \n";
int string_length;


void setup() 
{
//    Serial.begin(9600);
    pinMode(LED_PIN,OUTPUT);
    pinMode(BUTTON_PIN,INPUT_PULLUP);
    string_length = strlen(string);
}

void loop()
{
  for( int i=0 ; i<string_length ; i++ )
  {
    send_byte(string[i]);
//    Serial.print("i: ");
//    Serial.println(i);
//    Serial.print("string[i]: ");
//    Serial.println(string[i]);

  }
  delay(1500);
}

void send_byte(char my_byte)
{
  digitalWrite(LED_PIN,LOW);
  delay(PERIOD);

  for(int i=0 ; i<8 ; i++)
  {
      digitalWrite(LED_PIN, (my_byte&(0x01<<i))!=0);
      Serial.println( (my_byte&(0x01<<i))!=0);
      delay(PERIOD); 
  }
  digitalWrite(LED_PIN,HIGH);
  delay(PERIOD);
}
