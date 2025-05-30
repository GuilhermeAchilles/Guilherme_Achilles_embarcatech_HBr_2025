#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para rand()
#include "pico/stdlib.h"
#include "wifi_control.h"
#include "mqtt_comm.h"
#include "write_display.h"

int main() {

    stdio_init_all();

    init_display();
    clear_display();
    char *text[] = {"Conectando wi-fi"};
    write_string(text, 15, 32, 1);
    show_display();

    // Inicializa gerador de números aleatórios
    srand(time_us_64());

    // Credenciais da rede Wi-Fi
    const char *ssid = "NetCasa";
    const char *password = "982822588";

    // Informações do MQTT
    const char *client_id = "Rasp_1";
    const char *broker_ip = "192.168.1.114";

    // Mensagem temporária
    char mensagem[10];  // Buffer para armazenar número como string

    // Mensagem de inicialização
    for (int i = 0; i < 5; i++) {
        printf("Iniciando o sistema, tentativa %d...\n", i + 1);
        sleep_ms(1000);
    }

    // Conectar no Wi-Fi
    printf("Iniciando conexão Wi-Fi...\n");
    connect_to_wifi(ssid, password);

    clear_display();
    char *text2[] = {"Conectando MQTT"};
    write_string(text2, 10, 32, 1);
    show_display();

    // Conectar no broker MQTT
    printf("Iniciando conexão MQTT...\n");
    mqtt_setup(client_id, broker_ip, NULL, NULL);

    // Loop de publicação
    while (true) 
    {
        clear_display();
        char *text[] = {"Enviando:"};
        write_string(text, 1, 2, 1);

        int random_message = rand() % 51; // Número entre 0 e 50
        sprintf(mensagem, "%d", random_message); // Converte para string

        char *mensagem_dois[] = {mensagem};

        write_string(mensagem_dois, 60 ,32, 2);
        printf("Publicando mensagem: %s\n", mensagem);
        show_display();

        mqtt_comm_publish("escola/sala1/temperatura", mensagem, strlen(mensagem));

        sleep_ms(1000); // Espera 1 segundo para a próxima publicação
    }

    return 0;
}
