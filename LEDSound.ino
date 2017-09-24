const int SoundSensorSignalPin = A0;
const int numReadings = 100;
const int redLED = 11;
const int greenLED = 10;
const int blueLED = 9;

int sensorReading[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;
int previousAverage = 0;  // the average
int derivative = 0;


void setup() {
    pinMode(SoundSensorSignalPin, INPUT);
    pinMode (redLED, OUTPUT);
    //pinMode (greenLED, OUTPUT);
    pinMode (blueLED, OUTPUT);
    Serial.begin(9600);
    
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    sensorReading[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - sensorReading[readIndex];
  // read from the sensor:
  sensorReading[readIndex] = analogRead(SoundSensorSignalPin) + 150;
  // add the reading to the total:
  total = total + sensorReading[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;

  // calculate the average:
  average = total / numReadings;
  derivative = average - previousAverage;
  if(abs(derivative) < 20)
  {
    derivative = 0;
  }
  else if(derivative < -50)
  {
    digitalWrite(redLED, HIGH);
    //digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  else if(derivative > 50)
  {
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
    //digitalWrite(greenLED, LOW);
  }
//  else
//  {
//    digitalWrite(greenLED, HIGH);
//    digitalWrite(blueLED, LOW);
//    digitalWrite(redLED, LOW);
//  }
  Serial.println(derivative);
  
  // send it to the computer as ASCII digits
  // Serial.println(map(abs(average), 0, 300, 0, 255));
  
  previousAverage = average;
  delay(10);        // delay in between reads for stability
  }
}
