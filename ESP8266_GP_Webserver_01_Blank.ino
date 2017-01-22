//#########################################################################
//##############  General Purpose Webserver/Template ######################
//#########################################################################
// A webserver template that can be adjusted to suit your needs
//################# LIBRARIES ################
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiManager.h>     // https://github.com/tzapu/WiFiManager
//#include <HttpClient.h>
#include <DNSServer.h>
//################ VARIABLES ################

//------ NETWORK VARIABLES---------
const char *ssid      = "your_ssid";     // Not needed as this program includes the WiFi manager, see the instructions later
const char *password  = "your_password"; // Not needed as this program includes the WiFi manager, see the instructions later

//################ PROGRAM VARIABLES and OBJECTS ################
String page1_txt = "Page-1"; // Adjust the text to suit your needs, for example page1txt = 'Temperature'
String page2_txt = "Page-2";
String page3_txt = "Page-3";
String page4_txt = "Page-4";
String page5_txt = "Page-5";
String page6_txt = "Page-6";
String page7_txt = "Page-7";
String page8_txt = "Page-8";
String page9_txt = "Page-9"; // Adjust the text to suit your needs, for example page9_txt = 'Help'
bool   page1_enabled = true; // Set to false to remove/disable each command as required
bool   page2_enabled = true;
bool   page3_enabled = true;
bool   page4_enabled = true;
bool   page5_enabled = true;
bool   page6_enabled = true;
bool   page7_enabled = true;
bool   page8_enabled = true;
bool   page9_enabled = true;
String siteheading   = "My Webserver";
String subheading    = "My Webserver Sub-Heading";
String sitetitle     = "Webserver"; // Appears on browser tabs
String yourcopyright = "My System";
String siteversion   = "v1.0"; // Version of your webserver
String webpage       = "";     // General purpose variable to hold HTML code
#define sitewidth 1024         // Adjust site page width as required

ESP8266WebServer server(80);   // Start server on port 80 (default for a web-browser, change to your requirements, e.g. 8080 if your Router uses port 80
                               // To access server from the outside of a WiFi network e.g. ESP8266WebServer server(8266) add a rule on your Router that forwards a
                               // connection request to http://your_network_ip_address:8266 to port 8266 and view your ESP server from anywhere.
                               // Example http://yourhome.ip:8266 will be directed to http://192.168.0.40:8266 or whatever IP address your router gives to this server
void setup()
{
  Serial.begin(115200); // initialize serial communications
  WiFiManager wifiManager;
  // New OOB ESP8266 has no Wi-Fi credentials so will connect and not need the next command to be uncommented and compiled in, a used one with incorrect credentials will
  // so restart the ESP8266 and connect your PC to the wireless access point called 'ESP8266_AP' or whatever you call it below in ""
//// wifiManager.resetSettings(); // Include this command for new ESP8266 devices, then connect to http://192.168.4.1/ and follow instructions to make the WiFi connection
  // Set a timeout until configuration is turned off, useful to retry or go to sleep in n-seconds
  wifiManager.setTimeout(180);
  //fetches ssid and password and tries to connect, if connections succeeds it starts an access point with the name called "ESP8266_AP" and waits in a blocking loop for configuration
  if(!wifiManager.autoConnect("ESP8266_AP")) {
    Serial.println(F("failed to connect and timeout occurred"));
    delay(6000);
    ESP.reset(); //reset and try again
    delay(180000);
  }
  // At this stage the WiFi manager will have successfully connected to a network, or if not will try again in 180-seconds
  Serial.println(F("WiFi connected.."));
  //----------------------------------------------------------------------
  server.begin(); Serial.println(F("Webserver started...")); // Start the webserver
  Serial.println("Use this URL to connect: http://"+WiFi.localIP().toString()+"/");// Print the IP address
  server.on("/",         user_input); // If the user types at their browser http://192.168.0.100/ control is passed here and then to user_input, you get values for your program...
  server.on("/homepage", homepage);   // If the user types at their browser http://192.168.0.100/homepage or via menu control is passed here and then to the homepage
  server.on("/command1", page1);      // If the user types at their browser http://192.168.0.100/page1 or via menu control is passed here and then to the page1
  server.on("/command2", page2);      // If the user types at their browser http://192.168.0.100/page2 or via menu control is passed here and then to the page2
  server.on("/command3", page3);      // ...
  server.on("/command4", page4);      // ...
  server.on("/command5", page5);      // ...
  server.on("/command6", page6);      // ...
  server.on("/command7", page7);      // ...
  server.on("/command8", page8);      // ...
  server.on("/command9", page9);      // If the user types at their browser http://192.168.0.100/page9 or via menu control is passed here and then to the page9
}

void loop() {
  server.handleClient();
}

void homepage(){
  append_HTML_header(); 
  webpage += "<P class='style6'>This is the server home page</p>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page1(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-1</H3>";
  webpage += "<P class='style6'>This is the server home page</p>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page2(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-2</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page3(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-3</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page4(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-4</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page5(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-5</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page6(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-6</H3>";
  webpage += "<P class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page7(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-7</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page8(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-8</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page9(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-9</H3>";
  webpage += "<p class='style6'>";
  webpage += "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ullamcorper vestibulum nibh, ac ultricies tortor tempus id.";
  webpage += "Sed tincidunt elit eget velit vehicula, at rutrum enim mattis. Nunc sed nisi pharetra, efficitur quam eget, pulvinar nulla.";
  webpage += "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque malesuada dolor lacus, ac";
  webpage += "imperdiet enim maximus sit amet. Donec eu ullamcorper arcu. Mauris vitae diam ante. Duis vehicula dolor eget finibus rutrum.";
  webpage += "Nam augue diam, volutpat nec mauris et, finibus rhoncus urna. Morbi a iaculis sem. Nullam neque justo, malesuada sed auctor";
  webpage += "a, varius eu ante. Aenean semper fringilla hendrerit.";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void append_HTML_header() {
  webpage = "HTTP/1.1 200 OK";
  webpage += "Content-Type: text/html"; 
  webpage += "Connection: close";  // the connection will be closed after completion of the response
  webpage += "Refresh: 30";        // refresh the page automatically every 30 sec                                                  
  webpage += "<!DOCTYPE html><html><head>";
  webpage += "<meta http-equiv='refresh' content='60'>"; // 30-sec refresh time, test needed to prevent auto updates repeating some commands
  webpage += "<title>"+sitetitle+"</title><style>";
  webpage += "body {width:"+String(sitewidth)+"px;margin:0 auto;font-family:arial;font-size:14px;text-align:center;color:blue;background-color:#F7F2Fd;}";
  webpage += "</style></head><body><h1>"+siteheading+" "+ siteversion + "</h1>";
  webpage += "<h3>"+subheading+"<br></h1>";
}

void append_HTML_footer(){ // Saves repeating many lines of code for HTML page footers
  webpage += "<head><style>ul{list-style-type:none;margin:0;padding:0;overflow:hidden;background-color:#d8d8d8;font-size:14px;}";
  webpage += "li{float:left;border-right:1px solid #bbb;}last-child {border-right: none;}";
  webpage += "li a{display: block;padding:3px 15px;text-decoration:none;}";
  webpage += "li a:hover{background-color:#FFFFFF;}";
  webpage += "section {font-size:14px;}";
  webpage += "p {background-color:#E3D1E2;}";
  webpage += "h1{background-color:#d8d8d8;}";
  webpage += "h3{color:#9370DB;font-size:24px;}";
  webpage += "table{font-family: arial, sans-serif;font-size:16px;border-collapse: collapse;width: 100%;}";
  webpage += "td, th {border: 0px solid black;text-align: left;padding: 2px;}";
  webpage += ".style1 {text-align:center;font-size:24px; background-color:#D8BFD8;}";
  webpage += ".style2 {text-align:center;font-size:20px; background-color:#ADD8E6;}";
  webpage += ".style3 {text-align:center;font-size:16px; background-color:#FFE4B5;}";
  webpage += ".style4 {text-align:center;font-size:14px; background-color:#FFE4B5;}";
  webpage += ".style5 {text-align:center;font-size:14px; background-color:#D9BFD9;}";
  webpage += ".style6 {text-align:left;  font-size:16px; background-color:#F7F2Fd; width:100%;}";
  webpage += "sup{vertical-align:super;font-size:smaller;}"; // superscript controls
  webpage += "</style>";
  webpage += "<ul>";
  webpage += "  <li><a href='/homepage'>Home Page</a></li>";
  if (page1_enabled) webpage += "  <li><a href='/command1'>"+page1_txt+"</a></li>";
  if (page2_enabled) webpage += "  <li><a href='/command2'>"+page2_txt+"</a></li>";
  if (page3_enabled) webpage += "  <li><a href='/command3'>"+page3_txt+"</a></li>";
  if (page4_enabled) webpage += "  <li><a href='/command4'>"+page4_txt+"</a></li>";
  if (page5_enabled) webpage += "  <li><a href='/command5'>"+page5_txt+"</a></li>";
  if (page6_enabled) webpage += "  <li><a href='/command6'>"+page6_txt+"</a></li>";
  if (page7_enabled) webpage += "  <li><a href='/command7'>"+page7_txt+"</a></li>";
  if (page8_enabled) webpage += "  <li><a href='/command8'>"+page8_txt+"</a></li>";
  if (page9_enabled) webpage += "  <li><a href='/command9'>"+page9_txt+"</a></li>";
  webpage += "  <li><a href='/'>Setup</a></li>";
  webpage += "</ul>";
  webpage += "<p>&copy; "+yourcopyright+" 2017<br>";
  webpage += "&copy;"+String(char(byte(0x40>>1)))+String(char(byte(0x88>>1)))+String(char(byte(0x5c>>1)))+String(char(byte(0x98>>1)))+String(char(byte(0x5c>>1)));
  webpage += String(char((0x84>>1)))+String(char(byte(0xd2>>1)))+String(char(0xe4>>1))+String(char(0xc8>>1))+String(char(byte(0x40>>1)));
  webpage += String(char(byte(0x64/2)))+String(char(byte(0x60>>1)))+String(char(byte(0x62>>1)))+String(char(0x6e>>1))+"</p>";
  webpage += "</body></html>";
}

void user_input() {
  webpage = ""; // don't delete this command, it ensures the server works reliably!
  append_HTML_header();
  String IPaddress = WiFi.localIP().toString();
  webpage += "<h3>User Input, if required enter values then select Enter</h3>";
  webpage += "<form action=\"http://"+IPaddress+"\" method=\"POST\">";
  webpage += "Input field 1<br><input type='text' name='field1' value='field-1-default'><br>";
  webpage += "Input field 2<br><input type='text' name='field2' value='field-2-default'><br>";
  webpage += "Input field 3<br><input type='text' name='field3' value='field-3-default'><br>";
  webpage += "Input field 4<br><input type='text' name='field4' value='field-4-default'><br>";
  // And so-on
  webpage += "<input type='submit' value='Enter'><br><br>";
  webpage += "</form></body>";
  append_HTML_footer();
  server.send(200, "text/html", webpage); // Send a response to the client to enter their inputs, if needed, Enter=defaults
  if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      String Argument_Name   = server.argName(i);
      String client_response = server.arg(i);
      if (Argument_Name == "field1") {
        String field1_response = client_response;
      }
      if (Argument_Name == "field2") {
        String field2_response = client_response;
      }
      if (Argument_Name == "field3") {
        String field3_response = client_response;
      }
      if (Argument_Name == "field4") {
        String field4_response = client_response;
      }
    }
  }
  webpage = "";
  homepage();
}

