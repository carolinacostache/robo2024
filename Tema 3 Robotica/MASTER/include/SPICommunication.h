#ifndef SPICOMMS_H
#define SPICOMMS_H

#include <SPI.h>

class SPIComms {
public:
    SPIComms();
    void sendData(uint8_t data);
    uint8_t receiveData();

private:
    void setupSPI();
};

#endif
