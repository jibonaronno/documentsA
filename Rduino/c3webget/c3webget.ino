#include <WiFi.h>

// Replace with your network credentials
const char *ssid = "U+NetF3AE";
const char *password = "1A8E8E1FM@";

class JSONSTARTFLAG
{
  public:
    bool json_start;
    bool json_end;
    int _start_index;
    int _stop_index;
    bool json_complete;

    JSONSTARTFLAG()
    {
      this->json_start = 0;
      this->json_end = 0;
      this->_start_index = -1;
      this->_stop_index = -1;
      this->json_complete = false;
    };
};

// Set web server port number to 80
WiFiServer server(80);

JSONSTARTFLAG json_flag;

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output1State = "off";


// Assign output variables to GPIO pins
const int output1 = 2; 

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output1, OUTPUT);
  digitalWrite(output1, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("LOAD1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("LOAD1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            }
            //else if (header.indexOf("{") >= 0)
            else if (header.indexOf("%7B") >= 0)
            {
              json_flag._start_index = header.indexOf("%7B");
              if (header.indexOf("%7D") >= 0)
              {
                json_flag._stop_index = header.indexOf("%7D");
                json_flag.json_complete = true;
                Serial.println("\n\n\n JSON RECV \n");
                Serial.println(header.substring(json_flag._start_index, json_flag._stop_index));
              }
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #5B196A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #5B196A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>HOME AUTOMATION DUAL OUTPUT</h1>");
            
            // Display current state, and ON/OFF buttons for OUTPUT1 
            client.println("<p>LOAD1 - State " + output1State + "</p>");
           
            // If the output1State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
