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
  server.on("/GetValue", SendLdrValueAsJson); 
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
  if (server.hasArg("btn_pressed")) {
    //MapDir = (server.arg("btn_pressed")=="1") ? 1 : 2;
    MapDir = server.arg("btn_pressed").toInt();
  }
  

  char html[2000]="";
	strcat(html, "<html>");
	strcat(html, "<head>");
	strcat(html, "<meta charset=\"UTF-8\">");
	strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
	strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	// strcat(html, "<META HTTP-EQUIV=\"refresh\" CONTENT=\"1\">");
	strcat(html, "<title>Big_Number</title>");
  //beginig of my css
  strcat(html, "<style>");
  // the css body 
  strcat(html, "body{");
  strcat(html, " justify-content: center;");
  strcat(html, " align-items: center;");
  strcat(html, "  background-color: yellow;");
  strcat(html, "  };");
  //the css for big number 
  strcat(html, "  .BigNumber{");
  strcat(html, "  font-size: 100px;;");
  strcat(html, "  width: 30px;");
  strcat(html, "  align-items: center;");
  strcat(html, "  justify-content: center;;");
  strcat(html, "  };");
  // THE END OF MY CSS 
  strcat(html, "</style>");
  //the end of the head
  strcat(html, "</head>");
  // beginig of the body 
  strcat(html, "<body>");
  strcat(html, "<h2>LDR value</h2>");
  // LdrVal is from main tab
  char strTmp[5];
  itoa(LdrVal,strTmp,10);
  strcat(html, "<div class=\"BigNumber\" id='LdrVal'>");
  strcat(html, strTmp);
  strcat(html, "</div>");

  strcat(html, "<form action='' method='get'>");
  strcat(html, "<button name='btn_pressed' value='1'>אור סינכרוני</button>");
  strcat(html, "<button name='btn_pressed' value='2'>אור הפוך</button>");
  strcat(html, "</form>");

  strcat(html, "<script>");
  strcat(html, "async function logMovies() {");
  strcat(html, "const response = await fetch('/GetValue');");
  strcat(html, "const movies = await response.json();");//{Ldr:13}
  strcat(html, "document.getElementById('LdrVal').innerHTML=movies.Ldr;");
  strcat(html, "}");
  strcat(html, "setInterval(logMovies, 1000)");

  strcat(html, "</script>");
  // the end of the body
  strcat(html, "</body>");
  // the end of my html documnet
 strcat(html, "</html>");

  server.send(200, "text/html", html);
}
void SendLdrValueAsJson(){
  char json[100]="";
  strcat(json,"{Ldr:");

  char strTmp[5];
  itoa(LdrVal,strTmp,10);
  strcat(json, strTmp);
  
  strcat(json,"}");
  
  server.send(200, "application/json", json);
}





