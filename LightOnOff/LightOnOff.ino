void loop() {

   // Update the LEDs based on their states
  digitalWrite(led1, led1State ? HIGH : LOW); // If led1State is true, turn on LED 1
  digitalWrite(led2, led2State ? HIGH : LOW); // If led2State is true, turn on LED 2
  digitalWrite(led3, led3State ? HIGH : LOW); // If led3State is true, turn on LED 3
  digitalWrite(buzz, led4State ? HIGH : LOW); 
 

  // Wait for a little bit before checking again
  delay(1000); // Delay for 1 second
}







