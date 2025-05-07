#include <Arduino.h>
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>
#include <Controllino.h>
#include <Ethernet.h>

// Controllino Pin Definitions
int start_switch = CONTROLLINO_R0;
int stop_switch = CONTROLLINO_R9;
int led_red = CONTROLLINO_R2;
int led_green = CONTROLLINO_R1;
int led_blue = CONTROLLINO_R3;
int emer_switch = CONTROLLINO_DI0;
int limit_b_l = CONTROLLINO_AI5; //limit_1 //Analog input from old code
int limit_b_r = CONTROLLINO_AI4; //limit_2 //Analog input from old code
int limit_f_l = CONTROLLINO_AI2; //limit_3 //Analog input from old code
int limit_f_r = CONTROLLINO_AI3; //limit_4 //Analog input from old code
//int battery_read = CONTROLLINO_A0;
//int touchless_switch = CONTROLLINO_AI0;

// Variable Definitions
long preMillis = 0;

// Ethernet Definitions
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 1);
IPAddress server(192, 168, 1, 10); // update with the IP Address of your Modbus server

// Modbus Definitions
EthernetClient ethernetClient;
ModbusTCPClient modbusTCPClient(ethernetClient);


// Function Definetions
void led_set(bool r, bool g, bool b);
void ReadAndPackSensor();
void ReadCommand();

void setup() {
  // IO Setup
  pinMode(start_switch,OUTPUT);
  pinMode(stop_switch,OUTPUT);
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(emer_switch,INPUT);

  // Set LED For Testing
  led_set(true,true,true);
}

void loop() {
  if (modbusTCPClient.connected()) {
    // Connected successfully
  } else {
    // Connection failed, try again next time
    delay(200);
    return;
  }

  // Update Sensor Data Every 50ms
  if (millis() - preMillis > 50) {
    preMillis = millis();
    ReadAndPackSensor();
  }

  ReadCommand(); // Read Commands from Server

  delay(10); // Delay to avoid bus congestion
}

void led_set(bool r, bool g, bool b) {
  digitalWrite(led_red, r);
  digitalWrite(led_blue, g);
  digitalWrite(led_green, b);
}

void ReadAndPackSensor(){
  // Read emergency switch and update Modbus coils
  modbusTCPClient.coilWrite(0, digitalRead(emer_switch));

  // Read bumper sensors and update Modbus coils
  bool t_limit_b_l = (analogRead(limit_b_l) == 0);
  modbusTCPClient.coilWrite(1, t_limit_b_l);
  bool t_limit_b_r = (analogRead(limit_b_r) == 0);
  modbusTCPClient.coilWrite(2, t_limit_b_r);
  bool t_limit_f_l = (analogRead(limit_f_l) == 0);
  modbusTCPClient.coilWrite(3, t_limit_f_l);
  bool t_limit_f_r = (analogRead(limit_f_r) == 0);
  modbusTCPClient.coilWrite(4, t_limit_f_r);
}

void ReadCommand(){
  // LED Control Commands
  if (modbusTCPClient.coilRead(10)){
    // coil10 → led_red
    led_set(true, false, false);
    modbusTCPClient.coilWrite(10, 0); 
  }
  if (modbusTCPClient.coilRead(11)){
    // coil11 → led_green
    led_set(false, true, false);
    modbusTCPClient.coilWrite(11, 0); 
  }
  if (modbusTCPClient.coilRead(12)){
    // coil12 → led_blue
    led_set(false, false, true);
    modbusTCPClient.coilWrite(12, 0); 
  }
  if (modbusTCPClient.coilRead(13)){
    // coil13 → led_off
    led_set(false, false, false);
    modbusTCPClient.coilWrite(13, 0); 
  }
  if (modbusTCPClient.coilRead(14)){
    // coil14 → led_white
    led_set(true, true, true);
    modbusTCPClient.coilWrite(14, 0);
  }
  if (modbusTCPClient.coilRead(15)){
    // coil15 → led_purple
    led_set(true, true, false);
    modbusTCPClient.coilWrite(15, 0);
  }
  if (modbusTCPClient.coilRead(16)){
    // coil16 → led_yellow
    led_set(true, false, true);
    modbusTCPClient.coilWrite(16, 0);
  }
  if (modbusTCPClient.coilRead(17)){
    // coil17 → led_indigo
    led_set(false, true, true);
    modbusTCPClient.coilWrite(17, 0);
  }

  // Motor Control Commands
  if (modbusTCPClient.coilRead(20)){
    // coil20 → start_motor
    digitalWrite(start_switch, HIGH);
    digitalWrite(stop_switch, LOW);
    delay(1000); // Wait for 1 second
    digitalWrite(start_switch, LOW);
    modbusTCPClient.coilWrite(18, 0);
  }
  if (modbusTCPClient.coilRead(21)){
    // coil21 → stop_motor
    digitalWrite(start_switch, LOW);
    digitalWrite(stop_switch, HIGH);
    delay(1000); // Wait for 1 second
    digitalWrite(stop_switch, LOW);
    modbusTCPClient.coilWrite(19, 0);
  }
}