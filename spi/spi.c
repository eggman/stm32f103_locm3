#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

static void clock_setup(void)
{
  /* Enable HSE. */
  rcc_clock_setup_in_hse_12mhz_out_72mhz();

  /* Enable GPIOA clock. */
  rcc_periph_clock_enable(RCC_GPIOA);

  /* Enable SPI3 clock. */
  rcc_periph_clock_enable(RCC_SPI3);
}

static void spi_setup(void)
{
  /* Configure GPIOs: SS=PA4, SCK=PA5, MISO=PA6 and MOSI=PA7 */
  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO4 | GPIO5 | GPIO7 );
  gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO6);

  /* Reset SPI3. */
  spi_reset(SPI3);

  /* Set up SPI3. */
  spi_init_master(SPI3,
                  SPI_CR1_BAUDRATE_FPCLK_DIV_64,
                  SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE,
                  SPI_CR1_CPHA_CLK_TRANSITION_2,
                  SPI_CR1_DFF_8BIT,
                  SPI_CR1_MSBFIRST);

  /* Set NSS management to software.  */
  spi_enable_software_slave_management(SPI3);
  spi_set_nss_high(SPI3);

  /* Enable SPI3. */
  spi_enable(SPI3);
}

int main(void)
{
  int counter = 0;

  clock_setup();
  spi_setup();

  while (1) {
    spi_send(SPI3, (uint8_t) counter);
    spi_read(SPI3);

    counter++;
  }

  return 0;
}
