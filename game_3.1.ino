//Every success in the game leads to an increase in level
//Every five successes in the game leads to an increase in the stage

#include <FastLED.h>
#include <math.h>

#define LED_TYPE  WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 60
#define LED_PIN 3
#define Color_Run_Led Red
#define Constant_Led 0
#define Start_speed 100
#define BRIGHTNESS 70

int buttonPin = 2;
int buttonState = 0;
int n;
int Level = 1;
int stage = 1;
int Mistake_Counter = 1;            //Mistake_Counter = 1  means ther is full life 
int High_Level;
int Running_Led;
int Speed = Start_speed;

unsigned long initial_time; 
unsigned long current_time;


 
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  Serial.print("Hi"); 
  Serial.print("\n");  
  
  delay(3000);
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  for (Running_Led = 0; Running_Led < NUM_LEDS; Running_Led++)
  {
    // const for loop game
    leds[Constant_Led] = CRGB::White;
    leds[Running_Led] = CRGB::Color_Run_Led;
    FastLED.show();
    leds[Running_Led] = CRGB::Black;

    initial_time = millis();
    current_time = millis();
    
    while (current_time - initial_time <= Speed)
    {
      buttonState = digitalRead(buttonPin);
      current_time = millis();
      if (buttonState) 
      {
        post_click_response_Lowering_Levels_And_Speeds();
        break;
      }   
//      unsigned long end_time = millis();
//      Serial.print("  Meas.Dealy.func: ");
//      Serial.print(end_time-initial_time);
//      Serial.print("\t");
//      Serial.print("Req.Dealy.func: ");
//      Serial.print(Speed);                 
//      Serial.print("\n");
    }
  }
}

void post_click_response_Lowering_Levels_And_Speeds()
{
  if (Running_Led == Constant_Led)          //Success 
  {
    //Speed = Start_speed * pow (0.9, (Level-1)); 

    leds[Running_Led] = CRGB::Green;           //Shows the user that he has Success 
    FastLED.show();
    delay(1000);

    //Success ();

    if ((Level) % 5 == 0)                //evry 5 levels --> Big Success Festival
    {
      color_palette_faded_cylon();
      Mistake_Counter = 1;                  //up stage
    }

    else
      Success_Festival();

    FastLED.clearData();
    Running_Led = (NUM_LEDS / 2 + Constant_Led) % NUM_LEDS; //start again from the middle
    Level++;
    if (Level > High_Level)                 //showing the highest level since the game was on  
      High_Level = Level;
    Speed = Speed * 0.9;
  }

  else
    //Mistake 
  {
    if (Level < 6)                      //Mistake in the beginning levels 
    {
      Fatal_Mistake();                     //Shows the user that the game is --over--
      FastLED.clearData();

      Shows_level(Level);
      StandBy();
      FastLED.clearData();

      Running_Led = (NUM_LEDS / 2 + Constant_Led) % NUM_LEDS;
      Level = 1;
      Speed = Start_speed;
      return;
    }

    if (Mistake_Counter == 3)                   //The --Third mistake-- good bay
    {
      Fatal_Mistake();                  //Shows the user that he was --wrong--  
      //FastLED.clearData();
      Shows_Mistake_Counter();
      Shows_level(Level);             //show the user the level thet he hes reached
      StandBy();
      FastLED.clearData();

      Shows_level(High_Level);        //show the user the highest level since the game was on
      StandBy();
      FastLED.clearData();

      Running_Led = (NUM_LEDS / 2 + Constant_Led) % NUM_LEDS;
      Level = 1;
      Speed = Start_speed;
      Mistake_Counter = 0;
      return;
    }

    else
      //Mistake after the fifth level
      Mistake();
    FastLED.clearData();

    Shows_level(Level);
    Shows_Mistake_Counter();
    StandBy();
    FastLED.clearData();

    Running_Led = (NUM_LEDS / 2 + Constant_Led) % NUM_LEDS;
    Mistake_Counter++;

  }
}

 void Mistake()
{
  //Shows the user where he has Mistake
  leds[Running_Led] = CRGB::Color_Run_Led;
  FastLED.show();
  delay(1000);

  for (n = 0; n < NUM_LEDS; n++)
  {
    leds[(Running_Led + n) % NUM_LEDS] = CRGB::Red;
    FastLED.show();
    delay(20);
  }
}

void Fatal_Mistake()
{
  int  i;
  //Shows the user where he has Mistake
  leds[Running_Led] = CRGB::Color_Run_Led;
  FastLED.show();
  delay(1000);

  for (i = 0; i < 3; i++)
  {
    for (n = 0; n < NUM_LEDS; n++)
      leds[(Running_Led + n) % NUM_LEDS] = CRGB::Red;
    FastLED.show();
    delay(500);
    for (n = 0; n < NUM_LEDS; n++)
      leds[(Running_Led + n) % NUM_LEDS] = CRGB::Black;
    FastLED.show();
    delay(300);
  }
}

void Success_Festival()
{
  for (n = 0; n < NUM_LEDS; n++)
  {
    leds[n] = CRGB::Green;
    FastLED.show();
    delay(10);
  }
}

void color_palette_faded_cylon()
{
  static uint8_t hue = 0;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS * 7; i++)
  {
    // Set the i'th led to red 
    leds[i % NUM_LEDS] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black 
    //in that case i can shot down the 'fadeall'       
/*
leds[i % NUM_LEDS] = CRGB::Black;
*/
//also this 'for' can be in function by name: fadeall()
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i].nscale8(240);


    // Waiting to see the beautiful colors
    delay(7);
  }
}

void Shows_level(int Temp)
{
  for (n = 0; n < Temp; n++)
  {
    leds[(NUM_LEDS / 2 + Constant_Led) % NUM_LEDS + n] = CRGB::Orange;
    FastLED.show();
    delay(100);
  }
}

void Shows_Mistake_Counter()
{
  for (n = 0; n < Mistake_Counter; n++)
  {
    leds[(NUM_LEDS / 2 + Constant_Led) % NUM_LEDS - 1 - n] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
}

void StandBy()
{
  int i = 1;
  //As long as the value for 'buttonState' doesn't change 
  //you will remain on hold ( while keep Repeat itself )
  while (i)
  {
    // user pressed the button --> stop the StandBy
    buttonState = digitalRead(buttonPin);
    // For good button read results do not cross delay of 10 m/s
    delay(10);

    if (buttonState)
      i = 0;
  }
  //user keep press the button --> don't continue the game 
  while (digitalRead(buttonPin))
    delay(100);
}
