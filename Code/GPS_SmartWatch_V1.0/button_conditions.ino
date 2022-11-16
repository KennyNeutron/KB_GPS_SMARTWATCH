void button_conditions() {

  if (!status_btnUP() && !status_btnDN() && !SETClock && !SETNum && !SETEmg) {
    btn_emg++;
    if (btn_emg == 40) {
      SETEmg = true;
    }
  } else {
    btn_emg = 0;
  }

  if (status_btnUP() && !status_btnDN() && !toggle_setClock) {
    btn_cnt++;
    if (btn_cnt == 10 && !SETClock) {
      SETClock = true;
      toggle_setClock = true;
      TOSET = 0;
    } else if (btn_cnt == 10 && SETClock) {
      SETClock = false;
      toggle_setClock = true;
      toggle_SAVESET = true;
    }
  } else {
    btn_cnt = 0;
  }




  if (SETClock && toggle_btnDN && !toggle_TOSET) {
    TOSET++;
    toggle_TOSET = true;
  }

  if (!toggle_btnDN) {
    toggle_TOSET = false;
  }




  if (SETClock && toggle_btnUP && !toggle_SETVAR) {
    switch (TOSET) {
      case 1:
        toSET_HH++;
        break;
      case 2:
        toSET_MM++;
        break;
      case 3:
        toSET_SS++;
        break;
      case 4:
        toSET_MO++;
        break;
      case 5:
        toSET_DD++;
        break;
      case 6:
        toSET_YYYY++;
        break;
    }
    toggle_SETVAR = true;
  }


  if (toSET_HH >= 24) {
    toSET_HH = 0;
  }
  if (toSET_MM >= 60) {
    toSET_MM = 0;
  }
  if (toSET_SS >= 60) {
    toSET_SS = 0;
  }

  if (toSET_MO > 12) {
    toSET_MO = 1;
  }

  if (toSET_DD > 31) {
    toSET_DD = 1;
  }

  if (toSET_YYYY >= 100) {
    toSET_YYYY = 0;
  }

  if (!toggle_btnUP) {
    toggle_SETVAR = false;
  }
}
