/*
* ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Controlador de modos de operação
 */

#ifndef MODE_CONTROLLER_H
#define MODE_CONTROLLER_H

#include "config.h"
#include "led_controller.h"

class ModeController {
private:
    OperationMode currentMode;
    bool blockWiFi;
    bool blockBluetooth;
    unsigned long lastStatusTime;
    LedController* ledController;

public:
    ModeController();

    void init(LedController* ledCtrl);
    void setMode(OperationMode mode);
    OperationMode getCurrentMode();
    bool isWiFiBlocking();
    bool isBluetoothBlocking();
    void updateStatus();
};

#endif // MODE_CONTROLLER_H