#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "parker";
String ssid = "";
String password = "";
int val = 0;
/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 0; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

WiFiServer server(80);

void setup() 
{
  initHardware();
  setupWiFiAP();
  server.begin();
  if (ssid = "");
    RunWiFiAP();
}

void loop() 
{

if (ssid != "");
 Serial.println(ssid);
 const char* ssid     = ssid;
 const char* password = password;

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void setupWiFiAP()
{
  WiFi.mode(WIFI_AP);
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, AP_NameString.length() + 1, 0);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}
void RunWiFiAP()
{
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  String req1 = req;
  req1.replace("GET /setup?","");
  String req2 = req1;
  req2.replace(" HTTP/1.1","");
  Serial.println(req2);
  ssid = Serial.readStringUntil('&');
  
  client.flush();

  if (req.indexOf("/setup") != -1)
    val = 1; // Will print pin read

  client.flush();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";

  if (val == 1);
  {
    s += "<form>";
    s +=  "Wifi Name: <input type='text' name='wifiname'><br>";
    s +=  "Wifi Password: <input type='text' name='wifipass'><br>";
    s +=  "<input type='submit' value='Submit'>";
    s += "</form>";
  }
 
  // Send the response to the client
  client.print(s);
}

void initHardware()
{
  Serial.begin(115200);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.
}

