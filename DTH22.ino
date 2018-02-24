//Code Sample for transmitting DHT22 readings to PulseOverwatch server using ESP8266
//Author: Dipanjan
//You're free to use/change/modify/reproduce this code for personal/commercial purposes without consent

//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>;

//Constants
#define DHTPIN 1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


//Variables
float hum;
float temp;
const char* ssid = "Redmi4AR";
const char* password = "17mcs0024";

void setup()
{
    //Your baud rate may be different, like 9600. Change it in case.
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    dht.begin();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("\nConnecting...");
    }
}

void loop()
{
    //Storing temperature and humidity data from DHT22
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Displaying the data in serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    //Don't remove or decrease this delay, sometimes ESP8266 needs 2 seconds delay to re-initiate http requests
    delay(2000);

    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
  //Replace ##YourNodeID## with the Node ID generated in the website
        String url = "http://overwatch.pulseflare.com/api/weather/insert.php?nid=5a7ebef524658&temp=" + String(temp) + "&hum="+ String(hum);
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode > 0)
        {
      //Check return JSON payload
            String payload = http.getString();
            Serial.println(payload);
        }
        http.end();
    }
    //You should NOT decrease this below 2 seconds (2000) or the server might crash, you might increase it though
    delay(2000);
}

   
