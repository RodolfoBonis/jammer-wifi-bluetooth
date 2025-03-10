/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Arquivo de configuração centralizada
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

// Definições de pinos
// NRF24L01 #1
#define CE_PIN_1 16
#define CSN_PIN_1 15
#define SCK_PIN_1 14
#define MOSI_PIN_1 13
#define MISO_PIN_1 12

// NRF24L01 #2
#define CE_PIN_2 22
#define CSN_PIN_2 21
#define SCK_PIN_2 18
#define MOSI_PIN_2 23
#define MISO_PIN_2 19

// Pinos dos botões
#define WIFI_BUTTON_PIN 25
#define BT_BUTTON_PIN 26
#define BOTH_BUTTON_PIN 27

// Pinos do LED RGB
#define RED_PIN 32
#define GREEN_PIN 33
#define BLUE_PIN 34

// Configurações de tempo
#define STATUS_INTERVAL 3000    // Intervalo de atualização de status (ms)
#define DEBOUNCE_TIME 300       // Tempo de debounce para botões (ms)

// Canais de operação
// Canais para varredura geral (cobertura completa do espectro)
const uint8_t JAM_CHANNELS[] = {0, 2, 4, 5, 11, 16, 22, 27, 32, 38, 42, 43, 48, 52, 54, 60, 62, 65, 70, 76, 77, 80, 85, 90, 95, 100, 102, 105};
const uint8_t NUM_JAM_CHANNELS = sizeof(JAM_CHANNELS) / sizeof(uint8_t);

// Canais Wi-Fi otimizados (cobertura mais completa)
const uint8_t WIFI_CHANNELS[] = {4, 22, 42, 62, 80};
const uint8_t NUM_WIFI_CHANNELS = sizeof(WIFI_CHANNELS) / sizeof(uint8_t);

// Canais Bluetooth otimizados (mais distribuídos no espectro)
const uint8_t BT_CHANNELS[] = {2, 27, 52, 77, 102};
const uint8_t NUM_BT_CHANNELS = sizeof(BT_CHANNELS) / sizeof(uint8_t);

// Endereços de pipe para transmissão
const uint64_t PIPE_ADDR_WIFI_1 = 0xF0F0F0F0E1LL;
const uint64_t PIPE_ADDR_WIFI_2 = 0xF0F0F0F0D2LL;
const uint64_t PIPE_ADDR_BT_1 = 0xA0A0A0A0B1LL;
const uint64_t PIPE_ADDR_BT_2 = 0xA0A0A0A0B2LL;
const uint64_t PIPE_ADDR_SCAN_1 = 0xC0C0C0C0C1LL;
const uint64_t PIPE_ADDR_SCAN_2 = 0xC0C0C0C0C2LL;

// Enumerações

// Códigos de erro
enum ErrorCode {
  ERROR_RADIO_INIT = 1,
  ERROR_RADIO_TRANSMIT = 2
};

// Modos de operação
enum OperationMode {
  MODE_WIFI_ONLY,   // Apenas Wi-Fi
  MODE_BT_ONLY,     // Apenas Bluetooth
  MODE_BOTH         // Wi-Fi + Bluetooth
};

#endif // CONFIG_H