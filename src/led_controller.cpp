/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Controlador do LED RGB
 */

#include "led_controller.h"

LedController::LedController() {
    initialized = false;
}

void LedController::init() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Desliga todos os LEDs inicialmente
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

    initialized = true;
}

void LedController::setColor(bool red, bool green, bool blue) {
    if (!initialized) return;

    digitalWrite(RED_PIN, red ? HIGH : LOW);
    digitalWrite(GREEN_PIN, green ? HIGH : LOW);
    digitalWrite(BLUE_PIN, blue ? HIGH : LOW);
}

void LedController::showError(ErrorCode errorCode) {
    // Diferentes padrões de piscadas para diferentes erros
    switch (errorCode) {
        case ERROR_RADIO_INIT:
            // Pisca vermelho rápido para erro de inicialização de rádio
                for (int i = 0; i < 10; i++) {
                    setColor(true, false, false);
                    delay(100);
                    setColor(false, false, false);
                    delay(100);
                }
        break;

        case ERROR_RADIO_TRANSMIT:
            // Pisca vermelho e azul alternados para erro de transmissão
                for (int i = 0; i < 5; i++) {
                    setColor(true, false, false);
                    delay(200);
                    setColor(false, false, true);
                    delay(200);
                }
        break;

        default:
            // Pisca todas as cores para erro desconhecido
                for (int i = 0; i < 3; i++) {
                    setColor(true, false, false);
                    delay(200);
                    setColor(false, true, false);
                    delay(200);
                    setColor(false, false, true);
                    delay(200);
                }
        break;
    }

    // Volta para LED desligado
    setColor(false, false, false);
}