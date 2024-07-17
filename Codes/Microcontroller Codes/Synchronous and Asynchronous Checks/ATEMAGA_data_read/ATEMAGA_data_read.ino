#define STEP_PIN 4
#define DIR_PIN 5

String readString;

unsigned long lastStepTime = 0;
const unsigned long stepInterval = 30; // Adjust this value based on your requirements

void setup() {
  Serial.begin(115200);

  // Set STEP and DIR pins as OUTPUT for both steppers
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      // Newline character encountered, print the received string
      if (readString.length() > 0) {
        Serial.println(readString);
        readString = "";
      }
    } else {
      // Append the character to the string
      readString += c;
    }
  }

  if (readString == "step") {
    Serial.println("Triggered!");
    Step(1, true);
  }
}

void Step(int count, bool direction) {
  digitalWrite(DIR_PIN, direction);

  for (int x = 0; x < count; x++) {
    unsigned long currentTime = millis();

    if (currentTime - lastStepTime >= stepInterval) {
      lastStepTime = currentTime;

      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(500); // You may need to fine-tune this delay
      digitalWrite(STEP_PIN, LOW);
    }
  }
}
