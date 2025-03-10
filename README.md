# ESP32 Wi-Fi/Bluetooth Jammer

Este projeto implementa um bloqueador de sinais Wi-Fi 2.4GHz e Bluetooth utilizando um ESP32 e dois módulos NRF24L01+PA+LNA.

## ⚠️ Aviso Legal

Este dispositivo foi desenvolvido apenas para fins educacionais e de testes em ambientes controlados. A interferência intencional em redes sem fio é ilegal na maioria dos países e pode resultar em multas severas e penalidades criminais. O autor não se responsabiliza pelo uso indevido deste projeto.

**Use este código apenas:**
- Em ambientes de laboratório isolados
- Para fins de pesquisa e educação
- Em áreas onde você tem permissão legal para realizar testes

## Características

- Bloqueio seletivo de sinais Wi-Fi 2.4GHz e/ou Bluetooth
- Indicação visual do modo de operação através de LED RGB
- Seleção de modo através de botões físicos
- Utilização otimizada de dois módulos NRF24L01 com interfaces SPI independentes
- Estrutura de código modular seguindo boas práticas de engenharia de software

## Requisitos de Hardware

- 1 ESP32 (recomendado: DevKit ou NodeMCU-32S)
- 2 módulos NRF24L01+PA+LNA (versão com amplificador de potência e antena externa)
- 2 capacitores de 10μF (para estabilidade de alimentação dos módulos NRF)
- 1 LED RGB (catodo comum ou anodo comum)
- 3 botões momentâneos (push buttons)
- Resistores de 220-330 ohms para o LED RGB (opcional, mas recomendado)
- Cabos e protoboard para montagem

## Conexões do Hardware

### Módulo NRF24L01 #1

| Pino NRF24L01 | Pino ESP32 | Capacitor 10μF | Observações |
|---------------|------------|----------------|-------------|
| CE            | GPIO 16    |                |             |
| CSN           | GPIO 15    |                |             |
| SCK           | GPIO 14    |                |             |
| MOSI          | GPIO 13    |                |             |
| MISO          | GPIO 12    |                |             |
| VCC           | 3.3V       | +              |             |
| GND           | GND        | -              |             |

### Módulo NRF24L01 #2

| Pino NRF24L01 | Pino ESP32 | Capacitor 10μF  | Observações |
|---------------|------------|-----------------|-------------|
| CE            | GPIO 22    |                 |             |
| CSN           | GPIO 21    |                 |             |
| SCK           | GPIO 18    |                 |             |
| MOSI          | GPIO 23    |                 |             |
| MISO          | GPIO 19    |                 |             |
| VCC           | 3.3V       | +               |             |
| GND           | GND        | -               |             |

### LED RGB

| Pino LED RGB      | Pino ESP32 | Observações                                         |
|-------------------|------------|-----------------------------------------------------|
| Pino R (Vermelho) | GPIO 32    | Através de resistor 220-330 ohm                     |
| Pino G (Verde)    | GPIO 33    | Através de resistor 220-330 ohm                     |
| Pino B (Azul)     | GPIO 34    | Através de resistor 220-330 ohm                     |
| Pino Comum        | GND        | Para LED catodo comum. Use VCC para LED anodo comum |

### Botões

| Botão           | Conexão                                    | Observações                           |
|-----------------|--------------------------------------------|---------------------------------------|
| Botão Wi-Fi     | GPIO 25 para um terminal, GND para o outro | Modo apenas Wi-Fi (LED Verde)         |
| Botão Bluetooth | GPIO 26 para um terminal, GND para o outro | Modo apenas Bluetooth (LED Azul)      |
| Botão Ambos     | GPIO 27 para um terminal, GND para o outro | Modo Wi-Fi + Bluetooth (LED Vermelho) |

## Estrutura do Projeto no PlatformIO

```
jammer-wifi-bluetooth/              # Pasta raiz do projeto
├── .pio/                           # Pasta gerada pelo PlatformIO (ignorada pelo git)
├── .vscode/                        # Configurações do VS Code (se usando VS Code)
├── .idea/                          # Configurações do CLion (se usando CLion)
├── include/                        # Arquivos de cabeçalho (.h)
│   ├── button_handler.h
│   ├── config.h
│   ├── led_controller.h
│   ├── mode_controller.h
│   └── radio_manager.h
├── lib/                            # Bibliotecas personalizadas (opcional)
├── src/                            # Código-fonte (.cpp)
│   ├── button_handler.cpp
│   ├── led_controller.cpp
│   ├── main.cpp                    # Ponto de entrada do programa
│   ├── mode_controller.cpp
│   └── radio_manager.cpp
├── test/                           # Código de teste (opcional)
├── platformio.ini                  # Configuração do projeto PlatformIO
└── README.md                       # Documentação do projeto
```

## Configuração do Projeto no PlatformIO

### Configuração do platformio.ini

```ini
[env:esp32dev]
platform = espressif32@^6.3.2
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps = nrf24/RF24@^1.4.11
build_flags =
   -I${platformio.packages_dir}/framework-arduinoespressif32/libraries/SPI/src
   -I${platformio.packages_dir}/framework-arduinoespressif32/cores/esp32
   -I.pio/libdeps/esp32dev/RF24/
```

## Configurando o Projeto no VS Code

1. **Instale o VS Code e a extensão PlatformIO**:
   - Baixe e instale o [Visual Studio Code](https://code.visualstudio.com/)
   - Abra o VS Code e clique na aba de extensões (ou pressione `Ctrl+Shift+X`)
   - Procure por "PlatformIO IDE" e instale a extensão
   - Reinicie o VS Code após a instalação

2. **Crie um novo projeto**:
   - Clique no ícone do PlatformIO na barra lateral (ícone de formiga)
   - Clique em "New Project" na página inicial do PlatformIO
   - Preencha as informações:
      - Name: `jammer-wifi-bluetooth`
      - Board: `Espressif ESP32 Dev Module`
      - Framework: `Arduino`
   - Selecione o local para salvar o projeto
   - Clique em "Finish"

3. **Configure o arquivo platformio.ini**:
   - Abra o arquivo `platformio.ini` na raiz do projeto
   - Substitua o conteúdo pelo código fornecido acima
   - Salve o arquivo

4. **Crie os arquivos do projeto**:
   - Crie os arquivos nas pastas conforme a estrutura apresentada acima
   - Copie o código fornecido para cada arquivo
   - Certifique-se de que os arquivos de cabeçalho estejam na pasta `include/` e os arquivos de implementação na pasta `src/`

5. **Compile e faça upload**:
   - Clique no ícone do PlatformIO na barra lateral
   - Expanda o menu "Project Tasks"
   - Clique em "Build" para compilar o projeto
   - Conecte o ESP32 ao computador via USB
   - Clique em "Upload" para fazer upload do código para o ESP32
   - Para monitorar a saída serial, clique em "Monitor"

## Configurando o Projeto no CLion

1. **Instale o CLion e o Plugin PlatformIO**:
   - Baixe e instale o [CLion](https://www.jetbrains.com/clion/)
   - Abra o CLion e vá para File > Settings > Plugins
   - Clique em "Marketplace" e pesquise por "PlatformIO"
   - Instale o plugin "PlatformIO for CLion"
   - Reinicie o CLion após a instalação

2. **Crie um novo projeto PlatformIO**:
   - Vá para File > New Project
   - Selecione "PlatformIO" na lista de tipos de projeto
   - Configure o projeto:
      - Nome: `jammer-wifi-bluetooth`
      - Placa: `Espressif ESP32 Dev Module`
      - Framework: `Arduino`
   - Clique em "Create"

3. **Configure o arquivo platformio.ini**:
   - Abra o arquivo `platformio.ini` na raiz do projeto
   - Substitua o conteúdo pelo código fornecido acima
   - Salve o arquivo

4. **Crie os arquivos do projeto**:
   - Organize os arquivos nas pastas conforme a estrutura apresentada acima
   - Use o menu de contexto do CLion (botão direito do mouse) para criar novas pastas e arquivos
   - Copie o código fornecido para cada arquivo
   - Certifique-se de que os arquivos de cabeçalho estejam na pasta `include/` e os arquivos de implementação na pasta `src/`

5. **Compile e faça upload**:
   - Use os ícones do PlatformIO na barra inferior ou superior do CLion
   - Clique no ícone "Build" para compilar o projeto
   - Conecte o ESP32 ao computador via USB
   - Clique no ícone "Upload" para fazer upload do código para o ESP32
   - Para monitorar a saída serial, clique no ícone "Serial Monitor"

## Resolvendo Problemas Comuns do PlatformIO

### Erro ao Encontrar a Biblioteca RF24

Se você encontrar um erro como `UnknownPackageError: Could not find the package with 'nrf24/RF24 @ ^1.4.11' requirements for your system`:

1. **Solução 1**: Tente a versão alternativa do `platformio.ini` usando a URL do GitHub:
   ```ini
   lib_deps =
       https://github.com/nRF24/RF24.git
   ```

2. **Solução 2**: Instale a biblioteca manualmente:
   - Baixe a biblioteca RF24 do GitHub: https://github.com/nRF24/RF24/archive/refs/heads/master.zip
   - Descompacte o arquivo
   - Crie uma pasta chamada `RF24` dentro da pasta `lib/` do seu projeto
   - Copie todos os arquivos do RF24 para esta pasta

3. **Solução 3**: Use o gerenciador de bibliotecas do PlatformIO:
   - No VS Code: Clique no ícone do PlatformIO > Libraries > Procure por "RF24"
   - No CLion: PlatformIO > Libraries > Procure por "RF24"

### Problemas de Porta Serial

Se o PlatformIO não conseguir encontrar a porta serial do ESP32:

1. Verifique se o driver do chip USB está instalado (geralmente CP210x ou CH340)
2. No arquivo `platformio.ini`, adicione:
   ```ini
   upload_port = PORTA_COM  # Substitua PORTA_COM pela porta do seu ESP32 (ex: COM3 no Windows ou /dev/ttyUSB0 no Linux)
   ```

### Erros de Compilação

Se enfrentar erros de compilação:

1. Verifique se todas as dependências estão instaladas
2. Certifique-se de que os arquivos estão nas pastas corretas
3. Verifique se não há conflitos de nomes de funções ou variáveis

## Uso

1. **Inicialização**: Ao ligar, o dispositivo iniciará no modo de bloqueio de Wi-Fi e Bluetooth (LED vermelho)

2. **Troca de Modos**:
   - Pressione o botão Wi-Fi para bloquear apenas Wi-Fi (LED verde)
   - Pressione o botão Bluetooth para bloquear apenas Bluetooth (LED azul)
   - Pressione o botão Ambos para bloquear Wi-Fi e Bluetooth simultaneamente (LED vermelho)

3. **Monitoramento**: O dispositivo envia informações de status pela porta serial (115200 bps)

4. **Alcance Efetivo**:
   - Wi-Fi: Aproximadamente 5-10 metros (dependendo do ambiente)
   - Bluetooth: Aproximadamente 5-15 metros (dependendo do dispositivo alvo)

## Personalizações

### Ajuste de Canais
Para ajustar os canais de bloqueio, modifique os arrays em `config.h`:

```cpp
// Para Wi-Fi
const uint8_t WIFI_CHANNELS[] = {4, 22, 42, 62, 80};

// Para Bluetooth
const uint8_t BT_CHANNELS[] = {2, 27, 52, 77, 102};
```

### Ajuste de Potência
Para modificar a potência de transmissão, altere a configuração do rádio em `radio_manager.cpp`:

```cpp
// Opções: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
radio1.setPALevel(RF24_PA_MAX);
radio2.setPALevel(RF24_PA_MAX);
```

### LED RGB de Anodo Comum
Se você estiver usando um LED RGB de anodo comum (onde o pino comum vai para VCC em vez de GND), modifique a função `setColor()` em `led_controller.cpp`:

```cpp
void LedController::setColor(bool red, bool green, bool blue) {
  if (!initialized) return;
  
  // Para anodo comum, a lógica é invertida
  digitalWrite(RED_PIN, red ? LOW : HIGH);
  digitalWrite(GREEN_PIN, green ? LOW : HIGH);
  digitalWrite(BLUE_PIN, blue ? LOW : HIGH);
}
```

## Resolução de Problemas

1. **Os módulos NRF24L01 não inicializam**:
   - Verifique as conexões de todos os pinos
   - Confirme que os capacitores de 10μF estão corretamente instalados
   - Teste cada módulo individualmente com um código de teste simples

2. **LED não acende ou mostra cores incorretas**:
   - Verifique se está usando um LED de anodo comum ou catodo comum e ajuste o código conforme necessário
   - Confirme as conexões dos pinos RGB

3. **Botões não respondem**:
   - Verifique as conexões dos botões
   - Certifique-se de que o outro terminal dos botões está conectado ao GND

4. **Alcance limitado**:
   - Verifique se está usando a versão PA+LNA dos módulos NRF24L01 (com amplificador e antena externa)
   - Certifique-se de que as antenas estão corretamente montadas e não obstruídas

## Licença

Este projeto é disponibilizado apenas para fins educacionais.