//Libraries
#include "arduino.h"
#include <DHT.h>;

//Constants
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
const int mqPin_7d = 3 ;
const int mqPin_135d = 4 ;
const int mqPin_7 = A0 ;
const int mqPin_135 = A1 ;

//Variables
float co ;
float air ;
float temp ;
float hum ;
String transmissionData ;
int i ;

void setup()
{
    Serial.begin(115200); 
    dht.begin();
    pinMode(mqPin_7d, INPUT);
    pinMode(mqPin_135d, INPUT);
    pinMode(mqPin_7, INPUT);
    pinMode(mqPin_135, INPUT);
    
}

void loop()
{
    Serial.println("\n\n-------New Reads-------");
    //Digital Reads
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print Reads
    Serial.print("\nHumidity: ");
    Serial.print(hum);
    Serial.print("\nTemperature: ");
    Serial.print(temp);

    //Analog Reads
    co = analogRead(mqPin_7);
    delay(700) ;
    air = analogRead(mqPin_135);
    //Print Reads
    Serial.println("\nCO: ");
    Serial.println(co) ;
    Serial.println("Alcohol: ");
    Serial.println(air) ;
    delay(1000) ;
/*
    //Transmit Data
    Serial.println("\nTransmission Data: ") ;
    transmissionData="temp=" + String(temp) + "&hum=" + String(hum) + "&co=" + String(co) + "&nh3=" + String(air) ;
    i = transmissionData.length() ;*/
    Serial.write(transmissionData.length());
    
    /*
    for(i=0;i<transmissionData.length();i++)
    {
        Serial.println(transmissionData[i]) ;
        Serial.write(transmissionData[i]);
    }*/

    //Delay Cycle
    delay(5000) ;
}
