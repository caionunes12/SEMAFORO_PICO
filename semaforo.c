#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definir os pinos para os LEDs
#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13
#define GND_PIN 8  // Definindo o pino GPIO 8 como GND para o circuito

// Variáveis de controle para o estado do semáforo
int semaforo_estado = 0;

// Função de callback para o temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Controlar a mudança do estado do semáforo
    switch (semaforo_estado) {
        case 0:
            gpio_put(LED_VERMELHO, 1);  // Acende o LED vermelho
            gpio_put(LED_AMARELO, 0);   // Apaga o LED amarelo
            gpio_put(LED_VERDE, 0);     // Apaga o LED verde
            semaforo_estado = 1;         // Próximo estado
            break;
        case 1:
            gpio_put(LED_VERMELHO, 0);  // Apaga o LED vermelho
            gpio_put(LED_AMARELO, 1);   // Acende o LED amarelo
            gpio_put(LED_VERDE, 0);     // Apaga o LED verde
            semaforo_estado = 2;         // Próximo estado
            break;
        case 2:
            gpio_put(LED_VERMELHO, 0);  // Apaga o LED vermelho
            gpio_put(LED_AMARELO, 0);   // Apaga o LED amarelo
            gpio_put(LED_VERDE, 1);     // Acende o LED verde
            semaforo_estado = 0;         // Retorna ao estado inicial
            break;
    }

    return true;  // Retorna verdadeiro para continuar chamando o temporizador
}

int main() {
    // Inicializar os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializar o pino GPIO 8 como saída (GND no circuito)
    gpio_init(GND_PIN);
    gpio_set_dir(GND_PIN, GPIO_OUT);

    // Inicializar a comunicação serial
    stdio_init_all();

    // Criar um temporizador que chama a função de callback a cada 3000ms
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Imprimir uma mensagem a cada segundo
        printf("Semáforo em funcionamento... Estado: %d\n", semaforo_estado);
        sleep_ms(1000);
    }

    return 0;
}
