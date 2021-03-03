void initWiFi()
{
  const char* wifi_ssid = "x";
  const char* wifi_password = "71908872$$";
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print(WiFi.localIP());
  byte ret = sendEmail(emailfrom, emailto, "The last time that the ESP8266 connected to wifi is :  " + gettime());
}
