const long utcOffsetInSeconds = 7200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

String gettime() {
  timeClient.begin();
  timeClient.update();
  String timestamp = String(daysOfTheWeek[timeClient.getDay()]) + "  " + String(timeClient.getHours()) +
  ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds());
  return timestamp;
}
