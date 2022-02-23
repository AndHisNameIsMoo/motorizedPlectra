// ALL OF THE IMPORTANT, COSTUMIZABLE STUFF ARE OVER HERE!!!

// The strength of the motor. 255 is the highest, 0 is the lowest.
// I set it to 100 because it's a nice, halfway-ish point.

#define pwmThing 100

// Setting up the BPM. Set this to the BPM of the song/solo you're doing.

int BPM = 120;

// MST stands for Motor Spinning Time. It's set in milliseconds (ms). The default is 50 milliseconds.

int MST = 10;

// This controls the type of notes in the movement array. Quarters would be 4, triplets would be 3, etc. 
// This also functions as the top number on a time measure in sheet music, hence the variable name.

int TopNumber = 4;

// The movement array. It decides what motors move when. 1 is spin, 0 is don't spin.
// Each pattern is a different strumming pattern. One could be set as a verse, another could be set as a chorus.
// You could use only one, or you could use up to five! Just set each strumming pattern here.

// Notice that the patterns are in groups of six. This is because there are six strings on a guitar.

int PatternOne[] =
 {1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0};

int PatternTwo[] =
 {1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0};

int PatternThree[] =
 {1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0};

int PatternFour[] =
 {1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0};

int PatternFive[] =
 {1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0};
  
// Now, you have to specify how the chorus structure works.
// The numbers are in pairs. The first number is the pattern you're using. The second is how many times it repeats.

int Setup[] =
 {1, 4,
  3, 4,
  2, 4,
  4, 4,
  2, 4,
  1, 8};

// The rest is just boring code stuff

// Defining all of the connections
#define pwmA 9
#define pwmB 10
#define pwmC 6
#define pwmD 11
#define pwmE 5
#define pwmF 3
#define AA 13
#define AB A0
#define BA 12
#define BB A3
#define CA 7
#define CB A1
#define DA 8
#define DB A4
#define EA 4
#define EB A2
#define FA 2
#define FB A5

// This single one is for the piezo. There's no
// way I'm having a project without a piezo.

#define PiezoPin 1

// Spin parity (so the motor switches between 
// moving deosil and widdershins)

int spinParityA = 0;
int spinParityB = 0;
int spinParityC = 0;
int spinParityD = 0;
int spinParityE = 0;
int spinParityF = 0;

// By taking the BPM, we get the amount of delays
// we want. There are 60000 milliseconds in a minute.
// By dividing this by the BPM, we get the amount of
// milliseconds it takes for a beat to... beat.

int BPMDelay = 60000 / BPM;

// This variable combines all of them together
// because I need those and don't feel like
// typing it a bunch of times.

int OtherDelay = (BPMDelay / TopNumber);

// Just a thing that checks how long Steup[] is.

int setupLength = (sizeof(Setup) / sizeof(Setup[0]) + 1) / 2;

int patternLength(int Pattern[]) {

  // This is the same code as setupLength[].
  // However, now it's a function because I need to take in an input array that changes.
  
  int interestingVarName = (sizeof(Pattern) / sizeof(Pattern[0]) + 1) / 6;
  return interestingVarName;

}

// Function that plays the notes. That's why it's called "playNotes()."
// "patternNumber" is the pattern number the motor's using.

int numToPat(int number) {

  if (number == 1) {
    return PatternOne;
  } if (number == 2) {
    return PatternTwo;
  } if (number == 3) {
    return PatternThree;
  } if (number == 4) {
    return PatternFour;
  } if (number == 5) {
    return PatternFive;
  }
}

void playNotes(int patternNumber) {

  int Pattern[] = numToPat(patternNumber);
  
  for(int i = 0; i < patternLength(patternNumber); ++i) {
    
    // Checks which motor's supposed to move. First
    // checks if the motor should be spinning according
    // to the array, and if so, then spins it.
    
    if (Pattern[i * 6] == 1) {
      spinMotor(1);
    } if (Pattern[i * 6 + 1] == 1) {
      spinMotor(2);
    } if (Pattern[i * 6 + 2] == 1) {
      spinMotor(3);
    } if (Pattern[i * 6 + 3] == 1) {
      spinMotor(4);
    } if (Pattern[i * 6 + 4] == 1) {
      spinMotor(5);
    } if (Pattern[i * 6 + 5] == 1) {
      spinMotor(6);
    }
    
    delay(MST);
    
    // Stops the motors. I made it its own function
    // because instead of just turning the ones on and
    // having to check which ones are moving, I instead
    // stop all of them at the same time to not worry
    // about it.
    
    stopMotors();
    
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

void playSong() {

  // Same thing as playNotes() but for the whole thing. Iteration!
  for(int i = 0; i < setupLength; ++i) {

    for(int i = 0; i < Setup[i * 2 + 1]; ++i) {
       playNotes(Setup[i * 2]);

    }
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
  
  // Plays the notes according to Setup[].

  
  playSong();
  
}
