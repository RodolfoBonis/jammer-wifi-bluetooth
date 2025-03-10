/*
* ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Controlador do LED RGB
 */

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "config.h"

class LedController {
private:
    bool initialized;

public:
    LedController();
    void init();
    void setColor(bool red, bool green, bool blue);
    void showError(ErrorCode errorCode);
};

#endif // LED_CONTROLLER_H