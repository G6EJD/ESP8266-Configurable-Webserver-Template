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
String page1_txt = "Page-1"; // Adjust the text to suit your needs, for example page1_txt = 'Temperature'
String page2_txt = "Page-2";
String page3_txt = "Page-3";
String page4_txt = "Page-4";
String page5_txt = "Page-5";
String page6_txt = "Page-6";
String page7_txt = "Page-7";
String page8_txt = "Page-8";
String page9_txt = "Page-9"; // Adjust the text to suit your needs, for example page9_txt = 'Help'
//
bool   page1_enabled = true;  // Set to false to remove/disable each command as required 
bool   page2_enabled = true;
bool   page3_enabled = true;
bool   page4_enabled = true;
bool   page5_enabled = true;
bool   page6_enabled = true;
bool   page7_enabled = false; // Example of switching off Page-7
bool   page8_enabled = true;
bool   page9_enabled = true;
String siteheading   = "My Webserver";              // Main heading for each page
String subheading    = "My Webserver Sub-Heading";  // Sub heading for pages as chosen
String sitetitle     = "Webserver";                 // Appears on browser tabs and when minimised
String yourcopyright = "My System";                 // Your own copyright string
String siteversion   = "v1.0";                      // Version of your webserver
String webpage       = "";                          // General purpose variable to hold the HTML code
#define sitewidth 1024                              // Adjust site page width as required
//#define sitewidth 640                             // Adjust site page width as required (example)
//#define sitewidth 800                             // Adjust site page width as required (example)
//#define sitewidth 1280                            // Adjust site page width as required (example)
//#define sitewidth 1920                            // Adjust site page width as required (example)

ESP8266WebServer server(80); // Start server on port 80 (default for a web-browser, change to your requirements, e.g. 8080 if your Router uses port 80
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
  webpage += "<p class='style6'><br>";
  webpage += "<a href='/command1'>Page-1</a> is an example of a table, adjust the contents and colours and styles as required.<br><br>"; // <br> is the HTML CR
  webpage += "<a href='/command2'>Page-2</a> is an example of a table, but with a changed style and font, see the style section in the footer section.<br><br>";
  webpage += "<a href='/command3'>Page-3</a> is an example of placing images in a table<br><br>"; 
  webpage += "<a href='/command4'>Page-4</a> is an example of placing HTML Embedded images in a table, to add you own images:<br>";
  webpage += " a. Select your image for Base-64 encoding<br>";
  webpage += " b. Visit this web site: <a href='http://online.base64encode.in/online/base64/character-encoding-declaration-html5'>See here</a><br>";
  webpage += " c. Either paste your image into the provided encoding box, or use the select file option to upload your image.<br>";
  webpage += " d. Copy and paste into your code the resultant HTML code and Base-64 image using the examples I have provided in this source code.<br><br>";
  webpage += "<a href='/command5'>Page-5</a> Provides examples of different HTML actions<br><br>";
  webpage += "<a href='/command6'>Page-6</a> Explains how to use the Wi-Fi Manager to get an automatic WiFi connection by the ESP8266<br>";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page1(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-1</H3>";
  webpage += "<table class='style1'>";  // Change the colours and fonts in style-1 to your requirements
  webpage += "<tr>";
  webpage += "  <th>Company</th>";
  webpage += "  <th>Contact</th>";
  webpage += "  <th>Country</th>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Alfreds Futterkiste</td>";
  webpage += "  <td>Maria Anders</td>";
  webpage += "  <td>Germany</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Centro comercial Moctezuma</td>";
  webpage += "  <td>Francisco Chang</td>";
  webpage += "  <td>Mexico</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Ernst Handel</td>";
  webpage += "  <td>Roland Mendel</td>";
  webpage += "  <td>Austria</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Island Trading</td>";
  webpage += "  <td>Helen Bennett</td>";
  webpage += "  <td>UK</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Laughing Bacchus Winecellars</td>";
  webpage += "  <td>Yoshi Tannamuri</td>";
  webpage += "  <td>Canada</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Magazzini Alimentari Riuniti</td>";
  webpage += "  <td>Giovanni Rovelli</td>";
  webpage += "  <td>Italy</td>";
  webpage += "</tr>";
  webpage += "</table>";  
  webpage += "<br>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page2(){
  append_HTML_header(); 
  webpage += "<H3>This is the server Page-2</H3>";
  webpage += "<table class='style2'>"; // Change the colours and fonts in style-2 to your requirements
  webpage += "<tr>";
  webpage += "  <th>Company</th>";
  webpage += "  <th>Contact</th>";
  webpage += "  <th>Country</th>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Alfreds Futterkiste</td>";
  webpage += "  <td>Maria Anders</td>";
  webpage += "  <td>Germany</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Centro comercial Moctezuma</td>";
  webpage += "  <td>Francisco Chang</td>";
  webpage += "  <td>Mexico</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Ernst Handel</td>";
  webpage += "  <td>Roland Mendel</td>";
  webpage += "  <td>Austria</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Island Trading</td>";
  webpage += "  <td>Helen Bennett</td>";
  webpage += "  <td>UK</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Laughing Bacchus Winecellars</td>";
  webpage += "  <td>Yoshi Tannamuri</td>";
  webpage += "  <td>Canada</td>";
  webpage += "</tr>";
  webpage += "<tr>";
  webpage += "  <td>Magazzini Alimentari Riuniti</td>";
  webpage += "  <td>Giovanni Rovelli</td>";
  webpage += "  <td>Italy</td>";
  webpage += "</tr>";
  webpage += "</table>";  
  webpage += "<br>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page3(){
  String iconfile1, iconfile2, iconfile3, iconfile4;
  iconfile1 = "http://icons-ak.wxug.com/i/c/k/sunny.gif";
  iconfile2 = "http://icons-ak.wxug.com/i/c/k/cloudy.gif";
  iconfile3 = "http://icons-ak.wxug.com/i/c/k/rain.gif";
  iconfile4 = "http://icons-ak.wxug.com/i/c/k/snow.gif";
  append_HTML_header(); 
  webpage += "<P>This is the server Page-3</p>";
  webpage += "<table class='style3'>"; // Change the colours and fonts in style-3 to your requirements
  webpage += "<tr>";
  webpage += "  <td><img src='"+iconfile1+"' alt='icon description if no connection' style='width:100px;height:100px;'></td>";
  webpage += "  <td><img src='"+iconfile2+"' alt='icon description if no connection' style='width:100px;height:100px;'></td>";
  webpage += "  <td><img src='"+iconfile3+"' alt='icon description if no connection' style='width:100px;height:100px;'></td>";
  webpage += "  <td><img src='"+iconfile4+"' alt='icon description if no connection' style='width:100px;height:100px;'></td>";
  webpage += "</tr>";
  webpage += "</table>";
  webpage += "<br>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page4(){
  append_HTML_header(); 
  webpage += "<P>This is the server Page-3 with examples of HTML5 embedded images</p>";
  webpage += "<table class='style3'>"; // Change the colours and fonts in style-3 to your requirements
  webpage += "<tr>";
  webpage += "  <td>";
  clear();
  webpage += "  </td>";
  webpage += "  <td>";
  cloudy();
  webpage += "  </td>";
  webpage += "  <td>";
  chancesnow();
  webpage += "  </td>";
  webpage += "  <td>";
  chancerain();
  webpage += "  </td>";
  webpage += "  <td>";
  sunny();
  webpage += "  </td>";
  webpage += "</tr>";
  webpage += "</table>";
  webpage += "<br>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page5(){
  append_HTML_header(); 
  webpage += "<H1>Your Title Here</H1>";
  webpage += "<BODY BGCOLOR='FFFFFF'>"; 
  webpage += "<CENTER><IMG SRC='clouds.jpg' ALIGN='BOTTOM'></CENTER>";
  webpage += "<HR>";
  webpage += "<a href='http://somegreatsite.com'>Link Name</a>";
  webpage += "is a link to another nifty site";
  webpage += "<H1>This is a Header</H1>";
  webpage += "<H2>This is a Medium Header</H2>";
  webpage += "Send me mail at <a href='mailto:support@yourcompany.com'>";
  webpage += "support@yourcompany.com</a>";
  webpage += "<P> This is a new paragraph!";
  webpage += "<P> <B>This is a new paragraph!</B>";
  webpage += "<BR> <B><I>This is a new sentence without a paragraph break, in bold italics.</I></B>";
  webpage += "<HR>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page6(){
  append_HTML_header(); 
  webpage += "<P class='style6'>Using the Wi-Fi Manager</p>";
  webpage += "<P class='style6'>";
  webpage += "Stage-1 include this command ( wifiManager.resetSettings(); ) if your using a new ESP8266 that contains no previous Wi-Fi credentials (SSID and PASSWORD)<br><br>";
  webpage += "LINE-55 should look like this wifiManager.resetSettings();<br><br>";
  webpage += "Stage-2 Compile and upload the code<br><br>";
  webpage += "Stage-3 Watch your list of Wi-Fi access points, on Windows PC's hover your mouse over the Wi-Fi icon, you should see ESP8266_AP as an available source<br><br>";
  webpage += "Stage-4 Disconnect your PC from your current Wi-Fi service, now connect to ESP8266_AP<br><br>";
  webpage += "Stage-5 As soon as your PC makes a connection it will launch a Web-Browser, follow the instructions, it automatics scans for services, select<br>";
  webpage += "your desired Wi-Fi service (the one you just disconnected from, then enter your Wi-Fi password, it will then disconnect you<br><br>";
  webpage += "Stage-6 Now re-connect to your normal Wi-Fi service and now when the ESP8266 starts it will automatically connect to the Wi-Fi.<br>";
  webpage += "and there is no need to include const char *ssid = \"your_ssid\"; and const char *password  = \"your_password\"; in your code.<br><br>";
  webpage += "Stage-7 To use the Wi-Fi manager again include these libraries in your next code:<br>";
  webpage += "#include WiFiManager.h\     // https://github.com/tzapu/WiFiManager<br>";
  webpage += "#include DNSServer.h\<br>";
  webpage += "and in the program setup include these lines:<br>";
  webpage += "WiFiManager wifiManager;<br>";
  webpage += "//wifiManager.resetSettings(); // If needed!<br>";
  webpage += "wifiManager.setTimeout(180);<br>";
  webpage += "if(!wifiManager.autoConnect(\"ESP8266_AP\")) {<br>"; // ACcess point to look for to connect to!
  webpage += " Serial.println(F(\"failed to connect and timeout occurred\"))";
  webpage += " delay(6000);<br>";
  webpage += " ESP.reset(); //reset and try again<br>";
  webpage += " delay(180000);";
  webpage += "}<br>";
  webpage += "</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page7(){
  append_HTML_header(); 
  webpage += "<P>This is the server Page-7</p>";
  webpage += "<br>";
  webpage += "<P>Design your HTML then add to this section as required.</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page8(){
  append_HTML_header(); 
  webpage += "<P>This is the server Page-8</p>";
  webpage += "<br>";
  webpage += "<P>Design your HTML then add to this section as required.</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void page9(){
  append_HTML_header(); 
  webpage += "<P>This is the server Page-9</p>";
  webpage += "<br>";
  webpage += "<P>Design your HTML then add to this section as required.</p>";
  append_HTML_footer();
  server.send(200, "text/html", webpage);
}

void append_HTML_header() {
  webpage  = "<!DOCTYPE html><html><head>";
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
  webpage += "<h3>User Input, if required enter values then select Enter.<br>Expand or contract the fields as required to get inputs from a client</h3>";
  webpage += "<h3>but NOTE: this must be the first or root \"/\" page of the server or inputs don't work!<br>It appears to be a compiler fault/issue</h3>";
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

// Delete this section forward if not using HTML5 embedded images
// HTML5 icons as examples go to http://online.base64encode.in/online/base64/character-encoding-declaration-html5 
// Ppaste your image in to the template or choose your image file, then copy the base-64 code and embed in your code like this!
void clear(){
  webpage += "<img src='data:image/gif;base64,R0lGODlhMgAyANUAAAAAAP//////AO/vAN/fAM/PAL+/AK+vAJ+fAI+PAICAAHBwAGBgAFBQAEBAADAwACAgABAQAO/v79/f38/Pz7+/v6+vr5+fn4+Pj39/f3BwcGBgYFBQUEBAQ";
  webpage += "DAwMCAgIBAQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACwAAAAAMgAyAAAG/8CAcEgsGo/IpHLJbD";
  webpage += "qf0Kh0Sq1ar9hrBpAhTrJKzOdC3HaHnw8FfNx2ytxhBQCSsI0TAOArNA83ABt3ARIWRICCfXEBeXtEEmtWHgBkQnMgGB0genQdHABvQxIeIJFUF3qVjZysnB18owAedlaolBicDggFAr0FCA6cGLGzWbZ6DgS9y8wEwXSytFk";
  webpage += "degnM18wJenVVGRl8AbgACNjlvQh6GEMT304SnBwWE5vW5ubaIBMVgAAaTxafWDmwR/CZK0NQJmjYBMAAQXsGtm0AJwXVg4cEH1C6AkgBRnsKAl2h5vBjuYihoHhbuUmZSWwE6Kz01qSVnpfmbAJoMjPDB9UAvHAyKwDgQ08p";
  webpage += "1A4IZXYA1BUNABYsXbagnxUJgCBM7QUhEMUn+1iRW4oOXoUnEybp8QQAwgChA7puoKbHgzs6G9ZI+MlAKIOidhSC8OfEgrQAcwD0NfkXwFlRh6Ps1dPgLcEBDThVwhLrJ4AIY8shiKCH3+YqxCB5jsAggYHXCRiQLrrG1mkpq";
  webpage += "Ycw1FmaiC2EVDYUs0SnQgYOPz9wyAA1pZALw1EfEqnoTKOvg64P8SME0aAibuCcQUwn8p0KHE5zF6Ic+3fx7+PLn0+/vv37+PNPCQIAOw=='";
  webpage += "width='150' height='150' alt='embedded folder icon'>"; 
}

void cloudy(){
  webpage += "<img src='data:image/gif;base64,R0lGODlhMgAyAMQAAAAAAP///+/v79/f38/Pz7+/v6+vr5+fn4+Pj4CAgH9/f3BwcGBgYFBQUEBAQDAwMCAgIBAQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  webpage += "AAAAAAAACwAAAAAMgAyAAAF/2AgjmRpnmiqrmzrvnAsz3Rt33iu73zv/8CgcEgcCRAOgHL5QAyKishyOlUIgoKHEoIgkAgIiPJx9WWVCBVCSvY1ABHviiB19ApKgwsP0O+SDDAMAA82BwsODgoGSnIuA3kKiQsHZSsGYlQAED";
  webpage += "JamhFpKoNwDAkJbwB2MaMNpgxSAIEoCkoMlgEEDwsyCRCOAQKjuyaQsScCBTIFtyMJjSaDhUWAJlJ+RIwRJkpFI0pPJNzdAUrJ4QDMQt8lYgfd2SYLqd3UJcUJRAfrJrQADeA+BqAadkKeEgcJDBQwh2yhw4cQl4lYaCBBklo";
  webpage += "rCnjSxLGjxy3X5ihocPGjySUOGhUo+DWupcuXMGPKnEmzps2bOHPGCAEAOw=='";
  webpage += "width='150' height='150' alt='embedded folder icon'>"; 
}

void sunny(){ // This is the sunny icon
  webpage += "<img src='data:image/gif;base64,R0lGODlhMgAyAMQeAEBAQL+/v39/f+/v75+fnxAQEDAwMCAgIM/Pz9/f32BgYFBQUK+vrxAQAICAAL+/ADAwAGBgAM/PAHBwcO/vAI+Pj6+vACAgAEBAAN/fAJ+fAHBwAAAAAP//";
  webpage += "AP///wAAACH/C1hNUCBEYXRhWE1QPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUg";
  webpage += "WE1QIENvcmUgNS4wLWMwNjAgNjEuMTM0Nzc3LCAyMDEwLzAyLzEyLTE3OjMyOjAwICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8";
  webpage += "cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdFJl";
  webpage += "Zj0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlUmVmIyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ1M1IE1hY2ludG9zaCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDpE";
  webpage += "OURGRDQ5RTFEQkExMUUwQTNDOERGQURFNkYxNTBBMyIgeG1wTU06RG9jdW1lbnRJRD0ieG1wLmRpZDo0NEI4NEZBQzFEQkMxMUUwQTNDOERGQURFNkYxNTBBMyI+IDx4bXBNTTpEZXJpdmVkRnJvbSBzdFJlZjppbnN0YW5j";
  webpage += "ZUlEPSJ4bXAuaWlkOkQ5REZENDlDMURCQTExRTBBM0M4REZBREU2RjE1MEEzIiBzdFJlZjpkb2N1bWVudElEPSJ4bXAuZGlkOkQ5REZENDlEMURCQTExRTBBM0M4REZBREU2RjE1MEEzIi8+IDwvcmRmOkRlc2NyaXB0aW9u";
  webpage += "PiA8L3JkZjpSREY+IDwveDp4bXBtZXRhPiA8P3hwYWNrZXQgZW5kPSJyIj8+Af/+/fz7+vn49/b19PPy8fDv7u3s6+rp6Ofm5eTj4uHg397d3Nva2djX1tXU09LR0M/OzczLysnIx8bFxMPCwcC/vr28u7q5uLe2tbSzsrGw";
  webpage += "r66trKuqqainpqWko6KhoJ+enZybmpmYl5aVlJOSkZCPjo2Mi4qJiIeGhYSDgoGAf359fHt6eXh3dnV0c3JxcG9ubWxramloZ2ZlZGNiYWBfXl1cW1pZWFdWVVRTUlFQT05NTEtKSUhHRkVEQ0JBQD8+PTw7Ojk4NzY1NDMy";
  webpage += "MTAvLi0sKyopKCcmJSQjIiEgHx4dHBsaGRgXFhUUExIREA8ODQwLCgkIBwYFBAMCAQAAIfkEAQAAHgAsAAAAADIAMgAABf+gJ45kaZ5oqq5s675wLM90bdNDUQw3HAAIUoDDCZAWC17vtOAYhESjiEEMLk2E6GhYHAE4hyvq";
  webpage += "wFFstZ4EkSBOFABKj4CYEHGlCs6ORACwZwhEBkoDRAtfRIkABRwTfIY1FYI8CWSJl5cLdR5ZYFY0nQYVjBwNERoPHR0PGhENRAUEoXE1nUQNDhSqu7sUDq+Jg1dNHBAZvMi7GRBEB7QvExwLDCNUxbrJ2RTMHNR2CgCbKsRg";
  webpage += "AgiMENjZ2swFCRWWXSsDBAaYHBLr+h0S9wcVMBAoIBVh374IiRRIkWHtmMF1/brZiAbh4T5mjmp82WBR3wYOAGCAA0ByEQcHHdf/OdBTkqSZFPeIoEyZbGVMFQQE6NRJZiZNXisP7NT5x8WXgj95IQxZY86FpLwucBBQI0Ee";
  webpage += "DqmgPiASjiEiIhigdsBwyY8LeIkKELOQ1IIhUnq8qVD0x16DfCklvHrCCRHVFQzMkThXCu9DvXo+pQnwzMUASw3YGrQAjENRGwPs6QGbNdkDsnosXZ6ReQ0CzRwuRHDw4IGDCFIFIShtuarmol9jEvnrgTbvGHNqiyjUSAAA";
  webpage += "zQYACGCUcbg9pjIGCJArh44dNHn2jBhQQfENMi893BGhRriYR/LEo/HwJcx5EnP4Xk9vzbsYBILPpPegIPx7FDlo99+ABBZo4IEIJqjgAwshAAA7'";
  webpage += "width='150' height='150' alt='embedded folder icon'>"; 
}

void chancerain(){
  webpage += "<img src='data:image/gif;base64,R0lGODlhMgAyAPcAAAAAAAEBAQICAgMDAwQEBAUFBQYGBgcHBwgICAkJCQoKCgsLCwwMDA0NDQ4ODg8PDxAQEBERERISEhMTExQUFBUVFRYWFhcXFxgYGBkZGRoaGhsbGxwcHB0d";
  webpage += "HR4eHh8fHyAgICEhISIiIiMjIyQkJCUlJSYmJicnJygoKCkpKSoqKisrKywsLC0tLS4uLi8vLzAwMDExMTIyMjMzMzQ0NDU1NTY2Njc3Nzg4ODk5OTo6Ojs7Ozw8PD09PT4+Pj8/P0BAQEFBQUJCQkNDQ0REREVFRUZGRkdHR";
  webpage += "0hISElJSUpKSktLS0xMTE1NTU5OTk9PT1BQUFFRUVJSUlNTU1RUVFVVVVZWVldXV1hYWFlZWVpaWltbW1xcXF1dXV5eXl9fX2BgYGFhYWJiYmNjY2RkZGVlZWZmZmdnZ2hoaGlpaWpqamtra2xsbG1tbW5ubm9vb3BwcHFxcX";
  webpage += "JycnNzc3R0dHV1dXZ2dnd3d3h4eHl5eXp6ent7e3x8fH19fX5+fn9/f4CAgIGBgYKCgoODg4SEhIWFhYaGhoeHh4iIiImJiYqKiouLi4yMjI2NjY6Ojo+Pj5CQkJGRkZKSkpOTk5SUlJWVlZaWlpeXl5iYmJmZmZqampubm5y";
  webpage += "cnJ2dnZ6enp+fn6CgoKGhoaKioqOjo6SkpKWlpaampqenp6ioqKmpqaqqqqurq6ysrK2tra6urq+vr7CwsLGxsbKysrOzs7S0tLW1tba2tre3t7i4uLm5ubq6uru7u7y8vL29vb6+vr+/v8DAwMHBwcLCwsPDw8TExMXFxcbGx";
  webpage += "sfHx8jIyMnJycrKysvLy8zMzM3Nzc7Ozs/Pz9DQ0NHR0dLS0tPT09TU1NXV1dbW1tfX19jY2NnZ2dra2tvb29zc3N3d3d7e3t/f3+Dg4OHh4eLi4uPj4+Tk5OXl5ebm5ufn5+jo6Onp6erq6uvr6+zs7O3t7e7u7u/v7/Dw8P";
  webpage += "Hx8fLy8vPz8/T09PX19fb29vf39/j4+Pn5+fr6+vv7+/z8/P39/f7+/v///ywAAAAAMgAyAAAI/wD/CRxIsKDBgwgTKlzIsKHDhxAjSpxIsaLFixgzatzI8eGrP1CAAIHy59W7jgnf/YEAoKXLlhDAnERJ8BkIAA2gSGJFjZq";
  webpage += "uT10aAIDwi6bAZyyFHOvJlOmxLi0/0XzHslDTq0wLDX2GEgyALljDUrsDAEjHbwA2LBWLtQaAohXffYIDBMyjPwDusA0rCQCUuXUffXu48qVLXXvDGnYJZ6ZCrw26fKL2SY3QxGFR+J1cWSgMxwfhAECBuCkrFJixCuHZ9Jhm";
  webpage += "swh/4VybuvZV1wCkHvRq1bbvpp8AwEAIosHv40w1IwRQAzlyKAC4GmTu/LgQAIMN3qz+ewMAhLy519wODgUh2ga0xYvFDTf0aNbqserSXP5xyxqF4ItnVQh6WdAIvXKTYd4tZqBLDWhmGAiPQPTMI2CIBAQEIEwIQIUStiQhE";
  webpage += "DDAJCFJ7V1EFXYDPVIWQUAA0KBRXv0x0IjZ/SPbcEY9c6FjosFB0E0hdpSibv/YCIFjeNVHU3CwCfTjixBAEGNH79wk3T+vCEdQi0b9gxcYL/I4kGwgALgRWkMOtCWKALySJXQr/vNNkzEimSWYBEHnokAjTolSh+3ZCAJBJu";
  webpage += "qY5TttCvSJmoCKmeWijDbq6KOQRipplgEBADs='";
  webpage += "width='150' height='150' alt='embedded folder icon'>"; 
}

void chancesnow(){
  webpage += "<img src='data:image/gif;base64,R0lGODlhMgAyAMQAAAAAAP///+/v79/f38/Pz7+/v6+vr5+fn4+Pj39/f3BwcGBgYFBQUEBAQDAwMCAgIBAQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  webpage += "AAAAAAACwAAAAAMgAyAAAF/2AgjmRpnmiqrmzrvnAsz3Rt1wmQ3Hy+8zLBQOQTDQTAlsABIQSKBIgDmVQtAU1fFDCtrq4QBoAB4VK9Vgdgve6iR+Tz6NqWiwSABlBtQIndJQd5NAgMQwEKAAooRScLOiIFDT8tZToCBlyMkCcP";
  webpage += "AAUCjwAPLwQNaw+CAIcljSUDawmWC6wuBp5sByeuJKprDQU1ib+1RJwkBGprizMFCcpsEAlnA2INTneibKMLBnYqmWwOCQano7rDbAwCCJYMBQdkbH0uAg/dcreoawwJ2m3BSDjTA0SArDW6RGyBkPCNiRwLSiSK6PCEGAQlCg";
  webpage += "yq+FBRoDEcX52CwMremG/CvLqVMLiNITxcWDCaKCDTBaw2CZwcsHQNGqoDyh4EGxDPUjErz7axETrigKcHCKjsXGMJFa0gOajWHMErAEs2OWkYrMqs1TES6SBsfeH0Vxl6ZimRyAQBl4OALsSMMnBzk9w5a9i5eyHrhyCCHf+O";
  webpage += "4OM1UVkWAs48UiziD0rHI47QUIN3DjRAIzSSAoKNBB1x31Q6BCNGHuiQYAhoKfO64pImTyBFqW37UCPNIf0GZ9F1uPHjyJMrX85cRAgAOw=='";
  webpage += "width='150' height='150' alt='embedded folder icon'>"; 
}

