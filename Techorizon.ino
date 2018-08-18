#include <Servo.h>
Servo myservo;  // create servo object to control a servo
const int xpin = A1;
const int ypin = A2;
const int knockSensor = A0;  // the piezo is connected to analog pin 0
const int threshold = 15;   // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;      // variable to store the value read from the sensor pin
int pos = 0;                // variable to store the servo position
int prepos = 0;
int pxt = 25;
int x, y;
int pyt = 25;
int nxt = -25;
void servom(int);

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
  x = analogRead(xpin)  ;
  y = analogRead(ypin)  ;
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  // Headlamp Positioning

  if ( x > 0 && x < pxt )
    servom(90);
  else if (x > pxt && y > pyt)
    servom(45);
  else if (x > pxt && y < pyt)
    servom(0);
  else if (x < nxt && y > pyt)
    servom(135);
  else if (x < nxt && y < pyt)
    servom(180);
  else
    delay(10000);




  // Accident Detection

  sensorReading = analogRead(knockSensor);
  if (sensorReading >= threshold) {
    if ( x > pxt || x < nxt )
      Serial.println("Accident Detected. Contacting Priority Contacts");
  }

  delay(5000);  // delay to avoid overloading the serial port buffer

}

void servom(int pos) {
  int i = 0;
  if ( prepos > pos ) {
    for (i = prepos; i >= pos; i -= 1)
      myservo.write(i);              // tell servo to go to position in variable 'pos'
    delay(10000);
  }
  else if (prepos < pos) {
    for (i = prepos; i <= pos; i += 1)
      myservo.write(i);              // tell servo to go to position in variable 'pos'
    delay(10000);
  }
  else
    delay(10000);
}
