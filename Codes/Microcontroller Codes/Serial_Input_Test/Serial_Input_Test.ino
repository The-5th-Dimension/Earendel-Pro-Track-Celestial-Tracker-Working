#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <string>

#define Serial_INT 2

using namespace std;

struct data
{
    string type;
    double value1, value2, value3;
};

data decode(char *input)
{
    data inputData;

    char delim = ' ';
    char *delimPtr = &delim;

    char *token = strtok(input, delimPtr); // This will be the type of data. e.g.: DATE, TIME, GPS, RADEC

    inputData.type = token;

    token = strtok(NULL, delimPtr); // The next part of the data.

    if (inputData.type == "DATE")
    {
        *delimPtr = '.';
    }
    else if (inputData.type == "TIME")
    {
        *delimPtr = ':';
    }
    else if (inputData.type == "GPS" || inputData.type == "RADEC")
    {
        *delimPtr = ',';
    }

    token = strtok(token, delimPtr); // Start extracting actual data values.

    inputData.value1 = atof(token);
    token = strtok(NULL, delimPtr);
    inputData.value2 = atof(token);
    token = strtok(NULL, delimPtr);
    inputData.value3 = atof(token);

    return inputData;
}

// Variables to be updated based on the Serial data from the ESP32.
volatile int year = 2000, month = 1, day = 1, hour = 12, minute = 0;
volatile double second = 0;
volatile double latitude = 0, longitude = 0;
double ra = 0, dec = 0;
bool valuesUpdated = true;

// Local coordinate values.
double altitude = 0, azimuth = 0;

// Function Declarations
void handleSerial();
void autoUpdateTime();

void setup()
{
  Serial.begin(115200);
  // Maybe need to add some initial delay to get the initial data from the ESP32 in the setup.

  pinMode(Serial_INT, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(Serial_INT), handleSerial, RISING);

  autoUpdateTime();
}

void loop()
{
  handleSerial();

  Serial.print(year);
  Serial.print('.');
  Serial.print(month);
  Serial.print('.');
  Serial.print(day);
  Serial.print('\t');

  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);
  Serial.print('\t');

  Serial.print(latitude);
  Serial.print(", ");
  Serial.print(longitude);
  Serial.print('\t');
  
  Serial.print(ra);
  Serial.print(", ");
  Serial.print(dec);
  Serial.println();

  delay(100);
}

// Function Definitions
void handleSerial()
{
  data inputData;

  // Set `valuesUpdated` to true after any change.
  if (Serial.available())
  {
    const int buffSize = 50;
    char input[buffSize];
    Serial.readStringUntil('\n').toCharArray(input, buffSize);
    inputData = decode(input);

    if (inputData.type == "DATE") {
      day = (int) inputData.value1;
      month = (int) inputData.value2;
      year = (int) inputData.value3;
    }
    else if (inputData.type == "TIME") {
      hour = (int) inputData.value1;
      minute = (int) inputData.value2;
      second = inputData.value3;
    }
    else if (inputData.type == "GPS") {
      latitude = inputData.value1;
      longitude = inputData.value2;
    }
    else if (inputData.type == "RADEC") {
      ra = inputData.value1;
      dec = inputData.value2;
    }
  }  
}

void autoUpdateTime()
{
  // The following are internal registers in ATmega328.
  // Internal interrupts (Timers) are used to keep track of time precisely.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 3036;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
}

ISR(TIMER1_OVF_vect)
{
  second += 1;
  if (second == 60)
  {
    second = 0;
    minute += 1;
  }
  if (minute == 60)
  {
    minute = 0;
    hour += 1;
  }
  if (hour == 24)
  {
    hour = 0;
    day += 1;
  }
  // This should be extended to work well with month and year boundaries.
  // e.g.: Update from 30th June to 1st of July.
  // However, let's assume this is enough for demonstration.

  // Setting back to 3036, otherwise it starts back from 0.
  TCNT1 = 3036;
}