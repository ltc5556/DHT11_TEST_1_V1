// Modified RTCtester for lab:
// - Serial prints group number first
// - TM1637 shows "组号:分钟" as GG:MM (4 digits + colon)
#include "TM1637.h"
#include "RTClib.h"

// TODO: change to your real group number
#define GROUP_NUM 26

#define CLK 10
#define DIO 9
TM1637 tm1637(CLK, DIO);
RTC_DS1307 RTC;
int8_t TimeDisp[] = {0xff, 0xff, 0xff, 0xff};

void setup() {
  Serial.begin(9600);
  if (!RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  tm1637.init();
  tm1637.set(2);
  tm1637.display(0, 10);
  tm1637.display(1, 11);
  tm1637.display(2, 12);
  tm1637.display(3, 13);
  delay(3000);
}

int minute, second;
unsigned char ClockPoint = 1;

void loop() {
  DateTime theTime = RTC.now();
  second = theTime.second();
  minute = theTime.minute();

  // PPT: print group number before sensor data
  Serial.print("Group: ");
  Serial.print(GROUP_NUM);
  Serial.print("  Time: ");
  Serial.print(theTime.hour());
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);

  // PPT: TM1637 show 组号:分钟  -> two digits group + two digits minute
  int g = GROUP_NUM;
  if (g < 0) g = 0;
  if (g > 99) g = 99;
  TimeDisp[0] = g / 10;
  TimeDisp[1] = g % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;

  tm1637.display(0, TimeDisp[0]);
  tm1637.display(1, TimeDisp[1]);
  tm1637.display(2, TimeDisp[2]);
  tm1637.display(3, TimeDisp[3]);

  ClockPoint = (~ClockPoint) & 0x01;
  if (ClockPoint) tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);

  delay(1000);
}
