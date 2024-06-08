#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 

IPAddress    apIP(55, 55, 55, 55); 

const char* ssid = "MyLdr"; //שם הרשת שיוצג
const char* password = "88888888";// הסיסמה לרשת אם נרצה להשתמש בה 
ESP8266WebServer server(80); 

void WifiSetup(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00   
  WiFi.softAP(ssid); 
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin(); 

}
void wifi_loop() {
  server.handleClient();//.server is defined at this tab
  delay(10);
} 
void handleNotFound(){
  String message = "File Not Found \n \n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}
void handleRoot(){
  char html[2000]="";
	strcat(html, "<html>");

  server.send(200, "text/html", html);
}





