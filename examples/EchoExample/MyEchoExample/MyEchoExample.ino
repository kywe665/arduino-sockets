#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 254, 11};
char socketServer[] = "192.168.254.15";
IPAddress server(192,168,254,15);
byte subnet[] = {255, 255, 255, 0};
byte gateway[] = { 192, 168, 254, 15};
char path[] = "/websocket";
WebSocketClient socketClient;
EthernetClient nodeClient;

void setup() {
  Serial.begin(9600);
  Serial.println("hey");
  delay(1000);
  Ethernet.begin(mac, ip, gateway, subnet);
  delay(1000);
  Serial.println("connecting...");
  if (nodeClient.connect(server, 2550)) {
    Serial.println("connected");
    // Make a HTTP request:
    //nodeClient.println("GET /websocket HTTP/1.1");
    //nodeClient.println("Host: example.com");
    //nodeClient.println();
    nodeClient.println("GET /websocket HTTP/1.1");
    nodeClient.println("Host: example.com");
    nodeClient.println("Upgrade: websocket");
    nodeClient.println("Connection: Upgrade");
    nodeClient.println("Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==");
    nodeClient.println("Sec-WebSocket-Version: 13");
    nodeClient.println("Origin: http://example.com");
    nodeClient.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  //Serial.println("waiting");
  //delay(4000);
  //Serial.println("connect socket...");
  //socketClient.connect(socketServer);
  //socketClient.setDataArrivedDelegate(dataArrived);
  //socketClient.send("Hello World!");
}

void loop() {
  socketClient.monitor();
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (nodeClient.available()) {
    char c = nodeClient.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!nodeClient.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    nodeClient.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}

void dataArrived(WebSocketClient socketClient, String data) {
  Serial.println("Data Arrived: " + data);
}
