/*
 * PURPOSE:
 * This is the Arduino code for a "Smart Plant" system. 
 * It reads the moisture level from a sensor. If the soil is too dry, it turns on 
 * a red LED and prints "Feed me!" to the serial monitor. If the soil is wet enough, 
 * it turns off the LED and prints "Thank you, Seymour!".
 *
 * WHAT IT TEACHES:
 * 1. Arduino Structure: The mandatory setup() and loop() functions.
 * 2. Analog vs Digital: Reading continuous data (analogRead) and turning pins on/off (digitalWrite).
 * 3. Serial Communication: Sending data back to the computer (Serial.print).
 * 4. Conditional Logic in Hardware: Using if/else to control physical components.
 */

// --- Pin Definitions ---
// The moisture sensor is connected to analog pin A0
const int sensorPin = A0; 
// The LED is connected to digital pin 13 (the built-in LED on the Arduino)
const int ledPin = 13;    

// The threshold value. If the value goes BELOW 800, the plant needs water.
// (In our Tinkercad simulation, the values might be reversed, but this is the book's logic).
const int threshold = 800; 

void setup()
{
    // Set the LED pin as an OUTPUT so we can send voltage to it
    pinMode(ledPin, OUTPUT);
    
    // Start serial communication at 9600 bits per second (baud rate)
    // This allows the Arduino to talk to the computer
    Serial.begin(9600);
}

void loop()
{
    // Read the analog value from the moisture sensor (returns a number between 0 and 1023)
    int sensorValue = analogRead(sensorPin);
    
    // Check if the plant is dry
    if (sensorValue < threshold) {
        // Plant needs water!
        digitalWrite(ledPin, HIGH); // Turn the LED ON
        Serial.println("Feed me!"); // Print the message to the computer
    } 
    else {
        // Plant has enough water
        digitalWrite(ledPin, LOW);  // Turn the LED OFF
        Serial.println("Thank you, Seymour!"); // Print the message
    }
    
    // Wait for 1 second (1000 milliseconds) before checking again
    delay(1000);
}
