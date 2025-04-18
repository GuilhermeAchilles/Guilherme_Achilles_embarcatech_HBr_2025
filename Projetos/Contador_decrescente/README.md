# Contador com Botões e Display OLED  - Raspberry Pi Pico, usando a plataforma BITDOGLAB

Este projeto implementa um **contador decrescente** com controle por botões e visualização em um **display OLED SSD1306**. Ele utiliza a **Raspberry Pi Pico**, que está integrada na placa **BITDOGLAB**, **interrupções por GPIO** e um **timer repetitivo** para controle de tempo.

---

## 📷 Foto do Projeto

<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/Contador_decrescente/assets/imagem_projeto_contador.jpeg?raw=true" width="400" alt="Imagem da BitDogLab"></p>

---

## 🧠 Funcionalidades

- Contagem regressiva iniciando de 10 segundos.
- Botão A: reinicia o contador para 10.
- Botão B: conta o número de vezes que foi pressionado enquanto o contador está ativo.
- Atualização contínua da tela OLED com:
  - Tempo restante
  - Número de apertos no botão B

---

## 🛠️ Hardware Necessário

- Raspberry Pi Pico
- Display OLED SSD1306 (I2C)
- 2 botões físicos (pull-up interno ativado)
- Cabos de conexão

### Conexões

| Componente  | GPIO Pico |
|-------------|------------|
| Botão A     | GP5        |
| Botão B     | GP6        |
| SDA (OLED)  | GP14       |
| SCL (OLED)  | GP15       |

---

## 🧰 Bibliotecas Utilizadas

- `pico/stdlib.h`
- `hardware/timer.h`
- `hardware/i2c.h`
- `ssd1306.h` (externa)

> Verifique se você incluiu corretamente a biblioteca do display OLED (`ssd1306.h`) no diretório `inc/`.

---

## ⚙️ Como Funciona

1. **Inicialização**:
   - Os botões A e B são configurados como entradas com pull-up interno.
   - O display OLED é inicializado via I2C.
   - Um `repeating_timer` decrementa o contador a cada 1 segundo.
   - Interrupções de borda de descida são configuradas para ambos os botões.

2. **Botões**:
   - **Botão A** reinicia o contador para 10 segundos.
   - **Botão B** incrementa o contador de apertos, **somente se o tempo for maior que 0**.
   - Há debounce por software com verificação de tempo (150ms).

3. **Display OLED**:
   - Mostra:
     - `"Segundos: "` seguido do valor do contador.
     - `"Apertos de B: "` seguido da quantidade de vezes que o botão B foi pressionado.

---

## 📦 Como Compilar

1. Certifique-se de que você tenha o [SDK do Raspberry Pi Pico Versão 1.5.1].
2. Certifique-se de que o arquivo `ssd1306.h` está incluído no projeto.

