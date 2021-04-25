#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servonum = 0;

int servoLow = 113;
int servoHigh = 98;

int menu = 0;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

int calibrateServo(int pinNum, int microSecs, int servoMove)
{
  pwm.setPWM(pinNum, 0, microSecs);  //.. and sends it to the servo
  Serial.print("pinNum is: ");
  Serial.print(pinNum);
  Serial.print(" microSecs: ");
  Serial.println(microSecs);
  delay(1000);
  if (servoMove == 0) {             //If user sends the value "0" then it permanently sets the pen height             
    int servoLow = microSecs;           //Sets the new "servoLow" variable to the pen height that was just chosen
    int servoHigh = microSecs - 400;     //Sets the "servoHigh" variable to X positions above servoLow
//          servoC.setPWM(servoHigh);           //Move the servo to servoHigh location.
//          Serial.print("servoLow: ");
//          Serial.println(servoLow);
//          Serial.print("servoHigh: ");
//          Serial.println(servoHigh);
    String note;
    Serial.println("Change these variable in the program if you would like to save them permanently.");
    switch (pinNum)
    {
      case 0:
        note = "C5";
        break;
      case 1:
        note = "C#5";
        break;
      case 2:
        note = "D5";
        servoHigh = microSecs + 400;
        break;
      case 3:
        note = "D#5";
        break;
      case 4:
        note = "E5";
        break;
      case 5:
        note = "F5";
        servoHigh = microSecs + 400;
        break;
      case 6:
        note = "F#5";
        break;
      case 7:
        note = "G5";
        break;
      case 8:
        note = "G#5";
        break;
      case 9:
        note = "A6";
        servoHigh = microSecs + 400;
        break;
      case 10:
        note = "A#6";
        servoHigh = microSecs + 400;
        break;
      case 11:
        note = "B6";
        break;
      case 12:
        note = "C6";
        servoHigh = microSecs + 400;
        break;
      case 13:
        note = "C#6";
        break;
    }
    Serial.print("Servo ");
    Serial.print(note);
    Serial.print(" low position is: ");
    Serial.println(servoLow);
    // Test the servo up down a couple times with the new values.
//    pwm.setPWM(pinNum, servoLow); 
//    delay(1000);
//    pwm.setPWM(pinNum, servoHigh);
//    delay(1000);
//    pwm.setPWM(pinNum, servoLow); 
//    delay(1000);
//    pwm.setPWM(pinNum, servoHigh);
//    delay(1000);
    return 0;
  }
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  if( menu == 0){
    //Prints the menu to the serial port
    Serial.flush();
    Serial.println("Select an option:");
    Serial.println("-----------------");
    Serial.println("1) Calibrate Servo Height for Servo C5");
    Serial.println("2) Calibrate Servo Height for Servo C#5");
    Serial.println("3) Calibrate Servo Height for Servo D5");
    Serial.println("4) Calibrate Servo Height for Servo D#5");
    Serial.println("5) Calibrate Servo Height for Servo E5");
    Serial.println("6) Calibrate Servo Height for Servo F5");
    Serial.println("7) Calibrate Servo Height for Servo F#5");
    Serial.println("8) Calibrate Servo Height for Servo G5");
    Serial.println("9) Calibrate Servo Height for Servo G#5");
    Serial.println("10) Calibrate Servo Height for Servo A6");
    Serial.println("11) Calibrate Servo Height for Servo A#6");
    Serial.println("12) Calibrate Servo Height for Servo B6");
    Serial.println("13) Calibrate Servo Height for Servo C6");
    Serial.println("14) Calibrate Servo Height for Servo C#6");
//    Serial.println(") Play C Chord");
    Serial.flush();
    
    while (!Serial.available()) {}  //Waits for an input on the serial device
    menu = Serial.parseInt();       //Takes the Serial input and looks for an integer
    Serial.flush();
  }
  if(menu >= 1 && menu <= 14){
    Serial.println("Centering Servo...");
    int servoHeight = 1300;
 //   servoC.setPWM(servoHeight); //Sends the default Servo center height to the servo, to calibrate

    int calibrating = 1;
    while (calibrating == 1) {          //While loop that will continue until "0" is sent in the serial port
      Serial.println("Enter servo low height in microseconds between 500 and 2500:");
      Serial.println("Enter 0 to set and save servo height.");
      while (!Serial.available()) {}    //Waits for an input on the serial device
      int servoMove = Serial.parseInt();  //Finds the input variable sent through serial
      Serial.flush(); 
      if (servoMove != 0){
        servoHeight = servoMove;                      //Adds the variable to the current height variable..
        calibrating = calibrateServo(menu-1, servoHeight, 1);
      }
      else{
        calibrating = calibrateServo(menu-1, servoHeight, 0);
      }
    }
    Serial.print("Setting height to:");
    Serial.println(servoHeight); 
    menu = 0;   //Sets the menu variable back to 0
  }
}
