#include <ESP8266WiFi.h>
#include <Servo.h>
#include <LiquidCrystal.h>

//Call to ESpressif SDK
extern "C" {
  #include <user_interface.h>
}

//Set ssid and password
const char* ssid     = "Rony De Router";
const char* password = "kpBYur5fXXBs";

int timeDelays[4] = {1000, 2000, 3000}; //Real times should be 14400000, 21600000, 50400000 (in this order) equates to 4hours 6hours 14hours

//Set unique mac adress
uint8_t mac[6] {0x5C, 0xCF, 0x7F, 0x78, 0x47, 0x37};

//Set host name
const char* host = "medbox.baileylievens.be";

//Used to read the info from online
String line = "";
int text1;
String text2 = "";

//Boolean to check if the relevant info has been reached yet
boolean reachedInfo = false;

//Delay between internet checks
int timeDelay = 0;

//Counter to hold where in the week we are
//For example 0 = monday morning, 1 = monday midday, 2 = monday evening, 3 = tuesday morning, 4 = tuesday midday, 5 = tuesday evening
int timeCounter = 0;

//Counter to hold the amount of lines read
//Starts at -1 because the website output starts with something useless
int lineCounter = -1;
Servo servo1;
int currentAngle = 180; // begin van 180 graden

//const int rs = 0, e = 16, d4 = 2, d5 = 12, d6 = 13, d7 = 15;
LiquidCrystal lcd(12, 13, 15, 16, 0, 2);

void setup() {
  Serial.begin(115200);
  Serial.println();
  servo1.attach(14); //aangesloten op pin 12
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //Set mac adress of the esp
  wifi_set_macaddr(0, const_cast<uint8*>(mac)); 
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Bezig met connecteren...");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Geconnecteerd!\nMijn IP adres: ");
  Serial.println(WiFi.localIP());
  Serial.printf("Mijn MAC adres is: %s\n", WiFi.macAddress().c_str());
  Serial.print("De gateway is: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("De DNS is: ");
  Serial.println(WiFi.dnsIP());
  Serial.println();
  Serial.println();
  }


void loop() {
  
  Serial.print("connecting to ");
  Serial.println(host);

  //Tries to connect to the host
  WiFiClient client;
  client.setTimeout(1000);
  const int httpPort = 80; //Set listening port
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  //Set the path we want to retrieve from the host
  String url = "/txt_schedule.txt";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  
  //Send a GET request to the host
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  //Read everything and store the schedule
  while(client.available()){
    line = client.readStringUntil('\n');
    text1 = line.indexOf(":");
    text2 = line.substring(text1);

    //When the start of the schedule has been reached, start concatonating it and storing the data
    if(line == "Schedule=" || reachedInfo){
      reachedInfo = true;

      if(lineCounter == timeCounter){
        setLcdText(line);//Change Lcd screen text
        openNextPillContainer();//Open next pill container
        break; //Stop the while when we have what we need 
      }
      lineCounter++;
      delay(250);
    }
  }

  //Close the connection we previously created
  Serial.println("closing connection");
  client.stop();
  
  //Delay to next connection || monday to midday//midday to evening//evening to morning
  int currentDelay = getDelay(timeCounter);

  reachedInfo = false; //Reset the boolean
  timeCounter++; //Increase the timeCounter
  lineCounter = -1; //Reset the lineCounter

  //Reset the timeCounter so that after sunday evening it goes back to monday morning
  if(timeCounter == 21){
    timeCounter = 0;
    closePillBox();//Close the pillbox again when the week is over
  }
 
  delay(currentDelay);
  Serial.println();
}

//Returns a delay relevant to the input
int getDelay(int currentTimeCounter){
  int delayToReturn = 0;
  int counter = 0;

  for(int i = 0; i < currentTimeCounter; i++){
    delayToReturn = counter;
    counter++;
    if(counter > 2){
      counter = 0;
    }
  }
  return timeDelays[delayToReturn];
}

//Open the next pill container
void openNextPillContainer(){
  for(int i=currentAngle; i>currentAngle-8.5; i--){ 
          servo1.write(i); // draai 8.5 graden verder
          delay(70); // om rustiger te draaien
        }
  currentAngle = currentAngle -8.5;
  Serial.println("Next pill container opened");
}

//Close the pill box
void closePillBox(){
  setLcdText("Closing box");
  for(int i=currentAngle; i<180 ; i++){
          servo1.write(i); // draai naar 180 graden
          delay(70);
        }
  currentAngle = 0;
  Serial.println("Pill box closed");  
}

//Set the lcd screen text
void setLcdText(String text){
  // Print the time to the LCD.
  lcd.setCursor(0,0);
  lcd.print(text);
  // printing pill name
  lcd.setCursor(0,1);
  lcd.print(text2);
  delay(7000);
  lcd.clear();
  Serial.println("Text changed to: " + text);
}
