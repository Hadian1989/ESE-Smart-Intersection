// Arduino Code for Input Board 1 (Master)
const int emergencySignal = 3;  // Connect to the Emergency input pin on the main board
const int permission = 2;
const int passingDemo = 4;
unsigned long startTime = 0;  // Variable to store the start time of the blinking LED
unsigned long currentTime = 0;  // Variable to store the start time of the blinking LED

const int slaveEmergencySignal = 5;  // Connect to the Emergency input pin on the slave board

void setup() {
  pinMode(emergencySignal, OUTPUT);
  pinMode(passingDemo, OUTPUT);
  pinMode(permission, INPUT);
  pinMode(slaveEmergencySignal, OUTPUT);
  Serial.begin(9600);
}

void loop() {
	currentTime = millis() - startTime; 
  if (currentTime < 5000 && currentTime > 0) {  // Check if it's between 3 and 6 seconds
    digitalWrite(emergencySignal, HIGH);
  } else {
    digitalWrite(emergencySignal, LOW);
  }
  
  int permissionInput = digitalRead(permission);

  // Send the state of the emergency button to the slave board
  Serial.print("Emergency: ");
  Serial.println(permissionInput);


  // Check if permission is HIGH, then set passingDemo to HIGH
  if (permissionInput == HIGH) {
    digitalWrite(passingDemo, HIGH);
    delay(500);  // Blinking interval: 500 milliseconds
    digitalWrite(passingDemo, LOW);
    delay(300);
  } else {
    digitalWrite(passingDemo, LOW);
    
  }


  delay(1000);  // Adjust delay based on your requirements
}