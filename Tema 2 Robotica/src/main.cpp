#include <Arduino.h>

/* the pins and the variables the will be used throught the code have been declared globally */

const int buttonPin = 3;
const int buttonDificultyPin = 2;
const int rgbLedRedPin = 10;
const int rgbLedGreenPin = 9;
const int rgbLedBluePin = 8;

const int baseCompareMatch = 62500;
const unsigned long buttonsDebounceDelay = 500;
const unsigned int blinkingTime = 500;
const unsigned long roundTime = 30000;
const unsigned int animationStartGameDuration = 3000;
const int wordCount = 50;
const char* words[wordCount] = {
    "seed", "honest", "bundle", "by", "fairy", "van", "orthodox", "abundant",
    "disappointment", "opinion", "tournament", "straight", "combine", "north",
    "accessible", "imposter", "drop", "cover", "lover", "embox", "parallel",
    "buy", "colorful", "satisfied", "dull", "missile", "fish", "precedent",
    "even", "remember", "education", "railroad", "drill", "museum", "part",
    "dentist", "loud", "random", "seat", "ferry", "superintendent", "tone",
    "demand", "privilege", "conservation", "provincial", "diameter", "frighten",
    "pipe",  "barrier"
};

/* for better comprehension and readability, using "enum", the state and difficulty options have been declared */

enum StateOptions { 
  IDLE = 0, 
  STARTING = 1, 
  RUNNING = 2
};

StateOptions gameState = IDLE;

#define DIFFICULTY_OPTIONS 3
enum DifficultyOptions { 
  UNKNOWN = -1, 
  EASY = 0, 
  MEDIUM = 1, 
  HARD = 2 
};

DifficultyOptions difficulty = UNKNOWN;

unsigned long lastButtonPressTime = 0;
unsigned long lastDifficultyPressTime = 0;
unsigned long roundStartTime = 0;
unsigned long wordStartTime = 0;
unsigned int timeLimit = 0;
int correctWordCount = 0;
String chosenWord;
String inputBuffer = "";

void setLEDColor(int red, int green, int blue) {
    analogWrite(rgbLedRedPin, red);
    analogWrite(rgbLedGreenPin, green);
    analogWrite(rgbLedBluePin, blue);
}

/* the words that the player should type are chosen randomly for the defined dictionary using the function "random()" */

void generateWord() {
    int wordIndex = random(wordCount);
    chosenWord = words[wordIndex];
    Serial.print("Type this word: ");
    Serial.println(chosenWord);
    inputBuffer = "";
    wordStartTime = millis();
}

/* when the difficulty button is pressed, the function cycles through the difficulty options and displays a specific message for each */

void triggerCycleDifficulty() {
    if (gameState == IDLE && millis() - lastDifficultyPressTime > buttonsDebounceDelay) {
        lastDifficultyPressTime = millis();
        difficulty = (DifficultyOptions)((difficulty + 1) % DIFFICULTY_OPTIONS);
        Serial.print(difficulty == EASY ? "Easy" : difficulty == MEDIUM ? "Medium" : "Hard");
        Serial.println(" mode on!");
        timeLimit = difficulty == EASY ? 10000 : (difficulty == MEDIUM ? 5000 : 3000);
        Serial.print("You have ");
        Serial.print(difficulty == EASY ? "10 sec" : difficulty == MEDIUM ? "5 sec" : "3 sec");
        Serial.println(" to type each word.");
    }
}

/* when the start button is pressed, the function starts or stops the game
   the function also verifies if the player chose a difficulty */

void triggerStartStopGame() {
    if (millis() - lastButtonPressTime > buttonsDebounceDelay) {
        lastButtonPressTime = millis();
        
        if (difficulty == UNKNOWN) {
            Serial.println("Select a difficulty level before starting the game!");
            return;
        }
        
        if (gameState == IDLE) {
            gameState = STARTING;
            Serial.println("Starting game...");
        } else {
            Serial.println("Game ended.");
            gameState = IDLE;
            correctWordCount = 0;
            difficulty = UNKNOWN;
            setLEDColor(255, 255, 255);
        }
    }
}

/* function to count down and start the game  */

void countdownAndStartGame() {
    for (int i = 3; i > 0; i--) {
        Serial.println(i);
        setLEDColor(255, 255, 255);
        delay(500);
        setLEDColor(0, 0, 0);
        delay(500);
    }
    gameState = RUNNING;
    roundStartTime = millis();
    Serial.println("Type the words as fast as you can.");
    setLEDColor(0, 255, 0);
    generateWord();
}

/* the words typed by the player are verrified using the following function */

void checkInput() {
    while (Serial.available()) {
        char receivedChar = Serial.read();
        Serial.print(receivedChar);     // show what the player is typing
        if (receivedChar == '\b' && inputBuffer.length() > 0) {       // handles the case where the player presses the backspace key to correct the word
            inputBuffer.remove(inputBuffer.length() - 1);
        } else if (receivedChar == '\n') {
            inputBuffer.trim();
            if (inputBuffer.equals(chosenWord)) {   // handles the case where the input word is correct
                Serial.println("Correct!");
                correctWordCount++;
                generateWord();
                setLEDColor(0, 255, 0);
                wordStartTime = millis();
            } else {
                Serial.println("Incorrect. Try again!");  //handles the case where the input word is wrong 
                setLEDColor(255, 0, 0);
                delay(500);
                setLEDColor(0, 0, 255);
            }
            inputBuffer = "";
        } else {
            inputBuffer += receivedChar;
        }
    }
    
    /* if the time limit set for typing each word is over, a new word will appeare in terminal */

    if (millis() - wordStartTime > timeLimit) {
        Serial.println("Time up! Moving to the next word.");
        generateWord();
        inputBuffer = "";
    }
}


void setup() {
    Serial.begin(28800);
    pinMode(rgbLedRedPin, OUTPUT);
    pinMode(rgbLedGreenPin, OUTPUT);
    pinMode(rgbLedBluePin, OUTPUT);

    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(buttonDificultyPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(buttonDificultyPin), triggerCycleDifficulty, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin), triggerStartStopGame, FALLING);

    randomSeed(millis());
    Serial.println("Let's play! Please choose a difficulty before procceding.");
}

void loop() {
    if (gameState == STARTING) {
        countdownAndStartGame();
    } else if (gameState == RUNNING && millis() - roundStartTime < roundTime) {
        checkInput();
    } else if (gameState == RUNNING && millis() - roundStartTime >= roundTime) {
        Serial.print("Game over! Correct words: ");
        Serial.println(correctWordCount);
        gameState = IDLE;
        difficulty = UNKNOWN;
        setLEDColor(255, 255, 255);
    }
}
