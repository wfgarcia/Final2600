#include <WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>

int latchPin = 2;          // Pin connected to ST_CP of 74HC595（Pin12）
int clockPin = 4;          // Pin connected to SH_CP of 74HC595（Pin11）
int dataPin = 15;          // Pin connected to DS of 74HC595（Pin14）

// Define the pattern data for a smiling face
 int board[] = {                       //"^ⅴ^"
  0x24, 0x24, 0x7F, 0x24, 0x24, 0x7F, 0x24, 0x24
};
const char keys[4][4] = {
{'1', '2', '3', 'a'},
{'4', '5', '6', 'b'},
{'7', '8', '9', 'c'},
{'*', '0', '#', 'd'}
};
byte rowPins[4] = {14, 27, 26, 25}; // connect to the row pinouts of the keypad
byte colPins[4] = {13, 21, 22, 23}; // connect to the column pinouts of the keypad
// Define the data of numbers and letters, and save them in flash area
Keypad input = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// WiFi
const char *ssid = "fegm65wifi6"; // Enter your WiFi name
const char *password = "a1b2c3d4e5";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/final";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str())) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 }
 // publish and subscribe
 client.publish(topic, "ESP32 is ready to play!");
 client.subscribe(topic);

}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 client.loop();
 int cols;
  char play;

  int player = 1;

    cols = 0x01;
    for (int i = 0; i < 8; i++) {   // display 8 column data by scaning
      matrixRowsVal(board[i]);// display the data in this column
      matrixColsVal(~cols);          // select this column                   // display them for a period of time         // clear the data of this column
      delay(1);
      matrixRowsVal(0x00);
      cols <<= 1;             // shift"cols" 1 bit left to select the next column
    }

    
    play = input.getKey();
    if(player == 1){
    if(play == '1'){
      board[0] = board[0] + 0xC0;
       client.publish(topic, "1");
      client.subscribe(topic);
      player = 2;
    } 
    if(play == '2'){
    board[3] = board[3] + 0xC0;
     client.publish(topic, "2");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '3'){
    board[6] = board[6] + 0xC0;
     client.publish(topic, "3");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '4'){
    board[0] = board[0] + 0x18;
     client.publish(topic, "4");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '5'){
    board[3] = board[3] + 0x18;
     client.publish(topic, "5");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '6'){
    board[6] = board[6] + 0x18;
     client.publish(topic, "6");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '7'){
    board[0] = board[0] + 0x03;
     client.publish(topic, "7");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '8'){
    board[3] = board[3] + 0x03;
     client.publish(topic, "8");
 client.subscribe(topic);
 player = 2;
    }
    if(play == '9'){
    board[6] = board[6] + 0x03;
     client.publish(topic, "9");
 client.subscribe(topic);
 player = 2;
    }
    if(play == 'a'){
    board[0] = 0x24;
    board[3] = 0x24;
    board[6] = 0x24;
    
    }
  }
  else{
    board[0] = board[0] + 0x80;
    board[1] = board[1] + 0x40;
       client.publish(topic, "1");
      client.subscribe(topic);
      player = 1;
    } 
    if(play == '2'){
    board[3] = board[3] + 0x80;
    board[4] = board[4] + 0x40;
     client.publish(topic, "2");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '3'){
    board[6] = board[6] + 0x80;
    board[7] = board[7] + 0x40;
     client.publish(topic, "3");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '4'){
    board[0] = board[0] + 0x10;
    board[1] = board[1] + 0x08;
     client.publish(topic, "4");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '5'){
    board[3] = board[3] + 0x10;
    board[4] = board[4] + 0x08;
     client.publish(topic, "5");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '6'){
    board[6] = board[6] + 0x10;
    board[7] = board[7] + 0x08;
     client.publish(topic, "6");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '7'){
    board[0] = board[0] + 0x02;
    board[1] = board[1] + 0x01;
     client.publish(topic, "7");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '8'){
    board[3] = board[3] + 0x02;
    board[4] = board[4] + 0x01;
     client.publish(topic, "8");
 client.subscribe(topic);
 player = 1;
    }
    if(play == '9'){
    board[6] = board[6] + 0x02;
    board[4] = board[4] + 0x01;
     client.publish(topic, "9");
 client.subscribe(topic);
 player = 1;
    }
    if(play == 'a'){
    board[0] = 0x24;
    board[3] = 0x24;
    board[6] = 0x24;
    player = 1;
    }

  }

}

void matrixRowsVal(int value) {
  // make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  // make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}

void matrixColsVal(int value) {
  // make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, MSBFIRST, value);
  // make latchPin output high level, then 74HC595 will update the data to parallel output
  digitalWrite(latchPin, HIGH);
}