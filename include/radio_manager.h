/*
* ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Gerenciador dos módulos de rádio
 */

#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H

#include "config.h"
#include "button_handler.h"

class RadioManager {
private:
    SPIClass spi1;
    SPIClass spi2;
    RF24 radio1;
    RF24 radio2;
    uint8_t data[32];

    void generateRandomData();

public:
    RadioManager();
    bool init();
    void blockWiFiSignals(ButtonHandler* buttonHandler);
    void blockBluetoothSignals(ButtonHandler* buttonHandler);
    void scanAllChannels(ButtonHandler* buttonHandler);
};

#endif // RADIO_MANAGER_H