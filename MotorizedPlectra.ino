// ALL OF THE IMPORTANT, COSTUMIZABLE STUFF ARE OVER HERE!!!

// The strength of the motor. 255 is the highest, 0 is the lowest.
// I set it to 100 because it's a nice, halfway-ish point.

#define pwmThing 100

// Setting up the BPM. Set this to the BPM of the song/solo you're doing.

int BPM = 120;

// MST stands for Motor Spinning Time. It's set in milliseconds (ms). The default is 50 milliseconds.

int MST = 20;

// This controls the type of notes in the movement array. Quarters would be 4, triplets would be 3, etc. 
// This also functions as the top number on a time measure in sheet music, hence the variable name.

int TopNumber = 4;

// The movement array. It decides what motors move when. 1 is spin, 0 is don't spin.
// Notice that the patterns are in groups of six. This is because there are six strings on a guitar.
// It is CRUCIAL that all of the patterns are the same size. This is because the code imvolves copy the patterns to the sample pattern.
// If they aren't the same size, then there will be an error.

int SamplePattern[] =
 {0, 0, 0, 0, 1, 0};
  
// Varible representing how long the pattern is. Set it to the amount of rows in SamplePattern[].

int patternLength = 1;

// The rest is just boring code stuff

// Defining all of the pin connections, so I don't have to input the numbers each time.
#define pwmA 5
#define pwmB 3
#define pwmC 6
#define pwmD 9
#define pwmE 10
#define pwmF 11
#define AA 4
#define AB 16
#define BA 2
#define BB 19
#define CA 7
#define CB 15
#define DA 8
#define DB 18
#define EA 13
#define EB 14
#define FA 12
#define FB 17

// This pin is for the piezo. The piezo will beep according to the BPM.

#define PiezoPin 1

// Spin parity (so the motor switches between 
// moving deosil and widdershins)

int spinParityA = 0;
int spinParityB = 0;
int spinParityC = 0;
int spinParityD = 0;
int spinParityE = 0;
int spinParityF = 0;

// By taking the BPM, this will calculate the amount of delay in milliseconds that we want.
// There are 60000 milliseconds in a minute.
// By dividing this by the BPM, we get how long a measure is in milliseconds.

int BPMDelay = 60000 / BPM;

// This variable combines the BPMDelay and the TopNumber to split the measure into beats.
int OtherDelay = (BPMDelay / TopNumber);


// Function that plays the notes. That's why it's called "playNotes()."
// "patternNumber" is the pattern number the motor's using. 1, 2, 3, 4 or 5.

void playNotes() {

  for(int i = 0; i < patternLength; ++i) {

    // Spin whatever motor is needed to spin
    
    if (SamplePattern[i * 6] == 1) {
      spinMotor(1);
    } if (SamplePattern[i * 6 + 1] == 1) {
      spinMotor(2);
    } if (SamplePattern[i * 6 + 2] == 1) {
      spinMotor(3);
    } if (SamplePattern[i * 6 + 3] == 1) {
      spinMotor(4);
    } if (SamplePattern[i * 6 + 4] == 1) {
      spinMotor(5);
    } if (SamplePattern[i * 6 + 5] == 1) {
      spinMotor(6);
    }

    // Delay for the motor spinning time.
    
    delay(MST);
    
    // Stops the motors. I made it its own function
    // because instead of just turning the ones on and
    // having to check which ones are moving, I instead
    // stop all of them at the same time to not worry
    // about it.
    
    stopMotors();

    // Delay for the rest of the beat.
    
    delay(OtherDelay - MST);
  }
}

// Function that stops all the motors.

void stopMotors() {
  
  // Stops all motors.
  
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
  digitalWrite(BA, LOW);
  digitalWrite(BB, LOW);
  digitalWrite(CA, LOW);
  digitalWrite(CB, LOW);
  digitalWrite(DA, LOW);
  digitalWrite(DB, LOW);
  digitalWrite(EA, LOW);
  digitalWrite(EB, LOW);
  digitalWrite(FA, LOW);
  digitalWrite(FB, LOW);
}


// Function that spins a motor.

void spinMotor(int string) {
  
  analogWrite(pwmA, pwmThing);
  analogWrite(pwmB, pwmThing);
  analogWrite(pwmC, pwmThing);
  analogWrite(pwmD, pwmThing);
  analogWrite(pwmE, pwmThing);
  analogWrite(pwmF, pwmThing);
  
  // Checks which motor is supposed to be moving, then
  // spins it.
  
  if (string == 1) {
    // The spin parity is what you think it is.
    
    if (spinParityA == 0) {
      digitalWrite(AA, HIGH);
      digitalWrite(AB, LOW);
    } else {
      digitalWrite(AA, LOW);
      digitalWrite(AB, HIGH);
    }
    
    // Changes spin parity, and sends the result
    // to the serial monitor.
    
    spinParityA = (spinParityA + 1) % 2;
  }
  
  // Honestly, I'm not sure if I need the "else" but
  // might as well, right?
  
  else if (string == 2) {
    if (spinParityB == 0) {
      digitalWrite(BA, HIGH);
      digitalWrite(BB, LOW);
    } else {
      digitalWrite(BA, LOW);
      digitalWrite(BB, HIGH);
    }
    spinParityB = (spinParityB + 1) % 2;
  }
  
  else if (string == 3) {
    if (spinParityC == 0) {
      digitalWrite(CA, HIGH);
      digitalWrite(CB, LOW);
    } else {
      digitalWrite(CA, LOW);
      digitalWrite(CB, HIGH);
    }
    spinParityC = (spinParityC + 1) % 2;
  }
  
  else if (string == 4) {
    if (spinParityD == 0) {
      digitalWrite(DA, HIGH);
      digitalWrite(DB, LOW);
    } else {
      digitalWrite(DA, LOW);
      digitalWrite(DB, HIGH);
    }
    spinParityD = (spinParityD + 1) % 2;
  }
  
  else if (string == 5) {
    if (spinParityE == 0) {
      digitalWrite(EA, HIGH);
      digitalWrite(EB, LOW);
    } else {
      digitalWrite(EA, LOW);
      digitalWrite(EB, HIGH);
    }
    spinParityE = (spinParityE + 1) % 2;
  }
  
  else if (string == 6) {
    if (spinParityF == 0) {
      digitalWrite(FA, HIGH);
      digitalWrite(FB, LOW);
    } else {
      digitalWrite(FA, LOW);
      digitalWrite(FB, HIGH);
    }
    spinParityF = (spinParityF + 1) % 2;
  }

}

void setup() {
  
  // Set all the motor control pins to outputs
  // Piezo priority though
  
  pinMode(PiezoPin, OUTPUT);
  
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(pwmC, OUTPUT);
  pinMode(pwmD, OUTPUT);
  pinMode(pwmE, OUTPUT);
  pinMode(pwmF, OUTPUT);
  
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
  pinMode(BA, OUTPUT);
  pinMode(BB, OUTPUT);
  pinMode(CA, OUTPUT);
  pinMode(CB, OUTPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);
  pinMode(EA, OUTPUT);
  pinMode(EB, OUTPUT);
  pinMode(FA, OUTPUT);
  pinMode(FB, OUTPUT);
  
  stopMotors();
 
  // Piezo thing. Yeah, I could use a for loop, but it's
  // only 4 loops long, I don't really care.
  
  tone(PiezoPin, 440, MST);
  delay(BPMDelay - MST);
  tone(PiezoPin, 440, MST);
  delay(BPMDelay - MST);
  tone(PiezoPin, 440, MST);
  delay(BPMDelay - MST);
  tone(PiezoPin, 440, MST);
  delay(BPMDelay - MST);
   
}

void loop() {
  
  playNotes();
  
}
