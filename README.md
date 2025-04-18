<p align ="center"><img src="assets/imagem-inicial-readme.png" width="400" alt="Imagem Inicial"></p>

<p align = "center">
    <img src="https://img.shields.io/github/license/GuilhermeAchilles/Guilherme_Achilles_embarcatech_HBr_2025?cacheSeconds=3600"
     width="100px">
</p>

# Sobre o Repositório

Este repositório é destinado a guardar e disponibilizar todos os projetos desenvolvidos durante a residência de sistemas embarcados - EMBARCATECH.

# Plataforma Utilizada 

Todos os projetos utilizam a placa [BITDOGLAB](https://github.com/BitDogLab/BitDogLab).

<p align ="center"><img src="assets/placa_bitdoglab.jpeg" width="400" alt="Imagem da BitDogLab"></p>

# Projetos

<details>
<summary>📌 Contador decrescente com contagem de aperto de botão — Um cronômetro que reinicia com botão e registra toques em outro</summary>

Projeto que utiliza dois botões:  
- O botão A reinicia um contador regressivo de 10 segundos.  
- O botão B registra quantas vezes foi pressionado durante a contagem.  
Essas informações são atualizadas em tempo real em um display OLED.

</details>

<details>
<summary>🎮 Leitura dos valores dos potenciômetros do Joystick — Mostra os valores analógicos suavizados dos eixos X e Y</summary>

Leitura contínua dos valores analógicos dos eixos X e Y do joystick (vRx e vRy) com uso de média móvel (janela de 50 amostras).  
Os valores são atualizados e exibidos no display OLED apenas quando houver mudança significativa, otimizando a atualização visual.

</details>

<details>
<summary>🌡️ Monitoramento de temperatura interna do RP2040 — Mostra temperatura média em tempo real no display</summary>

Leitura da temperatura interna do microcontrolador RP2040 via ADC, convertendo para Celsius com fórmula fornecida pela documentação oficial.  
É feita uma média móvel de 20 leituras para exibir um valor mais estável no display OLED. Ideal para aplicações de monitoramento embarcado.

</details>

# Licenças

Os códigos desenvolvidos nesse repositório são de uso livre, conforme a [GNU license].
