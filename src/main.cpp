/*
 * ESP32 Wi-Fi/Bluetooth Jammer
 *
 * Arquivo principal que coordena todos os componentes do sistema
 */

#include "config.h"
#include "radio_manager.h"
#include "mode_controller.h"
#include "led_controller.h"
#include "button_handler.h"

RadioManager radioManager;
ModeController modeController;
LedController ledController;
ButtonHandler buttonHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Sistema de Bloqueio de Sinais Wi-Fi/Bluetooth...");

  // Inicializa o controlador de LED
  ledController.init();

  // Inicializa o controlador de botões
  buttonHandler.init();

  // Inicializa o controlador de modo
  modeController.init(&ledController);

  // Passa referências para o handler de botões
  buttonHandler.setModeController(&modeController);

  // Inicializa os rádios
  if (!radioManager.init()) {
    Serial.println("Falha ao inicializar os módulos de rádio!");
    ledController.showError(ERROR_RADIO_INIT);
    while (1) {
      // Loop infinito em caso de erro de inicialização
      delay(1000);
    }
  }

  Serial.println("Sistema inicializado com sucesso!");
  Serial.println("Pressione os botões para selecionar o modo:");
  Serial.println("- Botão 1 (GPIO 25): Apenas Wi-Fi (LED Verde)");
  Serial.println("- Botão 2 (GPIO 26): Apenas Bluetooth (LED Azul)");
  Serial.println("- Botão 3 (GPIO 27): Wi-Fi + Bluetooth (LED Vermelho)");

  // Define o modo padrão (ambos)
  modeController.setMode(MODE_BOTH);
}

void loop() {
  // Verifica e processa os botões
  buttonHandler.update();

  // Atualiza o status do jammer periodicamente
  modeController.updateStatus();

  // Executa as operações com base no modo atual
  OperationMode currentMode = modeController.getCurrentMode();

  // Executa os bloqueios conforme o modo selecionado
  if (modeController.isWiFiBlocking()) {
    radioManager.blockWiFiSignals(&buttonHandler);
  }

  if (modeController.isBluetoothBlocking()) {
    radioManager.blockBluetoothSignals(&buttonHandler);
  }

  // Varredura geral se ambos estiverem ativos
  if (currentMode == MODE_BOTH) {
    radioManager.scanAllChannels(&buttonHandler);
  }
}