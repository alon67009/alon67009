// from https://onlineasciitools.com/generate-ascii-characters
// test output char

#define LED_PIN  A1 
#define PERIOD 6

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  //string_length = strlen(string);
}

void loop()
{
  Serial.print("Please enter your sentence");
    // read value to string sentence
  String sentence = Serial.readString();
    // check the length of the string
  int string_length = sentence.length();
    // did Serial.readString() read any data? if no keep trying
  while (string_length == 0)
  {
    sentence = Serial.readString();
    string_length = sentence.length();
  }
  Serial.println("Please enter your sentence");
    // declaring character array
  char char_array[string_length + 1];
    // copying the contents of the string to char array
  strcpy(char_array, sentence.c_str());
  
    //  ---output---
  Serial.print("Your sentence is: ");
    //print the contents of the sentence (in string, at once)
  //Serial.println(sentence);
    //print the contents of the sentence (char by char)
  for (int i = 0; i < string_length; i++)
  {
    Serial.print(char_array[i]);
  }
    // let the user read and understand the sentence he write
  delay(1500);
  
    //send char by char to send_byte function   
  for( int i=0 ; i<string_length ; i++ )
  {
    send_byte(char_array[i]);
  }
}

  //convert char to a pulse signal
  //more information
void send_byte(char my_byte)
{
  digitalWrite(LED_PIN,LOW);
  delay(PERIOD);

  for(int i=0 ; i<8 ; i++)
  {
    digitalWrite(LED_PIN, (my_byte&(0x01<<i))!=0);
    Serial.print( (my_byte&(0x01<<i))!=0);
    delay(PERIOD); 
  }
  Serial.print("\n");
  digitalWrite(LED_PIN,HIGH);
  delay(PERIOD);
}
