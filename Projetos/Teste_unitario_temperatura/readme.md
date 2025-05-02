# 🧪 Teste Unitário para Leitura de Temperatura

![C](https://img.shields.io/badge/C-blue)
![Unity](https://img.shields.io/badge/Testing_Platform-Unity-green)

Projeto de teste unitário para verificação da conversão de valores ADC para temperatura em Celsius usando o framework Unit

---
### 📁 Estrutura do Projeto

```text
teste_unitario_temperatura/
├── app/                       # Ponto de entrada com a função main()
│   └── main.c
├── drivers/                   # Drivers de hardware específicos
│   └── temperature_sensor.c
├── hal/                       # Camada de abstração de hardware (HAL)
│   └── ler_temperatura.c
├── include/                   # Arquivos de cabeçalho públicos
│   ├── ler_temperatura.h
│   └── temperature_sensor.h
├── src/                       # Framework Unity e dependências
│   ├── unity.c
│   ├── unity.h
│   └── unity_internals.h
├── test/                      # Testes unitários
│   └── test_hal_temperature.c
├── meson.build                # Sistema de build (Meson)
└── .gitignore                 # Arquivos ignorados pelo Git
```

---

## ⚙️ Pré-requisitos

- **Pico SDK 1.5.1** – Para compilar o código principal (`main.c`)  
- **GCC Compiler** – Para compilar os testes unitários  
- **Unity Framework** – Biblioteca de testes unitários para C

---

## 📦 Instalação do Framework Unity

1. Acesse o site oficial: [Unity - Throw The Switch](https://www.throwtheswitch.org/unity)
2. Baixe e extraia a biblioteca
3. Copie a pasta `src/` da Unity para o diretório `teste_unitario_temperatura/src/`

---

## 🚀 Executando os Testes

### Exemplo de Teste

```c
#include "ler_temperatura.h"
#include "unity.h"

void setUp(void) {}    // Executado antes de cada teste
void tearDown(void) {} // Executado após cada teste

void test_adc_to_celsius(void) {
    float tensao = 0.706f;               // Tensão de entrada
    float temperatura_esperada = 27.0f;  // Valor esperado em Celsius
    float tolerancia = 1.0f;             // Tolerância de 1 grau Celsius

    TEST_ASSERT_FLOAT_WITHIN(tolerancia, temperatura_esperada, adc_to_celsius(tensao));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius);
    return UNITY_END();
}
```
---
### 🛠️ Compilando o Teste

Para compilar e executar o teste, utilize o seguinte comando no terminal:

```bash
gcc test/test_hal_temperature.c src/unity.c hal/ler_temperatura.c drivers/temperature_sensor.c -Iinclude -Isrc -o test/teste_unitario.exe
./test/teste_unitario.exe
```
---
### ✅ Resultado Esperado

Ao executar o teste, você deve ver uma saída semelhante a esta:

```bash
test/test_hal_temperature.c:12:test_adc_to_celsius:PASS
-----------------------
1 Tests 0 Failures 0 Ignored
OK
```

Isso indica que o teste passou com sucesso, validando a conversão correta da tensão em temperatura.

