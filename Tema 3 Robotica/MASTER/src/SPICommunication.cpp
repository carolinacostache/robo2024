#include "SPICommunication.h"

SPIComms::SPIComms() {
    setupSPI();
}

void SPIComms::setupSPI() {
    SPI.begin();
    pinMode(SS, OUTPUT);
    digitalWrite(SS, HIGH);
}

void SPIComms::sendData(uint8_t data) {
    digitalWrite(SS, LOW);
    SPI.transfer(data);
    digitalWrite(SS, HIGH);
}

uint8_t SPIComms::receiveData() {
    digitalWrite(SS, LOW);
    uint8_t receivedData = SPI.transfer(0x00);
    digitalWrite(SS, HIGH);
    return receivedData;
}
