#include <MFRC522.h> //library responsible for communicating with the module RFID-RC522
#include <SPI.h> //library responsible for communicating of SPI bus
#include <BleKeyboard.h>
#define SS_PIN 21
#define RST_PIN 22

String readid;
String cardid="cardid";
MFRC522 mfrc522(SS_PIN, RST_PIN);
BleKeyboard bleKeyboard;

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    bleKeyboard.begin();
    mfrc522.PCD_Init();
}

void temp(byte *buffer, byte bufferSize)//function to store card uid as a string datatype.
{
  readid="";
  for(byte i = 0;i<bufferSize; i++)
  {
    readid=readid+String(buffer[i], HEX);
  }
}

void loop( ) 
{
 if(!mfrc522.PICC_IsNewCardPresent())
 {
  return;
 }
 if(!mfrc522.PICC_ReadCardSerial()) 
 {
  return;
 }
 mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // Display card details in serial Monitor.
 temp(mfrc522.uid.uidByte, mfrc522.uid.size);

// Serial.print(readid);
 
 if(readid==cardid)
 { 
   Serial.println("Card allowed");
   if(bleKeyboard.isConnected()) 
   {
    Serial.println("Connected");
    bleKeyboard.print("p");
    delay(100);
    bleKeyboard.print("a");
    delay(100);
    bleKeyboard.print("s");
    delay(100);
    bleKeyboard.print("s");
    delay(100);
    bleKeyboard.print("w");
    delay(100);
    bleKeyboard.print("o");
    delay(100);
    bleKeyboard.print("r");
    delay(100);
    bleKeyboard.print("d");
    delay(100);
    bleKeyboard.write(KEY_RETURN);
   }
   delay(1000);
 }
 else
 {
  Serial.println("Card not allowed");
  return;
 } 
}
