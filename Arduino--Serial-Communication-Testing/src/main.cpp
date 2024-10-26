#include <Arduino.h>


const int REFERENCE_NUMBER{0b10101010};
const int DATA_PIN{13};
const int BAUD_RATE{500}; // Baud rate in milliseconds
const bool writeMode{false}; // If true, than write mode. If false, then read mode.

void transmitDataViaDigitalPin(int value, int pin, int baudRate);
int readDataViaDigitalPin(int pin, int baudRate);


void setup() {
  Serial.begin(9600);
  Serial.println("Hello, world");

  if(writeMode) {
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(DATA_PIN, HIGH);
    return;
  }
  
  // Read Mode;
  pinMode(DATA_PIN, INPUT);
}

void loop() {
  // Write Mode
  if(writeMode) {
    transmitDataViaDigitalPin(REFERENCE_NUMBER, DATA_PIN, BAUD_RATE);
    delay(BAUD_RATE * 10);
    return;
  }
  
  // Read Mode
  if(digitalRead(DATA_PIN) == HIGH) { return; }
  int n = readDataViaDigitalPin(DATA_PIN, BAUD_RATE);
  Serial.print("Number: ");
  Serial.println(n);
}

int readDataViaDigitalPin(int dataPin, int baudRate) {
  delay(baudRate);
  int result{0};
  
  for(int i{0}; i < 8; ++i) {
    int resultBit = digitalRead(dataPin);
    Serial.print("Bit "); Serial.print(i); Serial.print(": ");
    Serial.println(resultBit);
    result += resultBit << i;
    delay(baudRate);
  }

  return result;
}

void transmitDataViaDigitalPin(int value, int dataPin, int baudRate) {
  /*
  - Outputs a zero to start communication
  - Outputs the each bit sequencial for an 8-bit number
  - Outputs a zero to end the communication
  - Outputs a 1

  Sample Data Written will look like this:
  111111[0110011000]1111111

  * One whole cycle takes 11 bits
  */

  const int MASK{0b1};

  digitalWrite(dataPin, LOW);
  delay(baudRate);

  for(int i{0}; i < 8; ++i) {
    digitalWrite(dataPin, value & MASK);
    delay(baudRate);

    value >>= 1;
  }

  digitalWrite(dataPin, LOW);
  delay(baudRate);
  digitalWrite(dataPin, HIGH);
}