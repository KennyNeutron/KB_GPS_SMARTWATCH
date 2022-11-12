void SendMessage() {
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");  //Sets the GSM Module in Text Mode
  delay(200);
  Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + emg_number + "\"\r");  //Mobile phone number to send message
  delay(200);
  String SMS = "I have an emergency... my current location is... ";
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
