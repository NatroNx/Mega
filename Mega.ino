#include "RTClib.h"


/*     
 For more details see: http://projectsfromtech.blogspot.com/
 

 Read char value from Serial Monitor
 Display that value on the Serial Monitor
 */



//** the testvariables
String testString = "Test";
int testInt = 786;
float testFloat = 8.9;
byte testByte = 23;
boolean testBoolean = false;
DateTime testDateTime = now.unixtime();



//** the testvariables

String StringFromSerial;

void setup()
{
  Serial.begin(115200);     
  Serial2.begin(115200);     
  Serial.println("Serial Monitor Connected");  
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
  Serial.println(testDateTime);
  

  
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
{ String part1;
part1 = com.substring(0, com.indexOf("|"));
  if(part1.equalsIgnoreCase("test10"))
  {
    Serial.println("This was successful");
    sendCommand("ACK");
    }
  else if (part1.equalsIgnoreCase("givemillis"))
  {
    Serial.println(millis());
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
   Serial2.write(charBuf);
}


