# Monitor de Temperatura Interna da Raspberry Pi Pico com Display OLED usando a placa BITDOGLAB

Este projeto lê a temperatura interna da **Raspberry Pi Pico** utilizando seu **sensor interno de temperatura via ADC**, processa uma média móvel e exibe o valor em tempo real em um **display OLED SSD1306** via comunicação **I2C**.

---

## 📷 Foto do Projeto

> *(Insira uma imagem do seu projeto aqui)*  
> Exemplo:
> ![Foto do Projeto](caminho/para/sua/imagem.jpg)

---

## 🧠 Funcionalidades

- Leitura contínua da temperatura interna do chip.
- Processamento da média de 20 amostras para suavização.
- Exibição da temperatura média em um display OLED 128x64 (SSD1306).
- Atualização do display a cada 20 leituras (~1s).
- Uso de interrupção (IRQ) para leitura eficiente do ADC.

---

## 🛠️ Hardware Necessário

- Raspberry Pi Pico
- Display OLED SSD1306 (I2C)
- Cabos de conexão

### Conexões I2C (padrão do código)

| Componente | GPIO Pico |
|------------|-----------|
| SDA        | GP14      |
| SCL        | GP15      |

---

## 🧰 Bibliotecas Utilizadas

- `pico/stdlib.h`
- `hardware/adc.h`
- `hardware/irq.h`
- `hardware/i2c.h`
- `hardware/timer.h`
- `ssd1306.h` (biblioteca externa para controle do display OLED)

> Certifique-se de que a biblioteca `ssd1306.h` esteja corretamente instalada no seu projeto. Ela pode estar na pasta `inc/` como no exemplo acima.

---

## ⚙️ Como Funciona

1. **Inicialização**:
   - O ADC da Raspberry Pi Pico é configurado para ler o canal 4 (sensor de temperatura interno).
   - Ativa-se uma interrupção sempre que uma nova leitura está disponível.

2. **Leitura e Processamento**:
   - A cada nova leitura, o valor do ADC é convertido para temperatura em graus Celsius.
   - O valor é armazenado em um buffer circular de 20 posições.
   - A média das últimas 20 amostras é calculada.

3. **Exibição**:
   - A cada 20 leituras (~1 segundo), o display OLED é atualizado com o texto:
     ```
     Temperatura CPU:
          XX.XX ºC
     ```

---

## 📦 Como Compilar

Certifique-se de que você tenha o [SDK do Raspberry Pi Pico Versão 1.5.1]
