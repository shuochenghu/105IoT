#include <Bridge.h>
#include <Temboo.h>
#include <limits.h>
#include "utility/TembooGPIO.h"
#include "TembooAccount.h" // Contains Temboo account information  
 
// The number of times to trigger the action if the condition is met
// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

// Declaring sensor configs
TembooGPIOConfig tmb_gasdetectorConfig;

// Declaring TembooSensors
TembooSensor tmb_gasdetector;

// Choreo execution interval in milliseconds
unsigned long choreoInterval = 300000; 
// Store the time of the last Choreo execution
unsigned long lastChoreoRunTime = millis() - choreoInterval; 

void setup() {
  Serial.begin(9600);

  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
  
  // Initialize sensors and configs
  tembooAnalogGPIOInit(&tmb_gasdetectorConfig, &tmb_gasdetector, A0, 0, INPUT);

  Serial.println("Setup complete.\n");
}

void loop() {
  if(millis() - lastChoreoRunTime >= choreoInterval) {
    int sensorValue = tmb_gasdetector.read(&tmb_gasdetectorConfig);
    Serial.println("Sensor: " + String(sensorValue));
    if (sensorValue > 120) {
      if (calls < maxCalls) {
        Serial.println("\nTriggered! Calling SetStatus Choreo...");
        runSetStatus(sensorValue);
        lastChoreoRunTime = millis();
        calls++;
      } else {
        Serial.println("\nTriggered! Skipping to save Temboo calls. Adjust maxCalls as required.");
      }
    }
  }

  if (millis() - lastChoreoRunTime >= ULONG_MAX - 10000) {
    lastChoreoRunTime = millis() - choreoInterval;
  }
  delay(250);
}

void runSetStatus(int sensorValue) {
  TembooChoreo SetStatusChoreo;

  // Invoke the Temboo client
  SetStatusChoreo.begin();

  // Set Temboo account credentials
  SetStatusChoreo.setAccountName(TEMBOO_ACCOUNT);
  SetStatusChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  SetStatusChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set Choreo inputs
  SetStatusChoreo.addInput("Message", "Gas Detect 0608");
  SetStatusChoreo.addInput("AccessToken", "EAAGDJqZBU86IBABfTw7ujndiWnXN69rlIL0BwDe2GhyWzEcSMS2202v83BxIxbFZBoZBaEhVblZBKxhn7wlb6RNzuwb9sqzktHzy1EdvALWS041LmtkB747xU7q03pICzjBGAPtxROf839Tg8hxL1znKSiTE03wZD");
  // Identify the Choreo to run
  SetStatusChoreo.setChoreo("/Library/Facebook/Publishing/SetStatus");

  // Run the Choreo
  unsigned int returnCode = SetStatusChoreo.run();

  // Read and print the error message
  while (SetStatusChoreo.available()) {
    char c = SetStatusChoreo.read();
    Serial.print(c);
  }
  Serial.println();
  SetStatusChoreo.close();
}
