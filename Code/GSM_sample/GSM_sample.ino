#include <SoftwareSerial.h>
SoftwareSerial sim(2, 3);
int _timeout;
String _buffer;
String number = "+639286707466";  //-> change with your number

bool ledstate = false;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  //delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call");


  //############# interrupt timer ##########################
//  cli();       //stop interrupts
//  //set timer0 interrupt at 2kHz
//  TCCR0A = 0;  // set entire TCCR2A register to 0
//  TCCR0B = 0;  // same for TCCR2B
//  TCNT0 = 0;   //initialize counter value to 0
//  // set compare match register for 2khz increments
//  OCR0A = 124;  // = (16*10^6) / (2000*64) - 1 (must be <256)
//  // turn on CTC mode
//  TCCR0A |= (1 << WGM01);
//  // Set CS01 and CS00 bits for 64 prescaler
//  TCCR0B |= (1 << CS01) | (1 << CS00);
//  // enable timer compare interrupt
//  TIMSK0 |= (1 << OCIE0A);
  sei();  //allow interrupts
  //#############################################################
}

int cnt = 0;
ISR(TIMER0_COMPA_vect) {

}

void loop() {


  if (Serial.available() > 0)
    switch (Serial.read()) {
      case 's':
      Serial.println("SSS");
        SendMessage();
        break;
      case 'r':
        RecieveMessage();
        break;
      case 'c':
        callNumber();
        break;
    }
  if (sim.available() > 0)
    Serial.write(sim.read());
}
void SendMessage() {
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");  //Sets the GSM Module in Text Mode
  delay(200);
  Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r");  //Mobile phone number to send message
  delay(200);
  String SMS = "Hello, World! -Kenny Neutron";
  Serial.print("Sending");
  sim.println(SMS);
  delay(100);
  Serial.print(".");
  sim.println((char)26);  // ASCII code of CTRL+Z

  Serial.print(".");
  delay(200);

  Serial.print(".");
  _buffer = _readSerial();

  Serial.print(".");
  Serial.println("MESSAGE SENT");
}
void RecieveMessage() {
  Serial.println("SIM800L Read an SMS");
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CNMI=1,2,0,0,0");  // AT Command to receive a live SMS
  delay(200);
  Serial.write("Unread Message done");
}
String _readSerial() {
  _timeout = 0;
  while (!sim.available() && _timeout < 12000) {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void callNumber() {
  sim.print(F("ATD"));
  sim.print(number);
  sim.print(F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}
