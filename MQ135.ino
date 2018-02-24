int sensorValue;

int digitalValue;

void setup()

{

  Serial.begin(9600);      // sets the serial port to 9600

 // pinMode( A, INPUT);
  pinMode(0, INPUT);

}




void loop()

{

  sensorValue = analogRead(0);       // read analog input pin 0

  digitalValue = digitalRead(0); 

  Serial.println("The value of air quality:");
  Serial.println(sensorValue, DEC);  // prints the value read

  Serial.println(digitalValue, DEC);

  delay(2000);                        // wait 100ms for next reading

}
