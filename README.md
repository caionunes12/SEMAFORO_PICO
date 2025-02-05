# SEMAFORO_PICO

Descrição do Projeto
Este código em C implementa a simulação de um semáforo utilizando o microcontrolador Raspberry Pi Pico com temporização periódica, LEDs e a biblioteca Pico SDK.

Funcionalidades
Controle dos três LEDs (vermelho, amarelo e verde) para simular um semáforo básico:

LED Vermelho: Ligado por 3 segundos, enquanto os LEDs amarelo e verde permanecem apagados.
LED Amarelo: Ligado por 3 segundos, enquanto os LEDs vermelho e verde permanecem apagados.
LED Verde: Ligado por 3 segundos, enquanto os LEDs vermelho e amarelo permanecem apagados.
Uso de um temporizador periódico configurado com a função add_repeating_timer_ms() para alternar os estados do semáforo a cada 3 segundos (3000ms).

Imprime mensagens no terminal serial a cada 1 segundo com o estado atual do semáforo.

O GPIO 8 foi configurado como uma saída lógica baixa para simular uma possível referência de GND no circuito, embora o uso de um pino real de GND seja mais indicado.

Explicação Técnica do Código
Definição de Pinos
c
Copiar
Editar
#define LED_VERMELHO 11 
#define LED_AMARELO 12 
#define LED_VERDE 13 
#define GND_PIN 8
Esses #define associam os números dos GPIOs aos LEDs do semáforo e definem o pino GND_PIN como uma saída configurada para nível lógico baixo.

Inicialização dos LEDs
c
Copiar
Editar
gpio_init(LED_VERMELHO);
gpio_set_dir(LED_VERMELHO, GPIO_OUT);
Cada LED é configurado como um pino de saída usando gpio_init() e gpio_set_dir().

Temporizador Periódico
c
Copiar
Editar
struct repeating_timer timer;
add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
Cria um temporizador que chama a função repeating_timer_callback() a cada 3000ms para alternar os estados do semáforo.

Função Callback
c
Copiar
Editar
bool repeating_timer_callback(struct repeating_timer *t) {
    switch (semaforo_estado) {
        case 0:
            gpio_put(LED_VERMELHO, 1); 
            gpio_put(LED_AMARELO, 0); 
            gpio_put(LED_VERDE, 0); 
            semaforo_estado = 1; 
            break;
        case 1:
            gpio_put(LED_VERMELHO, 0); 
            gpio_put(LED_AMARELO, 1); 
            gpio_put(LED_VERDE, 0); 
            semaforo_estado = 2;
            break;
        case 2:
            gpio_put(LED_VERMELHO, 0); 
            gpio_put(LED_AMARELO, 0); 
            gpio_put(LED_VERDE, 1); 
            semaforo_estado = 0;
            break;
    }
    return true;
}
Essa função alterna o estado dos LEDs conforme o valor da variável semaforo_estado.

Mensagens no Terminal
c
Copiar
Editar
while (true) {
    printf("Semáforo em funcionamento... Estado: %d\n", semaforo_estado);
    sleep_ms(1000);
}
No loop principal, imprime uma mensagem a cada segundo indicando o estado atual do semáforo.

Observações Importantes
Certifique-se de conectar corretamente os LEDs nos GPIOs 11, 12 e 13, com resistores de 330 ohms em série para limitar a corrente.
O pino GND_PIN (GPIO 8) está configurado apenas para simulação lógica e não deve ser utilizado como uma substituição do GND físico.
Para visualizar a saída serial, use um terminal serial configurado com uma taxa de transmissão de 115200 baud.