#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"

#include "esp32-hal-ledc.h"

DNSServer dnsServer;
AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "relay";
const char* PARAM_INPUT_2 = "state";

// Set to true to define Relay as Normally Open (NO)
#define RELAY_NO    true

// Set number of relays
#define NUM_RELAYS  4

// Assign each GPIO to a relay
int relayGPIOs[NUM_RELAYS] = {D3, D4, D5, D6};

int buttonStates[4] = {1, 1, 1, 1};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    .push-button {background-color: #2196F3; border: none; color: white; padding: 20px 40px; font-size: 2.0rem; border-radius: 10px; cursor: pointer; transition: background-color 0.2s;}
    .push-button:active {background-color: #0b7dda;}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
  xhr.send();
}
function sendRequest(element, state) {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?relay=" + element.id + "&state=" + state, true);
  xhr.send();
}</script>
</body>
</html>
)rawliteral";

bool flag_start = false;

// PWM Code
const int LEDPin = D2;  /* GPIO16 */
int dutyCycle;
/* Setting PWM Properties */
const int PWMFreq = 5000; /* 5 KHz */
const int PWMChannel = 0;
const int PWMResolution = 10;
// const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1); // 2^10 = 1024 . Lets fix it to 500
const int MAX_DUTY_CYCLE = 500;

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER")
  {
    String buttons ="";
    for(int i=1; i<=NUM_RELAYS; i++)
    {
      String relayStateValue = relayState(i);
      if(i == 1)
      {
        // buttons+= "<h4>LEFT - " + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
        //<button class="push-button" id="13" onmousedown="sendRequest(1)" onmouseup="sendRequest(0)" onmouseleave="sendRequest(0)" ontouchstart="sendRequest(1)" ontouchend="sendRequest(0)" ontouchcancel="sendRequest(0)">PUSH</button>
        buttons+= "<h4>GO</h4><button class=\"push-button\" id=\""+ String(i) +"\" ontouchstart=\"sendRequest(this, 1)\" ontouchend=\"sendRequest(this, 0)\" ontouchcancel=\"sendRequest(this, 0)\"></button>";
      }
      else if(i == 2)
      {
        //buttons+= "<h4>RIGHT - " + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
        buttons+= "<h4>BACK</h4><button class=\"push-button\" id=\""+ String(i) +"\" ontouchstart=\"sendRequest(this, 1)\" ontouchend=\"sendRequest(this, 0)\" ontouchcancel=\"sendRequest(this, 0)\"></button>";
      }
      else if(i == 3)
      {
        //buttons+= "<h4>FORWARD - " + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
        buttons+= "<h4>LEFT</h4><button class=\"push-button\" id=\""+ String(i) +"\" ontouchstart=\"sendRequest(this, 1)\" ontouchend=\"sendRequest(this, 0)\" ontouchcancel=\"sendRequest(this, 0)\"></button>";
      }
      else if(i == 4)
      {
        //buttons+= "<h4>BACK - " + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
        buttons+= "<h4>RIGHT</h4><button class=\"push-button\" id=\""+ String(i) +"\" ontouchstart=\"sendRequest(this, 1)\" ontouchend=\"sendRequest(this, 0)\" ontouchcancel=\"sendRequest(this, 0)\"></button>";
      }
    }
    return buttons;
  }
  return String();
}

void execCmd(int rel, int stat)
{
  if(rel == 4)
  {
    if(stat == 1)
    {
      digitalWrite(relayGPIOs[0], HIGH);
      digitalWrite(relayGPIOs[1], LOW);
      digitalWrite(relayGPIOs[2], LOW);
      digitalWrite(relayGPIOs[3], LOW);
      flag_start = true;
    }
    else
    {
      // digitalWrite(relayGPIOs[0], LOW);
      // digitalWrite(relayGPIOs[1], LOW);
      // digitalWrite(relayGPIOs[2], LOW);
      // digitalWrite(relayGPIOs[3], LOW);
      flag_start = false;
    }
  }
  else if(rel == 3)
  {
    if(stat == 1)
    {
      digitalWrite(relayGPIOs[0], LOW);
      digitalWrite(relayGPIOs[1], HIGH);
      digitalWrite(relayGPIOs[2], LOW);
      digitalWrite(relayGPIOs[3], LOW);
      flag_start = true;
    }
    else
    {
      // digitalWrite(relayGPIOs[0], LOW);
      // digitalWrite(relayGPIOs[1], LOW);
      // digitalWrite(relayGPIOs[2], LOW);
      // digitalWrite(relayGPIOs[3], LOW);
      flag_start = false;
    }
  }
  else if(rel == 2)
  {
    if(stat == 1)
    {
      digitalWrite(relayGPIOs[0], LOW);
      digitalWrite(relayGPIOs[1], LOW);
      digitalWrite(relayGPIOs[2], HIGH);
      digitalWrite(relayGPIOs[3], LOW);
      flag_start = true;
    }
    else
    {
      // digitalWrite(relayGPIOs[0], LOW);
      // digitalWrite(relayGPIOs[1], LOW);
      // digitalWrite(relayGPIOs[2], LOW);
      // digitalWrite(relayGPIOs[3], LOW);
      flag_start = false;
    }
  }
  else if(rel == 1)
  {
    if(stat == 1)
    {
      digitalWrite(relayGPIOs[0], LOW);
      digitalWrite(relayGPIOs[1], LOW);
      digitalWrite(relayGPIOs[2], LOW);
      digitalWrite(relayGPIOs[3], HIGH);
      flag_start = true;
    }
    else
    {
      // digitalWrite(relayGPIOs[0], LOW);
      // digitalWrite(relayGPIOs[1], LOW);
      // digitalWrite(relayGPIOs[2], LOW);
      // digitalWrite(relayGPIOs[3], LOW);
      flag_start = false;
    }
  }
}

/*
String relayState(int numRelay){
  if(RELAY_NO){
    if(digitalRead(relayGPIOs[numRelay-1])){
      return "";
    }
    else {
      return "checked";
    }
  }
  else {
    if(digitalRead(relayGPIOs[numRelay-1])){
      return "checked";
    }
    else {
      return "";
    }
  }
  return "";
}
*/

String relayState(int numRelay){
  if(RELAY_NO){
    if(digitalRead(buttonStates[numRelay-1])){
      return "";
    }
    else {
      return "checked";
    }
  }
  else {
    if(digitalRead(buttonStates[numRelay-1])){
      return "checked";
    }
    else {
      return "";
    }
  }
  return "";
}

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");

    response->print(index_html);
    //response->print("<!DOCTYPE html><html><head><title>Captive Portal</title></head><body>");
    //response->print("<p>This is out captive portal front page.</p>");
    //response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    //response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    //response->print("</body></html>");
    request->send(response);
  }
};

int g_steps = 50;  // Number of steps for smooth transition
int g_delayTime = 40;//1000 / 50; // duration (ms) / steps
int millis_elapsed = 0;

void setup(){
  //your other setup stuff...

  // Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  for(int i=1; i<=NUM_RELAYS; i++)
  {
    pinMode(relayGPIOs[i-1], OUTPUT);
    if(RELAY_NO)
    {
      digitalWrite(relayGPIOs[i-1], LOW);
    }
    else
    {
      digitalWrite(relayGPIOs[i-1], HIGH);
    }
  }
  
  WiFi.softAP("esp-captive");
  dnsServer.start(53, "*", WiFi.softAPIP());
  //server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...

  Serial.begin(115200);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?relay=<inputMessage>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    String inputMessage2;
    String inputParam2;
    // GET input1 value on <ESP_IP>/update?relay=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;

      execCmd(inputMessage.toInt(), inputMessage2.toInt());
      
      /*
      if(RELAY_NO)
      {
        Serial.print("NO ");
        digitalWrite(relayGPIOs[inputMessage.toInt()-1], !inputMessage2.toInt());
      }
      else
      {
        Serial.print("NC ");
        digitalWrite(relayGPIOs[inputMessage.toInt()-1], inputMessage2.toInt());
      }
      */
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage + inputMessage2);
    request->send(200, "text/plain", "OK");
  });
  
  server.begin();

  // 配置PWM通道，频率，分辨率
  ledcSetup(PWMChannel, PWMFreq, PWMResolution);
  // 把配置好的PWM通道，分配引脚
  ledcAttachPin(LEDPin, PWMChannel);

  //ledcAttach(LEDPin, PWMFreq, PWMResolution);

  //ledcWrite(PWMChannel, 450);

  millis_elapsed = millis();
}

void rampUp(int duration) 
{
  int steps = 50;  // Number of steps for smooth transition
  int delayTime = duration / steps;
  
  for (int duty = 0; duty <= MAX_DUTY_CYCLE; duty += (MAX_DUTY_CYCLE / steps)) 
  {
    ledcWrite(PWMChannel, duty);
    delay(delayTime);
  }
}

// Function to ramp down PWM smoothly over a given duration
void rampDown(int duration) 
{
  int steps = 50;
  int delayTime = duration / steps;
  
  for (int duty = MAX_DUTY_CYCLE; duty >= 0; duty -= (MAX_DUTY_CYCLE / steps)) 
  {
    ledcWrite(PWMChannel, duty);
    delay(delayTime);
  }
}

int g_duty = 0;

void loop(){
  dnsServer.processNextRequest();
  if(millis() > (millis_elapsed + g_delayTime))
  {
    if(flag_start)
    {
      if(g_duty <= MAX_DUTY_CYCLE)
      {
        g_duty += (MAX_DUTY_CYCLE / 100);
        ledcWrite(PWMChannel, g_duty);
      }
    }
    else
    {
      if(g_duty > 0)
      {
        if((g_duty - (MAX_DUTY_CYCLE / 100)) < 0)
        {
          g_duty = 0;
        }
        else
        {
          g_duty -= (MAX_DUTY_CYCLE / 100);
        }
        ledcWrite(PWMChannel, g_duty);
      }
      else
      {
        digitalWrite(relayGPIOs[0], LOW);
        digitalWrite(relayGPIOs[1], LOW);
        digitalWrite(relayGPIOs[2], LOW);
        digitalWrite(relayGPIOs[3], LOW);
      }
    }
    millis_elapsed = millis();
  }
}
