#define INT 40

int year = 2024, month = 3, day = 18, hour = 18, minute = 27;
double second = 10;
double latitude = 5.36, longitude = 82.84;
double ra = -6.34, dec = 3.55;

void giveInterrupt() {
  digitalWrite(INT, LOW);
  delayMicroseconds(10);
  digitalWrite(INT, HIGH);
  delayMicroseconds(10);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(INT, OUTPUT);

  digitalWrite(INT, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("DATE " + String(day) + '.' + String(month) + '.' + String(year) + '\n');
  giveInterrupt();
  delay(2000);

  Serial.print("GPS " + String(latitude) + ',' + String(longitude) + '\n');
  giveInterrupt();
  delay(2000);

  Serial.print("RADEC " + String(ra) + ',' + String(dec) + '\n');
  giveInterrupt();
  delay(2000);

  year += 2;
  month += 3;
  if (month > 12) {
    month = 1;
  }

  day += 5;
  if (day > 31) {
    day = 1;
  }

  latitude -= 1.456;
  if (latitude < -90) {
    latitude = 65;
  }

  longitude *= 1.05;
  if (abs(longitude) > 180) {
    longitude = 0;
  }

  ra -= 0.5;
  dec += 1.9;
}
