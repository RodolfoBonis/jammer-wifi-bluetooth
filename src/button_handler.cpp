/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Gerenciador de botões
 */

#include "button_handler.h"

ButtonHandler::ButtonHandler() {
    modeController = nullptr;
    lastButtonPressTime = 0;
}

void ButtonHandler::init() {
    // Configurando os pinos dos botões como input com pull-up
    pinMode(WIFI_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BOTH_BUTTON_PIN, INPUT_PULLUP);
}

void ButtonHandler::setModeController(ModeController* modeCtrl) {
    modeController = modeCtrl;
}

void ButtonHandler::update() {
    checkButtonsDebounced();
}

bool ButtonHandler::checkButtonsDebounced() {
    // Evita verificar botões se não tiver controlador de modo
    if (!modeController) return false;

    // Verificar se passou tempo suficiente desde o último pressionamento (debounce)
    if (millis() - lastButtonPressTime < DEBOUNCE_TIME) {
        return false;
    }

    bool buttonPressed = false;

    // Verifica o botão Wi-Fi (lógica invertida devido ao INPUT_PULLUP)
    if (digitalRead(WIFI_BUTTON_PIN) == LOW) {
        modeController->setMode(MODE_WIFI_ONLY);
        lastButtonPressTime = millis();
        buttonPressed = true;
    }

    // Verifica o botão Bluetooth
    else if (digitalRead(BT_BUTTON_PIN) == LOW) {
        modeController->setMode(MODE_BT_ONLY);
        lastButtonPressTime = millis();
        buttonPressed = true;
    }

    // Verifica o botão Ambos
    else if (digitalRead(BOTH_BUTTON_PIN) == LOW) {
        modeController->setMode(MODE_BOTH);
        lastButtonPressTime = millis();
        buttonPressed = true;
    }

    return buttonPressed;
}