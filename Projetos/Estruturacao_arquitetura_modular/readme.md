# 💡 Projeto: Piscar LED Embutido da RP2040 com Arquitetura Modular

Este projeto tem como objetivo fazer o LED embutido da placa **Raspberry Pi Pico (RP2040)** piscar, utilizando uma arquitetura **modular** com separação de camadas (app, HAL, drivers e headers).

---

## 🧠 Organização Modular

O código foi dividido em diferentes camadas, respeitando os princípios da arquitetura modular:

- **`app/`**: ponto de entrada (`main.c`) com a lógica principal da aplicação.
- **`hal/`**: camada de abstração de hardware (Hardware Abstraction Layer), onde estão as funções intermediárias.
- **`drivers/`**: camada que acessa diretamente os periféricos da RP2040.
- **`include/`**: arquivos de cabeçalho públicos com as definições e protótipos.

---

## 📂 Estrutura de Diretórios

```text
.
├── app/
│   └── main.c                      # Função principal
├── drivers/
│   └── led_embutido.c             # Controle direto do LED embutido
├── hal/
│   └── hal_led.c                  # Intermediário entre app e driver
├── include/
│   ├── hal_led.h
│   └── led_embutido.h
├── .vscode/                       # Configurações do VS Code
├── CMakeLists.txt                 # Arquivo de build principal
├── pico_sdk_import.cmake          # Inclusão do SDK da Raspberry Pi Pico
└── .gitignore                     # Arquivos ignorados pelo 
Git
```
---
🧪 Como Funciona

O fluxo do código é:

main.c chama init_led_embutido() (definido no HAL);

HAL chama a função correspondente no driver;

Em loop, a função led_toogle() alterna o estado do LED.

---
✅ Resultado Esperado
O LED da placa deve piscar continuamente com base na função led_toogle().

---

🧠 Aprendizados
Uso do SDK da Raspberry Pi Pico

Modularização em C

Separação por camadas (app / HAL / drivers)

Boas práticas de organização em projetos embarcados

---

📌 Observação
Este projeto foi feito com fins didáticos para mostrar como estruturar um código limpo e reutilizável em projetos embarcados.

