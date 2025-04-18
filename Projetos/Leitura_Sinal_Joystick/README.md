# Leitura de Joystick com Filtro de Média Móvel - Raspberry Pi Pico, Usando a plataforma BITDOGLAB

Este projeto utiliza a **Raspberry Pi Pico**, que está integrada na palca da **BITDOGLAB**, para ler os eixos X e Y de um **joystick analógico** usando o **ADC interno**, aplicar um **filtro de média móvel**, e exibir os valores suavizados em um **display OLED SSD1306 via I2C**.

---

## 📷 Foto do Projeto

> *(Insira aqui uma imagem do circuito montado)*  
> Exemplo:  
> ![Foto do Projeto](caminho/para/imagem.jpg)

---

## 🧠 Funcionalidades

- Leitura contínua dos canais analógicos do joystick (eixo X e Y).
- Filtro de média móvel com janela de 50 amostras para suavização do sinal.
- Atualização do display OLED apenas quando os valores mudam.
- Exibição dos valores médios de X e Y em tempo real.

---

## 🛠️ Hardware Necessário

- Raspberry Pi Pico
- Joystick analógico (com saídas X e Y)
- Display OLED SSD1306 (I2C)
- Cabos jumper

### Conexões

| Componente     | GPIO Pico |
|----------------|------------|
| Joystick X     | GP26 (ADC0) |
| Joystick Y     | GP27 (ADC1) |
| SDA (OLED)     | GP14        |
| SCL (OLED)     | GP15        |

---

## ⚙️ Como Funciona

1. **Inicialização do ADC e OLED**:
   - Canais ADC0 e ADC1 configurados para ler os valores analógicos do joystick.
   - Display OLED inicializado via barramento I2C1.

2. **Timers Repetitivos**:
   - Dois timers independentes são configurados para ler os valores dos eixos X e Y a cada 40ms.

3. **Filtro de Média Móvel**:
   - Implementado usando buffers circulares para ambos os eixos.
   - A média é atualizada continuamente e exibida no display OLED.

4. **Otimização de Atualização**:
   - O display só é atualizado quando há mudança na leitura média, reduzindo o flicker e consumo.

---

## 🧰 Bibliotecas Utilizadas

- `pico/stdlib.h`
- `hardware/timer.h`
- `hardware/adc.h`
- `hardware/i2c.h`
- `ssd1306.h` (custom)

> Certifique-se de incluir corretamente a biblioteca do SSD1306 no diretório `inc/`.

---

## 📦 Como Compilar

1. Certifique-se de que você tenha o [SDK do Raspberry Pi Pico Versão 1.5.1].
2. Certifique-se de que o arquivo `ssd1306.h` está incluído no projeto.

