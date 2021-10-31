#include <Adafruit_NeoPixel.h> //die Bibliothek für die Neopixel 
//#define LED_BUILTIN 
//#define LED2 12 
#define MICROPHONE 26 // Pin des Mikrophones
#define PINLED 27 // Port der LED 
#define RGBLED_POWER 16 // Pin auf welchem die LED mit Strom versorgt wird 
#define NUMPIXEL 1 // Anzahl an LEDs
#define CORRECTION 2 //Korrektur für Mikrofon 
#define MICROPHONE_POWER 28 //Strom für das Mikrofon 3.3V 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXEL, PINLED, NEO_RGB + NEO_KHZ800); //definition des Pixel Objektes 
// vint color[1][3]={{218,235,273}}; //erste Farbe (Test) 
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(9600); 
  pinMode(PINLED, OUTPUT);
  pixels.begin(); 
}

void blink(){
  for (int a = 0; a<20; a++){
    delay(100),
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
  }
}

//Variablen 
bool blinked = false;
int fade = 255; 
int red= 168;
int blue = 33;
int green = 24; 
int steprgb = 1;  
int Sum=0; 

//Steuern der LED 
void farbe(int red, int green, int blue){
  pixels.setPixelColor(0,pixels.Color(red, green, blue)); 
  pixels.show(); 
  delay(1000);
}

//gefilterter Wert vom Sensor 
int fSV(){
  int Sum=0;
  int sensorValue; 
  for(int a = 0; a<10; a++){
    sensorValue=analogRead(MICROPHONE);
    Sum = Sum+sensorValue; 
  }
  Sum = Sum/10;
  sensorValue=Sum;
  //free(&Sum); 
  return sensorValue; 
}
void farbeBar(int sensorValue, int red, int green, int blue){
  //equivalpent der Farbe Funktion fuer die multiplen LED
  #ifdef BAR 
    static bool initialized = false; 
    int LEDNumber = 10;
    Adafruit_NeoPixel pixelS = Adafruit_NeoPixel(LEDNumber, PINLED, NEO_RGB + NEO_KHZ800); 
    if(!initialized){
      pixelS.begin(); 
      initalized = true; 
    }
    if(sensorValue>720-71){ 
      for(int a=0; a<10; a++){
        pixelS.setPixelColor(a,pixelS.Color(red, green, blue)); 
      }
    }
    else if(sensorValue>720-(71*2)){
      for(int a=0; a<8; a++){
        pixelS.setPixelColor(a,pixelS.Color(red,green,blue);
      }
    }
    else if(sensorValue<720-(71*3)){
      pixelS.setPixelColor(a,pixelS.Color(red,green,blue); 
    }
    pixelS; 
  #endif 
}
void loop() {
  //igitalWrite(PINLED,HIGH); 
  int sensorValue = fSV(); //fSV 
  int minValue = 300; 
  //sensorValue=sensorValue-800;
  //sensorValue= sensorValue > 0 ? sensorValue : -sensorValue; 
  //sensorValue=sensorValue*3; 
  //static bool wasGreen=false;
  //static bool wasRed=false;
  //static bool wasBlue=false; 
  //static int lastValue; 
  //delay(10); 
  //int LEDRGB = 27; 
  sensorValue=sensorValue-minValue; 
  sensorValue = sensorValue>0 ? sensorValue : 0; 
  Serial.println(sensorValue); 
  //Serial.println(lastValue); 
  Serial.println("This is the value on the A0 port\n"); 
  //lastValue=sensorValue; 
  if(!blinked){
  for(int a = 0; a<10; a++){
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW); 
  }
  blinked = true; 
  }
  digitalWrite(RGBLED_POWER, HIGH); //Stromversorgung 
  digitalWrite(MICROPHONE_POWER, HIGH); 
  //digitalWrite(LED_BUILTIN, HIGH);
  // put your main code here, to run repeatedly:
  //delay(100);
  //digitalWrite(LED_BUILTIN, LOW); 
  //delay(100); 
  //digitalWrite(LED,HIGH);
  //delay(1000);
  //digitalWrite(LED,LOW)
  //delay(1000); 
  //analogWrite(PINLED, 255); 
  /*for(int a=255; a<10000; a++){
    analogWrite(LEDRGB,a); 
    delay(10); 
  }*/
  //analogWrite(LEDRGB,200);
  //digitalWrite(LEDRGB,280); 
  //farbe(red,green,blue); 
  //delay(10);
  //farbe(48, 29, 194);
  /*if(sensorValue<350){
    red=255;
    green=0;
    blue=0;
    if(!wasRed){
      delay(1000); 
    }
    wasRed=true; 
    wasBlue=false;
    wasGreen=false;
  }
  else if(sensorValue<670){
    red=0;
    green=255;
    blue=0;
    if(!wasGreen){
        delay(1000);
    }     
    wasRed=false;
    wasGreen=true;
    wasBlue=false;
  }
  else{  
    red=0;
    green=0;
    blue=255; 
    if(!wasBlue){
    delay(1000); 
    }
    wasRed=false;
    wasGreen=false;
    wasBlue=true; 
  }*/  
  if (sensorValue<361){  //512 ==> 0,33,255 , 0 ==> 168,33,24
    int temp = sensorValue*255/361; 
    red = 255-temp; 
    green = temp; 
    red = red > 0 ? red : 0; //ist Rot groeßer Null, wenn nein, ist es Null 
    blue=0; 
  }
  else{
    int temp = (sensorValue-361) * 255/361; ; 
    red=0; 
    green = 255-temp/2;
    blue = temp/2; 
    green = green > 0 ? green : 0; //ist Gruen groeßer als Null, wenn nein, ist es Null 
    //Serial.println(blue);  
    }
  farbe(red,green,blue); 
  //delay(100);
  //red = 168;
  //blue = 33;
  //green = 24; 
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000);
  //digitalWrite(LED_BUILTIN, LOW);  
}
