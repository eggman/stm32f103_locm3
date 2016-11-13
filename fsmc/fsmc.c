#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/fsmc.h>

#define __IO    volatile
#define fsmc_test_address    ((uint32_t)0x60000000)

static void clock_setup(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  /* Enable GPIOC clock. */
  rcc_periph_clock_enable(RCC_GPIOA);

  /* Enable PORTD and PORTE */
  rcc_periph_clock_enable(RCC_GPIOD);
  rcc_periph_clock_enable(RCC_GPIOE);

  /* Enable FSMC */
  rcc_periph_clock_enable(RCC_FSMC);
}

static void fsmc_setup(void)
{
  /* config FSMC data lines */
  uint16_t portd_gpios = GPIO0 | GPIO1 | GPIO8 | GPIO9 |
                         GPIO10 | GPIO14 | GPIO15;
  gpio_set_mode(GPIOD, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, portd_gpios);

  uint16_t porte_gpios = GPIO7 | GPIO8 | GPIO9 | GPIO10 | 
                         GPIO11 | GPIO12 | GPIO13 | GPIO14 |
                         GPIO15;
  gpio_set_mode(GPIOE, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, porte_gpios);

  /* config FSMC NOE */
  gpio_set_mode(GPIOD, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO4);

  /* config FSMC NWE */
  gpio_set_mode(GPIOD, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO5);
  
  /* config FSMC NE1 */
  gpio_set_mode(GPIOD, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO7);

  /* config FSMC register */
  FSMC_BTR(0) = FSMC_BTR_ACCMODx(FSMC_BTx_ACCMOD_B) |
                FSMC_BTR_DATLATx(0)  |
                FSMC_BTR_CLKDIVx(0)  |
                FSMC_BTR_BUSTURNx(0) |
                FSMC_BTR_DATASTx(3)  |
                FSMC_BTR_ADDHLDx(0)  |
                FSMC_BTR_ADDSETx(0);

  FSMC_BCR(0) = FSMC_BCR_WREN | FSMC_BCR_MWID | FSMC_BCR_MBKEN;
}

int main(void)
{
  uint16_t d=0;

  clock_setup();
  fsmc_setup();

  while (1) {
    *(__IO uint16_t *) (fsmc_test_address) = d;
    d += 1;
  }

  return 0;
}

