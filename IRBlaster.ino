#include "IRLibAll.h"

/* String input; */
#define INPUT_SIZE 30
char input[INPUT_SIZE + 1];

IRrecvPCI myReceiver(2);
IRdecode myDecoder;
IRsend mySender;

const int GREEN_LED = 21;

const char* READ_ACTION = "READ";
const char* SEND_ACTION = "SEND";

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    digitalWrite(GREEN_LED, HIGH);
    delay(50);
    digitalWrite(GREEN_LED, LOW);
    delay(50);
    ; // wait for serial port to connect. Needed for native USB
  }
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  while(Serial.available()) {
    byte inputSize = Serial.readBytesUntil('\n', input, INPUT_SIZE);
    input[inputSize] = 0;
    char* command = strtok(input, " ");
    if (strcmp(command, READ_ACTION) == 0) {
      read();
    } else if (strcmp(command, SEND_ACTION) == 0) {
      send();
    }
  }
}

void read() {
  myReceiver.enableIRIn();
  while(!myReceiver.getResults()) {
    digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
    delay(100);
  }
  digitalWrite(GREEN_LED, LOW);
  myDecoder.decode();
  Serial.print("OK ");
  Serial.print(myDecoder.protocolNum,DEC);
  Serial.print(" ");
  Serial.print(myDecoder.value, DEC);
  Serial.print(" ");
  Serial.print(myDecoder.bits, DEC);
  Serial.println();
}

void send() {
  uint8_t protocol = strtoul(strtok(NULL, " "), NULL, 10);
  uint32_t code = strtoul(strtok(NULL, " "), NULL, 10);
  uint16_t bits = strtoul(strtok(NULL, " "), NULL, 10);
  uint16_t times = strtoul(strtok(NULL, " "), NULL, 10);
  uint16_t sleep = strtoul(strtok(NULL, " "), NULL, 10);
  for(uint16_t i = 0; i < times; i++) {
    if(i > 0) {
      delay(sleep);
    }
    mySender.send(protocol, code, bits);
  }
  Serial.println("OK");
  /* Serial.print("OK "); */
  /* Serial.print(protocol,DEC); */
  /* Serial.print(" "); */
  /* Serial.print(code, DEC); */
  /* Serial.print(" "); */
  /* Serial.print(bits, DEC); */
  /* Serial.println(); */
}
