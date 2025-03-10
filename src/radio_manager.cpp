/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Implementação do gerenciador de rádios
 */

#include "radio_manager.h"

RadioManager::RadioManager()
  : spi1(VSPI),
    spi2(HSPI),
    radio1(CE_PIN_1, CSN_PIN_1),
    radio2(CE_PIN_2, CSN_PIN_2) {
  // O corpo do construtor está vazio porque a inicialização é feita nas listas
}

bool RadioManager::init() {
  // Inicializando interfaces SPI separadas
  spi1.begin(SCK_PIN_1, MISO_PIN_1, MOSI_PIN_1);
  spi2.begin(SCK_PIN_2, MISO_PIN_2, MOSI_PIN_2);

  // Configurando o primeiro módulo NRF24L01
  if (!radio1.begin(&spi1)) {
    Serial.println("Falha ao inicializar o módulo NRF24L01 #1");
    return false;
  }

  Serial.println("Módulo NRF24L01 #1 inicializado com sucesso");

  // Configurando o segundo módulo NRF24L01
  if (!radio2.begin(&spi2)) {
    Serial.println("Falha ao inicializar o módulo NRF24L01 #2");
    return false;
  }

  Serial.println("Módulo NRF24L01 #2 inicializado com sucesso");

  // Configurações para máxima potência e interferência
  radio1.setPALevel(RF24_PA_MAX);  // Potência máxima
  radio1.setDataRate(RF24_1MBPS);  // Taxa de dados otimizada
  radio1.disableCRC();             // Desabilita CRC para transmissões mais rápidas

  radio2.setPALevel(RF24_PA_MAX);
  radio2.setDataRate(RF24_1MBPS);
  radio2.disableCRC();

  // Gerando dados aleatórios para transmissão
  generateRandomData();

  Serial.println("Radio Manager Inicializado");

  return true;
}

void RadioManager::generateRandomData() {
  // Gera dados aleatórios diferentes a cada transmissão
  // Isso impede que os dispositivos alvo se adaptem ao padrão
  data[0] = random(0, 255);
  data[4] = random(0, 255);
  data[8] = random(0, 255);
  data[12] = random(0, 255);
  data[16] = random(0, 255);
  data[20] = random(0, 255);
  data[24] = random(0, 255);
  data[28] = random(0, 255);
  data[31] = random(0, 255);
}

void RadioManager::blockWiFiSignals(ButtonHandler* buttonHandler) {
  // Foca nos canais Wi-Fi mais comuns
  for (int i = 0; i < NUM_WIFI_CHANNELS; i++) {
    // Transmitindo em canais Wi-Fi com o módulo 1
    radio1.setChannel(WIFI_CHANNELS[i]);
    radio1.openWritingPipe(PIPE_ADDR_WIFI_1);
    radio1.stopListening();

    // Transmitindo em canais adjacentes com o módulo 2
    radio2.setChannel(WIFI_CHANNELS[i] + 3);
    radio2.openWritingPipe(PIPE_ADDR_WIFI_2);
    radio2.stopListening();

    // Transmitindo pacotes em rajada para maximizar interferência
    for (int j = 0; j < 25; j++) {
      // Verificar botões entre transmissões para resposta rápida
      if (j % 5 == 0) {
        buttonHandler->checkButtonsDebounced();
      }

      // Transmissões mais longas para Wi-Fi
      generateRandomData();
      radio1.write(data, 32);
      radio2.write(data, 32);

      // Intervalo curto entre transmissões
      delayMicroseconds(200);
    }

    // Verificar botões após cada canal
    buttonHandler->checkButtonsDebounced();
  }
}

void RadioManager::blockBluetoothSignals(ButtonHandler* buttonHandler) {
  // Transmitindo em frequências Bluetooth com saltos rápidos
  for (int i = 0; i < NUM_BT_CHANNELS; i++) {
    // Configurando o primeiro módulo para um canal Bluetooth
    radio1.setChannel(BT_CHANNELS[i]);
    radio1.openWritingPipe(PIPE_ADDR_BT_1);
    radio1.stopListening();

    // Configurando o segundo módulo para outro canal Bluetooth
    radio2.setChannel(BT_CHANNELS[(i+1) % NUM_BT_CHANNELS]);
    radio2.openWritingPipe(PIPE_ADDR_BT_2);
    radio2.stopListening();

    // Transmitindo em rajadas mais curtas e rápidas para Bluetooth
    for (int j = 0; j < 20; j++) {
      // Verificar botões entre transmissões para resposta rápida
      if (j % 5 == 0) {
        buttonHandler->checkButtonsDebounced();
      }

      generateRandomData();
      radio1.write(data, 32);
      radio2.write(data, 32);

      // Saltos mais rápidos para Bluetooth (afeta o mecanismo de salto de frequência)
      delayMicroseconds(100);
    }

    // Verificar botões após cada canal
    buttonHandler->checkButtonsDebounced();
  }
}

void RadioManager::scanAllChannels(ButtonHandler* buttonHandler) {
  // Varredura completa de todos os canais para maximizar cobertura
  for (int i = 0; i < NUM_JAM_CHANNELS; i += 2) {
    // Verificar botões para resposta mais rápida
    if (i % 4 == 0) {
      buttonHandler->checkButtonsDebounced();
    }

    // Dividimos os canais entre os dois módulos para varredura mais rápida
    radio1.setChannel(JAM_CHANNELS[i]);
    radio1.openWritingPipe(PIPE_ADDR_SCAN_1);
    radio1.stopListening();

    if (i+1 < NUM_JAM_CHANNELS) {
      radio2.setChannel(JAM_CHANNELS[i+1]);
    } else {
      radio2.setChannel(JAM_CHANNELS[0]); // Volta ao início
    }
    radio2.openWritingPipe(PIPE_ADDR_SCAN_2);
    radio2.stopListening();

    // Transmissão rápida em cada canal
    for (int j = 0; j < 8; j++) {
      generateRandomData();
      radio1.write(data, 32);
      radio2.write(data, 32);
      delayMicroseconds(300);
    }
  }
}