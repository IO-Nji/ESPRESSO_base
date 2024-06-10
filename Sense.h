// #include <Wire.h>
// #include <Adafruit_APDS9960.h>
// #include <VL53L0X_mod.h>

// VL53L0X_mod sensor;
// Adafruit_APDS9960 apds;
// String apdsStatus;

// void senseSetup() {
//   Wire.begin();

//   // // Gesture Sensor Set Up
//   // if (!apds.begin()) {
//   //   String apdsStatus = "APDS Sensor FAIL!";
//   //   // while (1)
//   //     // ;
//   // }

//   // sensor.setTimeout(500);
//   // if (!sensor.init()) {
//   //   Serial.println("ToF Sensor FAIL!");
//   //   // while (1) {}
//   // }
  
//   sensor.setMeasurementTimingBudget(200000);
//   sensor.startContinuous(200);
//   Serial.println("SENSORS initialized!");
// }

// uint8_t getGesture() {
//   // Get Data from APDS Sensor
//   // String gesture;
//   //read a gesture from the device
//   uint8_t apdsGest = apds.readGesture();
//   // APDS9960_DOWN
//   // APDS9960_UP
//   // APDS9960_LEFT
//   // APDS9960_RIGHT

//   return apdsGest;
// }

// uint16_t getDistance() {
//   uint16_t NewMeasurement = sensor.readRangeSingleMillimeters();
//   return NewMeasurement;
// }
