void getTime() {
//  Serial.print(myRTC.getYear(), DEC);
//  Serial.print("-");
//  Serial.print(myRTC.getMonth(century), DEC);
//  Serial.print("-");
//  Serial.print(myRTC.getDate(), DEC);
//  Serial.print(" ");
//  Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);  //24-hr
//  Serial.print(":");
//  Serial.print(myRTC.getMinute(), DEC);
//  Serial.print(":");
//  Serial.println(myRTC.getSecond(), DEC);

  B_time_HH = myRTC.getHour(h12Flag, pmFlag);
  B_time_MM = myRTC.getMinute();
  B_time_SS = myRTC.getSecond();

  I_date_YY= myRTC.getYear();
  B_date_MO=myRTC.getMonth(century);
  B_date_DD=myRTC.getDate();
}
