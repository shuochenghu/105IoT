#include <Bridge.h>
#include <Temboo.h>
#include "utility/TembooGPIO.h"
#include "TembooAccount.h" // Contains Temboo account information  
 
// The number of times to trigger the action if the condition is met
// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

// Declaring sensor configs
TembooGPIOConfig tmb_mq4Config;

// Declaring TembooSensors
TembooSensor tmb_mq4;

void setup() {
  Serial.begin(9600);

  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
  
  // Initialize sensors and configs
  tembooAnalogGPIOInit(&tmb_mq4Config, &tmb_mq4, A0, 0, INPUT);

  Serial.println("Setup complete.\n");
}

void loop() {
  int sensorValue = tmb_mq4.read(&tmb_mq4Config);
  Serial.println("Sensor: " + String(sensorValue));
  if (sensorValue >= 300) {
    if (calls < maxCalls) {
      Serial.println("\nTriggered! Calling SetStatus Choreo...");
      runSetStatus(sensorValue);
      calls++;
    } else {
      Serial.println("\nTriggered! Skipping to save Temboo calls. Adjust maxCalls as required.");
    }
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
  SetStatusChoreo.addInput("Message", "Gas  Gas Detect");
  SetStatusChoreo.addInput("AccessToken", "EAAJ8vfziqfoBAPim32enHhazpHMFJBCrqjpZBl1ZCpi86aqMrCiKT60VraP8xZCJNsRvDU4ZBpbmysaxKiThtkx7ywBj7O2gQHpfHgM1WjQdZC0hJ7zs01CosfjWvFQuJrjLN0mOIAyXOOmkeGIUk1LZCU7PhCiVcZD");
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
