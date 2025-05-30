#include <stdio.h>
#include <string.h>
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

    // Credenciais da rede Wi-Fi
    const char *ssid = "NetCasa";
    const char *password = "982822588";

    // Informações do MQTT
    const char *client_id = "Rasp_2";
    const char *broker_ip = "192.168.1.114";

    // Mensagem de inicialização
    for (int i = 0; i < 5; i++) {
        printf("Iniciando o sistema, tentativa %d...\n", i + 1);
        sleep_ms(1000);
    }

    // Conectar no Wi-Fi
    printf("Inindo conexão Wi-Fi...\n");
    connect_to_wifi(ssid, password);

    clear_display();
    char *text2[] = {"Conectando MQTT"};
    write_string(text2, 10, 32, 1);
    show_display();

    // Conectar no broker MQTT
    printf("Iniciando conexão MQTT...\n");
    mqtt_setup(client_id, broker_ip, NULL, NULL);
    mqtt_comm_subscribe("escola/sala1/temperatura");

    

    // Loop de publicação
    while (true) 
    {   
        tight_loop_contents();
    }

    return 0;
}
