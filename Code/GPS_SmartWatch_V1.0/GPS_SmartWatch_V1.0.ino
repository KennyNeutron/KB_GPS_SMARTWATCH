#include <avr/wdt.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include <TinyGPSPlus.h>


#include <SoftwareSerial.h>
SoftwareSerial sim(2, 3);
int _timeout;
String _buffer;
String emg_number = "+639286707466";  //-> change with your number

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);




U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);  // Dev 0, Fast I2C / TWI




#define btn_up 7
#define btn_dn 6


bool SETClock = false;
bool SETNum = false;
bool SETEmg = false;

bool EMGmsg_sent = false;

DS3231 myRTC;

byte TOSET = 0;

bool toggle_TOSET = false;
bool toggle_SETVAR = false;
bool toggle_SAVESET = false;

byte toSET_HH = 0;
byte toSET_MM = 0;
byte toSET_SS = 0;

byte toSET_DD = 0;
byte toSET_MO = 0;
int toSET_YYYY = 0;

bool century = false;
bool h12Flag;
bool pmFlag;

byte B_time_HH;
byte B_time_MM;
byte B_time_SS;

int I_date_YY;
byte B_date_MO;
byte B_date_DD;

String gps_lat = " ";
String gps_lon = " ";

uint32_t last_millis=0;

void setup() {


  pinMode(btn_up, INPUT);
  pinMode(btn_dn, INPUT);


  Serial.begin(9600);
  Serial.println("START");

  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);

  delay(1000);

  //##################### OLED DISPLAY #####################
  // flip screen, if required
  // u8g.setRot180();
  if (u8g.getMode() == U8G_MODE_R3G3B2) {
    u8g.setColorIndex(255);  // white
  } else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3);  // max intensity
  } else if (u8g.getMode() == U8G_MODE_BW) {
    u8g.setColorIndex(1);  // pixel on
  } else if (u8g.getMode() == U8G_MODE_HICOLOR) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
  //########################################################

  //###### Watchdog Timer ##########
  //wdt_enable(WDTO_8S);
  //################################

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
  //  sei();  //allow interrupts
  //#############################################################


  //GPS
  ss.begin(GPSBaud);
  Serial.println(TinyGPSPlus::libraryVersion());
}

//timer0 interrupt 2kHz
int btn_cnt = 0;

int btn_emg = 0;

bool toggle_btnUP = false;
bool toggle_btnDN = false;
bool toggle_setClock = false;
//
//ISR(TIMER0_COMPA_vect) {
//  if (!status_btnUP()) {
//    toggle_btnUP = true;
//  } else {
//    toggle_btnUP = false;
//    toggle_setClock = false;
//  }
//
//  if (!status_btnDN()) {
//    toggle_btnDN = true;
//  } else {
//    toggle_btnDN = false;
//    toggle_setClock = false;
//  }
//
//  button_conditions();
//
//}

void isr_tmr() {
  if (!status_btnUP()) {
    toggle_btnUP = true;
  } else {
    toggle_btnUP = false;
    toggle_setClock = false;
  }

  if (!status_btnDN()) {
    toggle_btnDN = true;
  } else {
    toggle_btnDN = false;
    toggle_setClock = false;
  }

  button_conditions();
}



void loop() {
//  if (!SETEmg) {
//    wdt_reset();
//  }
  isr_tmr();
  if (toggle_SAVESET) {
    myRTC.setHour(toSET_HH);
    myRTC.setMinute(toSET_MM);
    myRTC.setSecond(toSET_SS);
    myRTC.setMonth(toSET_MO);
    myRTC.setDate(toSET_DD);
    myRTC.setYear(toSET_YYYY);
    toggle_SAVESET = false;
  }

  /*
    Serial.println(latitud);
    Serial.println(latitudHemisphere);
    Serial.println(longitud);
    Serial.println(longitudMeridiano);



    Serial.println(link);

  */


  gps_loop();


  u8g.firstPage();
  do {
    if (!SETClock) {
      if (SETEmg) {
        displayEmg();
      } else {
        drawClock();
      }
    } else {
      setClock();
    }
    getTime();
  } while (u8g.nextPage());


  if (SETEmg) {
    Serial.println("EMG");
    if (!EMGmsg_sent) {
      Serial.println("EMG!!!!");
      SendMessage();
      EMGmsg_sent=true;
      last_millis=millis();
    }

    if(millis()-last_millis>=5000){
      SETEmg=false;
      EMGmsg_sent=false;
    }
  }

   
}
