#include <common.h>
#include <dm.h>
#include <errno.h>
#include <spl.h>
#include <serial.h>
#include <debug_uart.h>

#include <asm/arch/s5p4418.h>
#include <asm/arch/s5p4418_syscon.h>
#include <asm/arch/s5p4418_gpio.h>
#include <asm/arch/s5p4418_clk_gen.h>

int board_init(void)
{
  /* Set Initial global variables */
  /*
  gd->bd->bi_arch_number = MACH_TYPE_GONI;
  gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
  */

  return 0;
}


int dram_init(void)
{
  /*
  gd->ram_size = PHYS_SDRAM_1_SIZE + PHYS_SDRAM_2_SIZE + PHYS_SDRAM_3_SIZE;
  */
  return 0;
}

#ifndef CONFIG_DM_SERIAL
struct serial_device *default_serial_console(void)
{
#if 0
  if (board_is_icev2())
    return &eserial4_device;
  else
    return &eserial1_device;
#endif
  return NULL;
}
#endif

#ifdef CONFIG_DEBUG_UART_BOARD_INIT
void board_debug_uart_init(void)
{
  s5p4418_gpio_t*     gpiod   = (s5p4418_gpio_t*)S5P4418_BASE_GPIO_D;
  s5p4418_clk_gen_t*  clkgen  = (s5p4418_clk_gen_t*)S5P4418_BASE_UART0_CLKENB;

  //
  // nanopi2-fire uses UART0 as console
  //

  //
  // setup GPIO
  // UART0 uses GPIOD18/14 for TX/RX.
  // their alt function is 1
  //
  s5p4418_gpio_set_altfn(gpiod, 18, 1);
  s5p4418_gpio_set_altfn(gpiod, 14, 1);

  //
  // setup UART clock
  // only supports 50 Mhz for now
  // using 1 Ghz PLL0 and clock divider 20
  //
  writel( S5P4418_UART_OUTCLKINV0(0)      |
          S5P4418_UART_CKSRCSEL0(0)       |
          S5P4418_UART_CLKDIV0(19)        |
          S5P4418_UART_OUTCLKENB(0),
          &clkgen->clkgen0l);
  writel( S5P4418_UART_CLKGEN_ENB(1),
          &clkgen->clkenb);

}
#endif

#ifdef CONFIG_BOARD_EARLY_INIT_F
static inline void
setup_blue_led(void)
{
  //
  // setup blue LED
  // GPIO-B12 is connected to LED
  //
  s5p4418_gpio_t*   reg = (s5p4418_gpio_t*)S5P4418_BASE_GPIO_B;

  // b12, alt function 2
  s5p4418_gpio_set_altfn(reg, 12, 2);

  // setup B12 as output
  s5p4418_gpio_set_io_mode(reg, 12, 1);

  // set B12 high to that LED goes off.
  s5p4418_gpio_set_output(reg, 12, 0);

}

int board_early_init_f(void)
{
  setup_blue_led();

#ifdef CONFIG_DEBUG_UART
  debug_uart_init();
#endif
  return 0;
}
#endif
