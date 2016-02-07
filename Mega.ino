
//needed Libraries
#include <SdFat.h>
#include <UTFT.h>    //TFT
#include <RCSwitch.h>
#include <UTouch.h> //Touch
#include <OneWire.h>  // needed for RelaisBreakout (I2C)
#include <DallasTemperature.h> //needed for Temp
#include <Wire.h>  // Wire.h library is required to use SX1509 lib
#include <sx1509_library.h>  // Include the SX1509 library
#include "RTClib.h"
#define ONE_WIRE_BUS 10 //needed for Temperature
#include <EEPROM.h>  // used to store and retrieve settings from memory
#include <tinyFAT.h> // used to acess the SD card
#include <UTFT_SdRaw.h>  // used to read .raw images from the SD card
#include <avr/wdt.h>

/*     

 

 Read char value from Serial Monitor
 Display that value on the Serial Monitor
 */

boolean debugging=0;

//** the testvariables
String testString = "Test";
int testInt = 786;
float testFloat = 8.9;
byte testByte = 23;
boolean testBoolean = true;
DateTime testDateTime;




      
String StringFromSerial;

void setup()
{
  Serial.begin(115200);     
  Serial2.begin(115200);     
  Serial.println("Serial Monitor Connected");  
  printMyValues();
  Serial.println("DataForYou|test1|testDateTime_1454873609|test3|");
  Serial.println("DataforMe|test1|teststring_ThisTest|test3|");
}

void printMyValues()
  {if(debugging)
      {
        Serial.print("testString : ");
        Serial.println(testString);  
        Serial.print("testInt : ");
        Serial.println(testInt);  
        Serial.print("testFloat : ");
        Serial.println(testFloat);  
        Serial.print("testByte : ");
        Serial.println(testByte);  
        Serial.print("testBoolean : ");
        Serial.println(testBoolean);  
        Serial.print("testDateTime : ");
        Serial.print(testDateTime.hour(), DEC);
        Serial.print(':');
        Serial.print(testDateTime.minute(), DEC);
        Serial.print(':');
        Serial.print(testDateTime.second(), DEC);
        Serial.print(' ');
        Serial.print(testDateTime.day(), DEC);
        Serial.print('.');
        Serial.print(testDateTime.month(), DEC);
        Serial.print('.');
        Serial.println(testDateTime.year(), DEC);
      }
  }



void loop() 
{
    if(Serial2.available())
    {
        char charFromSerial = Serial2.read();
        if (charFromSerial == '\n')
          {parseCommand(StringFromSerial);
            StringFromSerial="";
          }
          else
          {
            StringFromSerial += charFromSerial;
          }
        
    
    }
    
    
}

void parseCommand(String com)
{ 
String part1;
 // part1 = com.substring(0, com.indexOf("|"));
  if(com.substring(0, com.indexOf("|")).equalsIgnoreCase("DataForYou"))
    {
    for(int i=com.indexOf("|"); i<com.lastIndexOf("|"); i=com.indexOf("|",i+1))
     {String part1 = com.substring(i+1, com.indexOf("|",i+1));
      //____________________________________________________________________________________________________use this to parseStrings
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("teststring"))
      {
        testString=part1.substring(part1.indexOf("_")+1,part1.length());
        printMyValues();
      }
      //____________________________________________________________________________________________________use this to parseInts
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testInt"))
      {
        testInt=(part1.substring(part1.indexOf("_")+1,part1.length())).toInt();
        printMyValues();
      }      
      //____________________________________________________________________________________________________use this to parseFloats
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testFloat"))
      {
        testFloat=(part1.substring(part1.indexOf("_")+1,part1.length())).toFloat();
        printMyValues();
      }    
       //____________________________________________________________________________________________________use this to parseByte
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testByte"))
      {
        testByte=(part1.substring(part1.indexOf("_")+1,part1.length())).toInt();
        printMyValues();
      }  
       //____________________________________________________________________________________________________use this to parseBoolean
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testBoolean"))
      {
        testBoolean=(part1.substring(part1.indexOf("_")+1,part1.length())).toInt();
        printMyValues();
      }  
       //____________________________________________________________________________________________________use this to parseByte
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testBoolean"))
      {
        testBoolean=(part1.substring(part1.indexOf("_")+1,part1.length())).toInt();
        printMyValues();
      }  
       //____________________________________________________________________________________________________use this to parsDateTime in Seconds unixtimne!
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testDateTime"))
      {
        char arr[12];
        (part1.substring(part1.indexOf("_")+1,part1.length())).toCharArray(arr, sizeof(arr));
        testDateTime=atol(arr);
        printMyValues();
      }  
    }
    }
  else  if(com.substring(0, com.indexOf("|")).equalsIgnoreCase("DataForMe"))
    {
    for(int i=com.indexOf("|"); i<com.lastIndexOf("|"); i=com.indexOf("|",i+1))
     {String part1 = com.substring(i+1, com.indexOf("|",i+1));
      //____________________________________________________________________________________________________use this to parseStrings
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("teststring"))
      {
        sendCommand(testString);
      }
      //____________________________________________________________________________________________________use this to parseInts
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testInt"))
      {
        sendCommand(String(testInt));
      }      
      //____________________________________________________________________________________________________use this to parseFloats
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testFloat"))
      {
        sendCommand(String(testFloat));
      }    
       //____________________________________________________________________________________________________use this to parseByte
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testByte"))
      {
        sendCommand(String(testByte));
      }  
       //____________________________________________________________________________________________________use this to parseBoolean
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testBoolean"))
      {
        sendCommand(String(testBoolean));
      }  
       //____________________________________________________________________________________________________use this to parsDateTime in Seconds unixtimne!
      if(part1.substring(0, part1.indexOf("_")).equalsIgnoreCase("testDateTime"))
      {        sendCommand(String(testDateTime.unixtime()));
      }  
    } 
    }

  else
   {
    Serial.println(com);
   }
  
}




void sendCommand(String sendCom)
{
  String sendThis = sendCom + "| \n" ;
   char charBuf[100];
   sendThis.toCharArray(charBuf, 100);
   Serial.write(charBuf);
}


