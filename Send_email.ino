WiFiClient espClient;

char smtp_server[] = "mail.smtp2go.com";

byte sendEmail(String from, String to, String body) {

  if (espClient.connect(smtp_server, 2525) == 1) {
    Serial.println(("connected"));
  } else {
    Serial.println(("connection failed"));
    return 0;
  }
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending EHLO"));
  espClient.println("EHLO www.example.com");
  if (!emailResp())
    return 0;
  //
  /*Serial.println(("Sending TTLS"));
    espClient.println("STARTTLS");
    if (!emailResp())
    return 0;*/
  //
  Serial.println(("Sending auth login"));
  espClient.println("AUTH LOGIN");
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending User"));
  // Change this to your base64, ASCII encoded username
  /*
    For example, the email address test@gmail.com would be encoded as dGVzdEBnbWFpbC5jb20=
  */
  espClient.println("YWZheWFk"); //base64, ASCII encoded Username
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending Password"));
  // change to your base64, ASCII encoded password
  /*
    For example, if your password is "testpassword" (excluding the quotes),
    it would be encoded as dGVzdHBhc3N3b3Jk
  */
  espClient.println("ZzRwa2w5V2FVR0pF");//base64, ASCII encoded Password
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending From"));
  // change to sender email address
  espClient.println(("MAIL From: " + String(from)));
  if (!emailResp())
    return 0;
  // change to recipient address
  Serial.println(("Sending To"));
  espClient.println(("RCPT To: " + String(to)));
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending DATA"));
  espClient.println(("DATA"));
  if (!emailResp())
    return 0;
  Serial.println(("Sending email"));
  // change to recipient address
  espClient.println(("To: " + String(to)));
  // change to your address
  espClient.println(("From: " + String(from)));
  espClient.println(("Subject: ESP8266 Device\r\n"));
  espClient.println((" " + String(body)));
  //
  espClient.println(("."));
  if (!emailResp())
    return 0;
  //
  Serial.println(("Sending QUIT"));
  espClient.println(("QUIT"));
  if (!emailResp())
    return 0;
  //
  espClient.stop();
  Serial.println(("disconnected"));
  return 1;
}

byte emailResp()
{
  byte responseCode;
  byte readByte;
  int loopCount = 0;

  while (!espClient.available())
  {
    delay(1);
    loopCount++;
    // Wait for 20 seconds and if nothing is received, stop.
    if (loopCount > 20000)
    {
      espClient.stop();
      Serial.println(("\r\nTimeout"));
      return 0;
    }
  }

  responseCode = espClient.peek();
  while (espClient.available())
  {
    readByte = espClient.read();
    Serial.write(readByte);
  }

  if (responseCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}
