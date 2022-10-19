void button_conditions() {

  if (!status_btnUP() && !status_btnDN() && !toggle_setClock) {
    btn_cnt++;
    if (btn_cnt >= 2000 && !SETClock) {
      SETClock = true;
      toggle_setClock = true;
      TOSET = 0;
    } else if (btn_cnt >= 2000 && SETClock) {
      SETClock = false;
      toggle_setClock = true;
      toggle_SAVESET=true;
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
    }
    toggle_SETVAR=true;
  }


  if(toSET_HH>=24){
    toSET_HH=0;
  }
  if(toSET_MM>=60){
    toSET_MM=0;
  }
  if(toSET_SS>=60){
    toSET_SS=0;
  }

  if (!toggle_btnUP) {
    toggle_SETVAR = false;
  }
}