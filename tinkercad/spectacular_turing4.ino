// Arduino Code for Input Board 4
const int pedestrianSignal = 3;  // Connect to the Pedestrian input pin on the main board
const int permission = 2;
const int passingDemo = 4;

unsigned long startTime = 0;  // Variable to store the start time
unsigned long currentTime = 0;


void setup() {
  pinMode(pedestrianSignal, OUTPUT);
  pinMode(passingDemo, OUTPUT);
  pinMode(permission, INPUT);
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();  // Get the current time

  if (currentTime > 0 && currentTime < 10000) {  // Check if it's between 3 and 6 seconds
    digitalWrite(pedestrianSignal, HIGH);
  } else {
    digitalWrite(pedestrianSignal, LOW);
  }

  int permissionInput = digitalRead(permission);

  // Send the state of the car button to the main board
  Serial.print("Pedestrian: ");
  Serial.println(permissionInput);


   // Check if permission is HIGH, then set passingDemo to HIGH
  if (permissionInput == HIGH) {
    digitalWrite(passingDemo, HIGH);
    delay(500);  // Blinking interval: 500 milliseconds
    digitalWrite(passingDemo, LOW);
    delay(300);
  } else {
    digitalWrite(passingDemo, LOW);
    currentTime = 0;
  }

  delay(1000);  // Adjust delay based on your requirements
}
