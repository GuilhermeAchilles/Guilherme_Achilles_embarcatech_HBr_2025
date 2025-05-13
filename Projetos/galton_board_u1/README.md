# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Guilherme Achilles de Oliveira e Aguiar**  
Curso: Residência Tecnológica em Sistemas Embarcados  
Instituição: EmbarcaTech - HBr  
Brasília, 09/05 de 2025

---

## 🎯 Descrição

Este projeto implementa uma **Galton Board digital** em um microcontrolador **Raspberry Pi Pico W**, simulando a distribuição de uma variável binomial através da queda de esferas, com controle analógico de tendência (via potenciômetro) e exibição gráfica em um display OLED.

A aplicação envolve conceitos de:

- Filas circulares (`ball_queue`)
- Leitura analógica (`analogic_read`)
- Controle via botões (`button`)
- Renderização gráfica (`write_display`, `draw_table`, `draw_graphic`)
- Geração pseudoaleatória (`random_number`)
- Dinâmica de movimento (`system_dinamic`, `ball`)

---

## 🛠️ Estrutura do Projeto

```bash
├── src/
│   ├── main.c                   # Loop principal do jogo
│   ├── utils/                   # Componentes auxiliares
│   ├── driver/                  # Drivers de hardware (ADC, Display, Botões)
│   ├── include/                 # Headers compartilhados
│   └── CMakeLists.txt           # Configuração para build
├── build/                       # Arquivos gerados pela compilação
├── README.md                    # Este arquivo
└── .vscode/                     # Configurações do VSCode (opcional)

## 🧩 Pasta `utils/`
```

A pasta `utils/` contém os **módulos auxiliares responsáveis pela lógica central e visual da simulação da Galton Board**. Cada arquivo implementa uma parte específica do comportamento do sistema:

- **`ball_queue.c`**: Gerencia a **fila de bolas** em queda, controlando sua ordem e movimentação na simulação.
- **`ball.c`**: Define a **estrutura, estado e dinâmica individual de cada bola**, incluindo colisões e movimentação baseada em tendência.
- **`draw_graphic.c`**: Responsável pela **exibição gráfica estatística**, desenha o histograma das quedas.
- **`draw_table.c`**: Renderiza a **estrutura da árvore (Galton Board)** e elementos visuais como linhas e contadores no display.
- **`random_number.c`**: Gera os **ângulos aleatórios** de desvio das bolas ao colidir com pinos, simulando a aleatoriedade do sistema.
- **`system_dinamic.c`**: Gerencia a **dinâmica geral do sistema**, integrando leitura analógica (tendência), atualização de estado e movimento.

> Esses arquivos formam a espinha dorsal da lógica da simulação, separando responsabilidades e facilitando manutenção e testes.


# ⚙️ Dinâmica das Bolas

O comportamento dinâmico das bolas neste sistema é modelado com base em conceitos da física clássica, em particular o movimento com aceleração (gravidade), colisões elásticas e vetores de velocidade.

## 🎱 Objeto `ball`

O objeto `ball` representa a bola do jogo e encapsula suas propriedades físicas, estado e comportamento dinâmico ao longo do tempo. Ele é representado por uma `struct` com os seguintes campos:

```c
typedef struct {
    float position_initial[2];     // Posição inicial da bola [x, y]
    float position_final[2];       // Posição final (atual) da bola [x, y]
    float vel_x_y[2];              // Velocidade da bola nos eixos x e y
    uint32_t time_ball;            // Tempo (em microssegundos) da última atualização
    float angle_impact;            // Ângulo de impacto em graus
    float state;                   // Direção do movimento vertical (1 = descendo, -1 = subindo)
    float tendencie;              // Desvio horizontal causado por influência externa (ex: controle ADC)
    int detect_colision;          // Flag que indica se houve colisão
} ball;
```

### 🔄 Funções associadas à bola

* `create_ball(ball *b)`: Inicializa a bola na posição (64, 0) com velocidade vertical padrão.
* `calculate_pos(ball *b)`: Atualiza a posição da bola em função do tempo decorrido, levando em conta gravidade e tendência horizontal.
* `draw_ball(ball *b)`: Desenha a bola na tela, com base em sua posição atual.
* `change_state(ball *b)`: Inverte o estado vertical da bola (de subida para descida e vice-versa).
* `return_tendencie(int adc_value)`: Retorna a tendência horizontal da bola com base na leitura de um ADC (usado para controle externo).


## 📐 Equações Utilizadas

### 1. Atualização de velocidade vertical (gravidade)

```c
float v_y = b->vel_x_y[1] = +b->vel_x_y[1] + 10 * delta;
```

**Equações:**

$$
v = \sqrt{v_x^2 + v_y^2} \cdot 0.4
$$

$$
v_x = v \cdot \sin(\theta) + \text{tendência}
$$

$$
v_y = v \cdot \cos(\theta)
$$


- $\( v \):$ velocidade total com amortecimento (fator 0.4)  
- $\( \theta \)$: ângulo de impacto (em graus)  
- **Tendência**: valor externo (como do ADC) que causa leve desvio lateral



### ⚙️ Comportamento físico

A posição da bola é atualizada segundo a fórmula da cinemática básica:

```
x(t) = x₀ + vₓ * Δt 
y(t) = y₀ + vᵧ * Δt + ½ * g * Δt²
```

* Onde `g = 10 m/s²` é a aceleração gravitacional simulada no jogo.
* A tendência (`tendencie`) afeta o eixo X, criando um leve desvio lateral nas colisões.



### 2. Cálculo da velocidade total e decomposição em componentes x e y

```c
float speed = sqrtf(powf(b->vel_x_y[0], 2) + powf(v_y, 2)) * 0.4f;
float vel_x = b->vel_x_y[0] = speed * sinf(b->angle_impact * M_PI / 180) + b->tendencie;
b->vel_x_y[1] = speed * cosf(b->angle_impact * M_PI / 180);
```

**Equações:**

$$
v_y = v_{y_0} + g \cdot \Delta t
$$

- $v_y$: nova velocidade vertical  
- $v_{y_0}$: velocidade vertical anterior  
- $g = 10 \ \text{m/s}^2$: aceleração gravitacional  
- $\Delta t$: tempo desde a última atualização


---

### 3. Inversão da velocidade na colisão com paredes

```c
b->vel_x_y[0] = -b->vel_x_y[0];
```

**Interpretação:**  
A colisão com as paredes laterais é modelada como uma **colisão elástica**, onde a componente horizontal da velocidade inverte seu sinal.

---

### 4. Verificação para transição de estado (queda lenta)

```c
if (velocity_y < 1)
```

Quando a velocidade vertical atinge um valor muito baixo, a bola é considerada “parada” ou pronta para mudar de fase/estado. Isso simula o fim do movimento entre dois pontos de impacto.

---

## 🧪 Considerações Físicas

- A gravidade é aplicada de forma simplificada como uma aceleração constante de `10 m/s²`.
- O movimento da bola é calculado por vetores 2D \((x, y)\), com separação clara entre suas componentes horizontais e verticais.
- A simulação considera **pequenas colisões discretas com obstáculos**, a partir de uma árvore de pontos.
- O fator de amortecimento `0.4` simula perda de energia após impactos (como resistência do ar ou atrito).
- O sistema é idealizado e discreto, ajustado ao tempo de execução e não contínuo.

## 🎲 Randomização de Ângulos

### 🎯 Objetivo da Randomização

A randomização de ângulos é crucial para simular o comportamento aleatório das bolas ao colidirem com obstáculos na Galton Board, introduzindo imprevisibilidade no sistema.

### 🔢 Implementação da Função `random_angle_degrees()`

```c
#include <stdlib.h>

float random_angle_degrees() {
    int angle = (rand() % 36) + 10; // Gera número de 10 a 36
    if (rand() % 2 == 0) {
        return -angle;  // Negativo
    } else {
        return angle;   // Positivo
    }
}
```

### 📐 Detalhamento da Geração de Ângulos

#### 1. Intervalo de Ângulos
- **Faixa**: 10° a 45°
- **Método**: `(rand() % 36) + 10`
  - `rand() % 36` gera números de 0 a 35
  - `+ 10` desloca o intervalo para 10 a 45

#### 2. Sinal do Ângulo
- 50% de chance de ser positivo
- 50% de chance de ser negativo
- Implementado por `rand() % 2 == 0`

### 🧠 Função de Iniciação de Seed

```c
void initiate_seed() {
    srand(2);  // Seed fixa para reprodutibilidade
}
```

### 🔍 Características da Randomização

- **Reprodutibilidade**: Usa seed fixa para consistência entre execuções
- **Distribuição Uniforme**: 
  - Ângulos entre -45° e -10°
  - Ângulos entre 10° e 45°
- **Precisão**: Trabalha com números inteiros, convertidos para float

### 💡 Possíveis Melhorias

- Usar geradores de números aleatórios mais sofisticados
- Implementar distribuição de probabilidade mais complexa
- Adicionar variabilidade na amplitude dos ângulos

### 📊 Exemplo de Distribuição

```
Ângulos possíveis:
- Positivos: 10°, 11°, 12°, ..., 45°
- Negativos: -10°, -11°, -12°, ..., -45°
- Total de 72 possibilidades
```

### 🔬 Impacto na Simulação

A randomização de ângulos simula:
- Variabilidade natural do movimento
- Imprevisibilidade das colisões
- Comportamento próximo a um sistema binomial

## 🖥️ Função Main

### 🔍 Visão Geral do Funcionamento

A função `main()` é o núcleo do programa, responsável por gerenciar o ciclo principal do sistema de simulação de bolas.

### 🚀 Inicialização do Sistema

Quando o programa é iniciado, a função `main()` executa inicializações cruciais:

```c
stdio_init_all();
init_display();
init_buttons();
init_adc();
initiate_seed();
init_queue(&fila);
init_button_interrupts();
```

#### Detalhes das Inicializações

- **`stdio_init_all()`**: Inicializa comunicações de entrada e saída
- **`init_display()`**: Prepara o display
- **`init_buttons()`**: Configura os botões
- **`init_adc()`**: Inicializa leitura analógica
- **`initiate_seed()`**: Prepara geração de números aleatórios
- **`init_queue(&fila)`**: Inicializa a fila de bolas
- **`init_button_interrupts()`**: Configura interrupções dos botões

### 🔄 Loop Principal

O loop principal (`while(1)`) gerencia três funções principais:

#### 1. Geração de Bolas

```c
if (absolute_time_diff_us(ultimo_spawn, get_absolute_time()) > 90000)
{
    ball nova_bola;
    create_ball(&nova_bola);

    if (fila.count < MAX_BOLAS)
    {
        enqueue(&fila, &nova_bola);
        cont_balls++;
    }

    ultimo_spawn = get_absolute_time();
}
```

- Gera uma nova bola a cada 90 milissegundos
- Adiciona à fila se não exceder `MAX_BOLAS`
- Incrementa contador de bolas

#### 2. Modo Gráfico

```c
if (button_a_nivel)
{
    cancel_repeating_timer(&timer_contador);
    timer_reativado = false;

    while (button_a_nivel)
    {
        clear_display();
        draw_graphics((float)cont_balls);
        show_display();
        sleep_ms(100);
    }
}
```

- Ativa quando botão A é pressionado
- Cancela timer de atualização normal
- Mostra gráfico com contagem de bolas
- Retorna ao modo normal ao soltar o botão

#### 3. Atualização de Display

```c
if (atualizar_display)
{
    show_display();
    atualizar_display = false;
}
```

- Monitora flag `atualizar_display`
- Mostra display quando flag é verdadeira
- Reseta flag após atualização

### ⚙️ Timer de Atualização

- Timer configurado para `update_balls_timer_callback()` a cada 100ms
- Atualiza estado das bolas na fila
- Gerencia:
  - Colisões
  - Cálculo de posição
  - Remoção de bolas

### 🔧 Características Técnicas

- Usa `tight_loop_contents()` para otimização de CPU
- Gerenciamento dinâmico de timer
- Sistema de fila para múltiplas bolas
- Modo gráfico interativo

### 📋 Fluxo de Execução

1. Inicialização completa
2. Entra em loop infinito
3. Gera bolas periodicamente
4. Verifica estado dos botões
5. Atualiza display
6. Repete o processo

### ⚠️ Pontos de Atenção

- Limite máximo de bolas: `MAX_BOLAS`
- Geração de bolas controlada por tempo
- Modo gráfico mostra estatísticas

### 💡 Observações Técnicas

- Sistema de interrupção para botões
- Gerenciamento de memória via fila circular
- Atualização de estado baseada em timer

---

## 📈 Resultados

A seguir, são apresentados os **resultados obtidos após a execução da simulação** com diferentes valores de tendência (controle analógico), usando um total de 1000 bolas para cada cenário.

### 🔧 Configuração Experimental

* **Número de bolas**: 1000
* **Tempo entre lançamentos**: 90ms
* **Tendência analógica (`tendencie`)**: Variada entre -5.0 (esquerda), 0.0 (neutra), +5.0 (direita)
* **Display**: OLED 128x64px, modo gráfico ativado com botão
* **Distribuição observada**: Histogramas exibidos em tempo real no display
* **Limite de pinos/saídas na base da Galton Board**: 7 

---

### ⚖️ 1. Tendência Neutra (`tendencie = 0.0`)

#### 📊 Distribuição Esperada:



Distribuição **simétrica**, aproximando uma **binomial equilibrada**.


<p align ="center"><img src="https://github.com/EmbarcaTech-2025/lab01_galton_board-GuilhermeAchilles/blob/main/assets/i_resultado_1.PNG?raw=true" width="400" alt="Imagem da BitDogLab"></p>



#### 📊 Distribuição Observada:


> A distribuição segue o comportamento esperado de uma curva normal discreta centrada, com maior acúmulo no meio.


<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/galton_board_u1/assets/i_resultado_1.JPG?raw=true" width="400" alt="Imagem da BitDogLab"></p>

---

### ⬅️ 2. Tendência à Esquerda (`tendencie = -5.0`)

<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/galton_board_u1/assets/i_resultado_3.PNG?raw=true" width="400" alt="Imagem da BitDogLab"></p>

#### 📊 Distribuição Esperada:

Deslocamento da curva para a **esquerda**, com maior acúmulo nas posições iniciais.


#### 📊 Distribuição Observada:

<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/galton_board_u1/assets/resultado_3.PNG?raw=true" width="400" alt="Imagem da BitDogLab"></p>

> O gráfico mostra claro **viés à esquerda**, indicando que o controle analógico influencia efetivamente o caminho das bolas.

---

### ➡️ 3. Tendência à Direita (`tendencie = +5.0`)

<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/galton_board_u1/assets/i_resultado_2.PNG?raw=true" width="400" alt="Imagem da BitDogLab"></p>

#### 📊 Distribuição Esperada:

Deslocamento da curva para a **direita**, com maior acúmulo nas posições finais.

#### 📊 Distribuição Observada:

<p align ="center"><img src="https://github.com/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025/blob/main/Projetos/galton_board_u1/assets/resultado_2.PNG?raw=true" width="400" alt="Imagem da BitDogLab"></p>

> A curva desloca-se para a direita, confirmando a resposta dinâmica ao input analógico.

---

## 📌 Análise Geral

* A simulação responde corretamente às variações de entrada analógica.
* O uso de física simplificada com randomização oferece **realismo suficiente** para observar o comportamento de uma distribuição binomial influenciada.
* O histograma exibido em tempo real permite **interpretação visual clara** dos resultados.

