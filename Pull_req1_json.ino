//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Variables
//float hum;
//float temp;
const char* ssid = "Redmi4AR";
const char* password = "17mcs0024";

void setup()
{
    //Serial.begin(9600);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("\nConnecting..");
    }

     //DynamicJsonBuffer jsonBuffer(200);

     void jsonParser(String);
     
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        String url = "http://xlr8hub.com/api/weather/last.php";
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode > 0)
        {
            String payload = http.getString();
            jsonParser(payload);
            //Serial.println(payload);
        }
        http.end();
    }

    delay(10000);
}


void jsonParser(String payload)
{
    DynamicJsonBuffer jsonBuffer;
    String json = payload;
      //"{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(json);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root["time"].as<long>();
  //const char* sucess = root["weather"];
  //int id = root["id"];
  int succ = root["success"];
  char* r1=root["weather"];
  char r2[strlen(r1)-2] ;
  int ctr=0, i ;
  for(i=0;i<strlen(r1);i++)
  {
    if((r1[i]!="[")||(r1[i]!="]"))
    {
      r2[ctr++]=r1[i];
    }
  }
  JsonObject& root1 = jsonBuffer.parseObject(r2);
  int id = root1["id"];
  int temp = root1["temp"];
  int hum = root1["hum"];

  // Print values.
  Serial.println(json);
  Serial.println(r1);
  Serial.println(r2);
  Serial.println(succ);
  Serial.println(id);
  Serial.println(temp);
  Serial.println(hum);

  
  /*
  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);*/
}

   
