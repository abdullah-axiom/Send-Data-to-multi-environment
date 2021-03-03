// Initialize Telegram BOT
#define BOTtoken "1530227262:AAEmfhkRyc70Bn86lfBdbPU8wfL7WUt7XHU"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "917858229"

WiFiClientSecure botclient;
UniversalTelegramBot bot(BOTtoken, botclient);


// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;


// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages, int v1, int v2) {

  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/Hello") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following command to see your outputs.\n\n";
      welcome += "/GetData \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/GetData") {

      bot.sendMessage(chat_id, "Degree is: " + String(v1) + "\n" + "Other is: " + String(v2) , "");
    }
  }
}

void telegram(int v1, int v2) {
  botclient.setInsecure();
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages,v1,v2);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  
}
