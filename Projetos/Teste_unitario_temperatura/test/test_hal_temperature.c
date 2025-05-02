#include "ler_temperatura.h"
#include "unity.h" 

void setUp() {};
void tearDown() {};

void test_adc_to_celsius(void) {

    float tensao = 0.706f; // Tensão de entrada
    float expected_temperature = 27.0f; // Temperatura esperada em Celsius
    float delta = 1.0f; // Tolerância de 1 grau Celsius

   TEST_ASSERT_FLOAT_WITHIN(delta, expected_temperature, adc_to_celsius(tensao)); // Verifica se a temperatura lida está dentro do intervalo esperado
}
 
int main(void) {
    UNITY_BEGIN(); // Inicia o Unity
    RUN_TEST(test_adc_to_celsius); // Executa o teste
    return UNITY_END(); // Finaliza o Unity e retorna o resultado dos testes
}