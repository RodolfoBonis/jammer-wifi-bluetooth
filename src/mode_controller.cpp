/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Implementação do controlador de modos
 */

#include "mode_controller.h"

ModeController::ModeController() {
    currentMode = MODE_BOTH;
    blockWiFi = true;
    blockBluetooth = true;
    lastStatusTime = 0;
    ledController = nullptr;
}

void ModeController::init(LedController* ledCtrl) {
    ledController = ledCtrl;
}

void ModeController::setMode(OperationMode mode) {
    currentMode = mode;

    switch (mode) {
        case MODE_WIFI_ONLY:
            blockWiFi = true;
        blockBluetooth = false;
        if (ledController) {
            ledController->setColor(false, true, false); // Verde para Wi-Fi
        }
        Serial.println("Modo alterado: Apenas Wi-Fi (LED Verde)");
        break;

        case MODE_BT_ONLY:
            blockWiFi = false;
        blockBluetooth = true;
        if (ledController) {
            ledController->setColor(false, false, true); // Azul para Bluetooth
        }
        Serial.println("Modo alterado: Apenas Bluetooth (LED Azul)");
        break;

        case MODE_BOTH:
            blockWiFi = true;
        blockBluetooth = true;
        if (ledController) {
            ledController->setColor(true, false, false); // Vermelho para ambos
        }
        Serial.println("Modo alterado: Wi-Fi + Bluetooth (LED Vermelho)");
        break;
    }
}

OperationMode ModeController::getCurrentMode() {
    return currentMode;
}

bool ModeController::isWiFiBlocking() {
    return blockWiFi;
}

bool ModeController::isBluetoothBlocking() {
    return blockBluetooth;
}

void ModeController::updateStatus() {
    // Reportar status a cada intervalo
    if (millis() - lastStatusTime > STATUS_INTERVAL) {
        Serial.print("Status: Bloqueando ");
        if (blockWiFi) Serial.print("Wi-Fi ");
        if (blockBluetooth) Serial.print("Bluetooth ");
        Serial.println();
        lastStatusTime = millis();
    }
}