#include <Arduino.h>
// definim pinii pentru LED-uri si butoane
#define butonStart 3  // buton start
#define butonStop 2   // buton stop
#define ledRGB_R 6        // rosu pentru LED-ul RGB
#define ledRGB_G 5         // verde pentru LED-ul RGB
#define led1 10           // LED 1 (25%)
#define led2 9            // LED 2 (50%)
#define led3 8            // LED 3 (75%)
#define led4 7            // LED 4 (100%)

bool charging = false;          // ne arata daca incarcarea are loc
int chargeLevel = 0;            // nivelul de incarcare
unsigned long lastUpdateTime = 0;  
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;    // timp pentru debounce (50ms)
unsigned long stopHoldTime = 1000;   // timp pentru apasare lunga

// pt butoane
int lastbutonStartState = LOW;   // starea precedenta a butonului start
int butonStartState = LOW;       // starea curenta a butonului start
int butonStopState = LOW;        // starea curenta a butonului stop

// clipirea LED-urilor
bool isBlinking = false;
unsigned long lastBlinkTime = 0;

// functiile de care avem nevoie
void resetAllLeds();
void startCharging();
void interruptCharging();
void stopCharging();
void updateCharging();
void blinkCurrentLed();
void blinkAllLeds();

void setup() {
    // declaram daca vor pinii de intrare sau de iesire
    pinMode(butonStart, INPUT);
    pinMode(butonStop, INPUT);
    
    pinMode(ledRGB_R, OUTPUT);
    pinMode(ledRGB_G, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);

    // setam starea initiala a statiei de incarcare (libera)
    digitalWrite(ledRGB_G, LOW);
    digitalWrite(ledRGB_R, HIGH);
    resetAllLeds();
}

void loop() {
    // pentru butonul de start
    int reading = digitalRead(butonStart);
    if (reading != lastbutonStartState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != butonStartState) {
            butonStartState = reading;
            if (butonStartState == HIGH && !charging) {
                startCharging();  // daca butonul este apasat, porneste procesul de incarcare
            }
        }
    }
    lastbutonStartState = reading;

    // pentru butonul de stop
    butonStopState = digitalRead(butonStop);
    if (butonStopState == LOW) {
        unsigned long pressStartTime = millis();
        while (digitalRead(butonStop) == LOW) {
            if (millis() - pressStartTime > stopHoldTime) {
                interruptCharging();  // daca  butonul este apasat, incarcarea se opreste fortat
                break;
            }
        }
    }

    // actualizeaza procesul de incarcare
    if (charging) {
        updateCharging();
    }
}

// functia care porneste incarcarea
void startCharging() {
    charging = true;
    chargeLevel = 0;
    lastUpdateTime = millis();
    digitalWrite(ledRGB_G, LOW); 
    digitalWrite(ledRGB_R, HIGH); // statia este ocupata
}

// functia care opreste incarcarea fortat
void interruptCharging() {
    charging = false;
    blinkAllLeds();
    stopCharging();
}

// functia care opreste incarcarea dupa ce este finalizata si reseteaza procesul
void stopCharging() {
    charging = false;
    digitalWrite(ledRGB_G, HIGH);
    digitalWrite(ledRGB_R, LOW);   // statia este libera
    resetAllLeds();
}

// functia pentru procesul de incarcare
void updateCharging() {
    if (chargeLevel <= 4) { //statia se incarca
        if (millis() - lastUpdateTime > 3000) {
            chargeLevel++;
            lastUpdateTime = millis();
        }

        // LED-ul de la nivelul curent de incarcare clipeste
        blinkCurrentLed();
    } else {
        blinkAllLeds();  // mini animatie pentru incarcare completa
        stopCharging();  // se opreste incarcarea si se reseteaza statia
    }
}

// functia pentru clipirea LED-ului curent
void blinkCurrentLed() {
    int currentLed;
    if (chargeLevel == 1) currentLed = led1;
    if (chargeLevel == 2) currentLed = led2;
    if (chargeLevel == 3) currentLed = led3;
    if (chargeLevel == 4) currentLed = led4;

    if (millis() - lastBlinkTime > 500) {
        isBlinking = !isBlinking;
        digitalWrite(currentLed, isBlinking ? LOW : HIGH);
        lastBlinkTime = millis();
    }
}

// mini animtia de la finalul procesului de incarcare
void blinkAllLeds() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        delay(500);
        resetAllLeds();
        delay(500);
    }
}

// functia care reseteaza toate LED-urile
void resetAllLeds() {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
}
