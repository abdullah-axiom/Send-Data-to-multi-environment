String serverName = "http://192.168.0.100";

void send_localdb(int v1, int v2){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // specify the path into the server
    String serverPath = serverName + "/test/dbwrite_post.php";
    // start HTTP connection
    http.begin(serverPath);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST("degree=" + String(v1) + "&other=" + String(v2));

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      byte ret = sendEmail(emailfrom,emailto,"Error accessing local database !!!!!!!!!!!");
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
