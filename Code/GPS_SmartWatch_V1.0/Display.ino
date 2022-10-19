void drawClock() {

  char current_time[9] = " ";
  char current_date[11] = "01-01-2000";



  if (B_time_HH < 10 && B_time_MM < 10 && B_time_SS < 10) {
    sprintf(current_time, "0%d:0%d:0%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH < 10 && B_time_MM < 10 && B_time_SS >= 10) {
    sprintf(current_time, "0%d:0%d:%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH < 10 && B_time_MM >= 10 && B_time_SS < 10) {
    sprintf(current_time, "0%d:%d:0%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH < 10 && B_time_MM >= 10 && B_time_SS >= 10) {
    sprintf(current_time, "0%d:%d:%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH >= 10 && B_time_MM < 10 && B_time_SS < 10) {
    sprintf(current_time, "%d:0%d:0%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH >= 10 && B_time_MM < 10 && B_time_SS >= 10) {
    sprintf(current_time, "%d:0%d:%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH >= 10 && B_time_MM >= 10 && B_time_SS < 10) {
    sprintf(current_time, "%d:%d:0%d", B_time_HH, B_time_MM, B_time_SS);
  } else if (B_time_HH >= 10 && B_time_MM >= 10 && B_time_SS >= 10) {
    sprintf(current_time, "%d:%d:%d", B_time_HH, B_time_MM, B_time_SS);
  }




  u8g.setFont(u8g_font_courB18r);

  u8g.drawStr(10, 32, current_time);

  u8g.setFont(u8g_font_courR12r);
  u8g.drawStr(15, 55, current_date);


  //############# test ######################

  char btnstatus[3];
  int bU = 0;
  int bD = 0;

  if (status_btnUP()) {
    bU = 1;
  } else {
    bU = 0;
  }

  if (status_btnDN()) {
    bD = 1;
  } else {
    bD = 0;
  }

  int istatus = (bU * 10) + bD;
  if (istatus < 10) {
    sprintf(btnstatus, "0%d", istatus);
  } else {
    sprintf(btnstatus, "%d", istatus);
  }

  u8g.drawStr(60, 11, btnstatus);
  //###########################################
}




void setClock() {
  if (toggle_setClock) {
    toSET_HH = myRTC.getHour(h12Flag, pmFlag);
    toSET_MM = myRTC.getMinute();
    toSET_SS = myRTC.getSecond();
  }
  char TOSET_time[9] = " ";
  char TOSET_date[11] = "01-01-2000";

  if (toSET_HH < 10 && toSET_MM < 10 && toSET_SS < 10) {
    sprintf(TOSET_time, "0%d:0%d:0%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH < 10 && toSET_MM < 10 && toSET_SS >= 10) {
    sprintf(TOSET_time, "0%d:0%d:%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH < 10 && toSET_MM >= 10 && toSET_SS < 10) {
    sprintf(TOSET_time, "0%d:%d:0%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH < 10 && toSET_MM >= 10 && toSET_SS >= 10) {
    sprintf(TOSET_time, "0%d:%d:%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH >= 10 && toSET_MM < 10 && toSET_SS < 10) {
    sprintf(TOSET_time, "%d:0%d:0%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH >= 10 && toSET_MM < 10 && toSET_SS >= 10) {
    sprintf(TOSET_time, "%d:0%d:%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH >= 10 && toSET_MM >= 10 && toSET_SS < 10) {
    sprintf(TOSET_time, "%d:%d:0%d", toSET_HH, toSET_MM, toSET_SS);
  } else if (toSET_HH >= 10 && toSET_MM >= 10 && toSET_SS >= 10) {
    sprintf(TOSET_time, "%d:%d:%d", toSET_HH, toSET_MM, toSET_SS);
  }

  u8g.setFont(u8g_font_courB18r);

  u8g.drawStr(10, 32, TOSET_time);

  u8g.setFont(u8g_font_courR12r);
  u8g.drawStr(15, 55, TOSET_date);

  u8g.drawStr(14, 10, "SET");

  switch (TOSET) {
    case 1:
      u8g.drawStr(10, 38, "---");
      u8g.drawStr(50, 11, "HOUR");
      break;
    case 2:
      u8g.drawStr(55, 38, "---");
      u8g.drawStr(50, 11, "MINUTE");
      break;
    case 3:
      u8g.drawStr(100, 38, "---");
      u8g.drawStr(50, 11, "SECONDS");
      break;
    case 4:
      u8g.drawStr(15, 62, "--");
      u8g.drawStr(50, 11, "DATE");
      break;
    case 5:
      u8g.drawStr(45, 62, "--");
      u8g.drawStr(50, 11, "MONTH");
      break;
    case 6:
      u8g.drawStr(75, 62, "----");
      u8g.drawStr(50, 11, "YEAR");
      break;
    case 7:
      u8g.drawStr(50, 11, "EXIT");
      break;
    case 8:
      u8g.drawStr(50, 11, "EXIT");
      break;
    case 9:
      TOSET = 1;
      break;
    default:
      TOSET = 1;
  }


  //############# test ######################
  /*char ch_toset[2];
  sprintf(ch_toset, "%d", TOSET);
  u8g.drawStr(45, 11, ch_toset);*/
  //###########################################
}