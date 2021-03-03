static const char *fingerprint = "D3 9A 63 03 25 7A 93 23 52 D0 84 41 75 3D 71 A5 8F FA 07 9F";
// example: <myiothub>.azure-devices.net
const char* iothub_url = "espnode.azure-devices.net";

// this is the id of the device created in Iot Hub
// example: myCoolDevice
const char* iothub_deviceid = "iotd1";

// <myiothub>.azure-devices.net/<myCoolDevice>
const char* iothub_user = "espnode.azure-devices.net/iotd1";

// SAS token should look like "SharedAccessSignature sr=<myiothub>.azure-devices.net%2Fdevices%2F<myCoolDevice>&sig=123&se=456"
const char* iothub_sas_token = "SharedAccessSignature sr=espnode.azure-devices.net%2Fdevices%2Fiotd1&sig=fA7HXYYvEniyMTt8%2FT29ERm87rFqMEOpw%2FiGycBGDSY%3D&se=1644921849";

// default topic feed for subscribing is "devices/<myCoolDevice>/messages/devicebound/#""
const char* iothub_subscribe_endpoint = "devices/iotd1/messages/devicebound/#";

// default topic feed for publishing is "devices/<myCoolDevice>/messages/events/"
const char* iothub_publish_endpoint = "devices/iotd1/messages/events/";


WiFiClientSecure esp8266Client;
PubSubClient iotClient(esp8266Client);

long lastMsg = 0;

// function to connect to MQTT server
void connect_mqtt() {
  // Loop until we're reconnected
  while (!iotClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (iotClient.connect(iothub_deviceid, iothub_user, iothub_sas_token)) {
      Serial.println("connected");
      // ... and resubscribe
      iotClient.subscribe(iothub_subscribe_endpoint);
    } else {
      byte ret = sendEmail(emailfrom,emailto,"Error accessing Azure IoTHub !!!!!!!!!!!");
      Serial.print("failed, rc=");
      Serial.print(iotClient.state());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// callback function for when a message is dequeued from the MQTT server
void callback(char* topic, byte* payload, unsigned int length) {
  // print message to serial for debugging
  Serial.print("Message arrived: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println('---');
}

void to_iothub(int v1, int v2) {
  esp8266Client.setFingerprint(fingerprint);
  iotClient.setServer(iothub_url, 8883);
  iotClient.setCallback(callback);

  // connect to MQTT
  connect_mqtt();
  iotClient.loop();
  long now = millis();

  // publish data and debug mqtt connection every 10 seconds
  if (now - lastMsg > 1000) {
    lastMsg = now;

    Serial.print("is MQTT client is still connected: ");
    Serial.println(iotClient.connected());

    // set up json object
    StaticJsonDocument<200> doc;

    // populate keys in json
    doc["degree"] = v1;
    // substitute the int value below for a real sensor reading (ie. an analogRead() result)
    doc["other"] = v2;

    // convert json to buffer for publishing
    char buffer[256];
    serializeJson(doc, buffer);

    // publish
    iotClient.publish(iothub_publish_endpoint, buffer);
    iotClient.disconnect();
  }
}
