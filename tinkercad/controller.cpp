// Arduino Code for Input Board 3 (Slave)
const int inputPinEmergency = 5;  // Pin for the first input signal
const int inputPinCar = 4;  // Pin for the second input signal
const int inputPinPedestrian = 3;  // Pin for the second input signal
const int analogPinCamera = A0; // Replace A0 with the analog pin you are using
const int analogPinWeather = A1; // Replace A1 with the analog pin you are using
const int outputPinEmergency = 13; // Pin for the Emergency Permission LED
const int outputPinCar = 12; // Pin for the Normal Permission LED
const int outputPinPedestrian = 11; // Pin for the Pedestrian LED
unsigned long emergencyStartTime = 0;  // Variable to store the start time of emergency state

void setup() {
  Serial.begin(9600);
  pinMode(inputPinEmergency, INPUT);
  pinMode(inputPinCar, INPUT);  
  pinMode(inputPinPedestrian, INPUT);

  pinMode(outputPinEmergency, OUTPUT);
  pinMode(outputPinCar, OUTPUT);
  pinMode(outputPinPedestrian, OUTPUT);
}

void checkPriority() {
  Serial.print("Emergency: ");
  Serial.println(digitalRead(inputPinEmergency));
  Serial.print("Pedestrian: ");
  Serial.println(digitalRead(inputPinPedestrian));
  Serial.print("CAr: ");
  Serial.println(digitalRead(inputPinCar));

  if (digitalRead(inputPinEmergency)) {
    Serial.println("Emergency condition");
    digitalWrite(outputPinEmergency, HIGH);
    digitalWrite(outputPinCar, LOW);
    digitalWrite(outputPinPedestrian, LOW);
  } else if (digitalRead(inputPinPedestrian)) {
    Serial.println("Pedestrian condition");
    digitalWrite(outputPinCar, LOW);
    digitalWrite(outputPinPedestrian, HIGH);
    digitalWrite(outputPinEmergency, LOW);

  } else if (digitalRead(inputPinCar)){
    Serial.println("Car condition");
    digitalWrite(outputPinCar, HIGH);
    digitalWrite(outputPinPedestrian, LOW);
    digitalWrite(outputPinEmergency, LOW);

  } else{
   	digitalWrite(outputPinCar, LOW);
    digitalWrite(outputPinPedestrian, LOW);
    digitalWrite(outputPinEmergency, LOW);}
}

void loop() {
  unsigned long startTime = micros();  // Record the start time
  checkPriority();
  unsigned long executionTime = micros() - startTime;  // Calculate the execution time
  Serial.print("Execution Time (us): ");
  Serial.println(executionTime);

  delay(100); // Adjust delay based on your requirements
}