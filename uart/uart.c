#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

static void clock_setup(void)
{
  /* Enable HSE */
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  /* Enable GPIOA clock. */
  rcc_periph_clock_enable(RCC_GPIOA);

  /* Enable clocks for USART2. */
  rcc_periph_clock_enable(RCC_USART2);
}

static void usart_setup(void)
{
  /* Setup A2 pin GPIO_USART2_TX. */
  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
          GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);

  /* Setup UART parameters. */
  usart_set_baudrate(USART2, 38400);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

  /* Finally enable the USART. */
  usart_enable(USART2);
}

int main(void)
{
  int i, j = 0, c = 0;

  clock_setup();
  usart_setup();

  while (1) {
    usart_send_blocking(USART2, c + '0');  /* USART2: Send byte. */
    c = (c == 9) ? 0 : c + 1;  /* Increment c. */
    if ((j++ % 80) == 0) {  /* Newline after line full. */
      usart_send_blocking(USART2, '\r');
      usart_send_blocking(USART2, '\n');
    }
    for (i = 0; i < 800000; i++)  /* Wait a bit. */
      __asm__("nop");
  }

  return 0;
}

