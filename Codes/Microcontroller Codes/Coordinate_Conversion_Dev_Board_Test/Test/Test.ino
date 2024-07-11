#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
#include "CoordinateConverter.h"

using namespace std;

double latitude = 5.80, longitude = 80.36;
int dd = 30, mm = 1, yy = 2024;
int hh = 13, minn = 15;
double secc = 0; 

// RA-DEC data of Sirius
double right_ascension = 6.75;
double declination = -16.72;

CoordinateConverter converter(latitude, longitude);

void setup() {
  // put your setup code here, to run once:
  converter.updateDateUTC(dd, mm, yy);
  converter.updateTimeUTC(hh, minn, secc);
  converter.update_RA_DEC(right_ascension, declination);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  converter.updateTimeUTC(hh, minn, secc);
  vector<double> alt_az = converter.convert();
  Serial.print("Seconds: ");
  Serial.print(secc);
  Serial.print("\tAltitude: ");
  Serial.print(alt_az[0]);
  Serial.print("\tAzimuth: ");
  Serial.println(alt_az[1]);
  secc++;
  delay(1000);
}
