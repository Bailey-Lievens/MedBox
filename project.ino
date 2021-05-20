#include <ESP8266WiFi.h>

//Call to ESpressif SDK
extern "C" {
  #include <user_interface.h>
}

//Set ssid and password
const char* ssid     = "BaileyTest";
const char* password = "Welkom01";

int timeDelays[4] = {1000, 2000, 3000}; //Real times should be 14400000, 21600000, 50400000 (in this order) equates to 4hours 6hours 14hours

//Set unique mac adress
uint8_t mac[6] {0x5C, 0xCF, 0x7F, 0x78, 0x47, 0x37};

//Set host name
const char* host = "medbox.baileylievens.be";

//Used to read the info from online
String line = "";

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
  
void setup() {
  Serial.begin(115200);
  Serial.println();
  
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
  //@Ellen zet hier code om die servo te draaien zodat de volgende container steeds opengaat, wss gelek 15° elke keer ofzo
  Serial.println("Next pill container opened");
}

//Close the pill box
void closePillBox(){
  //@Ellen zet hier code om die servo volledig terug te draaien, aka sluit de pillen doos
  Serial.println("Pill box closed");  
}

//Set the lcd screen text
void setLcdText(String text){
  //@Ellen zet hier code om de tekst op die lcd te veranderen naar de tekst die word meegegeven als parameter 
  Serial.println("Text changed to: " + text);
}
