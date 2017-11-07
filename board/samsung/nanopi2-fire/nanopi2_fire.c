#include <common.h>
#include <dm.h>
#include <errno.h>
#include <spl.h>
#include <serial.h>
#include <debug_uart.h>

#include <asm/arch/s5p4418_common.h>
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

void
s5p4418_board_pll_clk_init(void)
{
	//////////////////////////////////////////////////////////////////////////
  //
  // PLL0 : 1 GHz for f/h/b/p clk
  // PLL1 : 800 Mhz for md/m/mb/mp clk
  // PLL2 :
  // PLL3 :
  //
  // fclk : 1 Ghz
  // hclk : 250 Mhz
  // bclk : 333 Mhz
  // pclk : 166
  //
  // mdclk : 800 Mhz
  // mclk  : 800 Mhz
  // MBCLK : 400 Mhz
  // MPCLK : 200 Mhz
  //
  //////////////////////////////////////////////////////////////////////////
  s5p4418_syscon_t*   reg;

  reg = (s5p4418_syscon_t*)S5P4418_BASE_SYS_CON;

  // PLL0, SDIV: 1, MDIV: 500, PDIV : 6
  writel(S5P4418_PLL_SDIV(1)    |
         S5P4418_PLL_MDIV(500)  |
         S5P4418_PLL_PDIV(6)    |
         S5P4418_PLL_OUTDIV(0)  |
         S5P4418_PLL_BYPASS(1)  |
         S5P4418_PLL_PD(0)      |
         S5P4418_PLL_SSCG_EN(0),
         &reg->pllsetreg0);

  s5p4418_update_pll(reg, 0);

  // setup f/h clk
  writel(S5P4418_CLKSEL_FCLKCPU0(0)   |
         S5P4418_CLKDIV_FCLKCPU0(0)   |
         S5P4418_CLKDIV_HCLKCPU0(3),
         &reg->clkdivreg0);

  // setup b/p clk
  writel(S5P4418_CLKSEL_BCLK(0)       |
         S5P4418_CLKDIV_BCLK(2)       |
         S5P4418_CLKDIV_PCLK(1),
         &reg->clkdivreg1);

  // PLL1 SDIV : 1, MDIV: 400, PDIV: 6
  writel(S5P4418_PLL_SDIV(1)    |
         S5P4418_PLL_MDIV(400)  |
         S5P4418_PLL_PDIV(6)    |
         S5P4418_PLL_OUTDIV(0)  |
         S5P4418_PLL_BYPASS(1)  |
         S5P4418_PLL_PD(0)      |
         S5P4418_PLL_SSCG_EN(0),
         &reg->pllsetreg1);

  s5p4418_update_pll(reg, 1);

  //
  // setup mdclk/mclk/mbclk/mpclk
  // MDCLK : PLL1 / 1     = 800
  // MCLK  : MDCLK / 1    = 800
  // MBCLK : MCLK / 2     = 400
  // MPCLK : MBCLK / 2    = 200
  //
  writel(S5P4418_CLKSEL_MDCLK(1)    |
         S5P4418_CLKDIV_MDCLK(0)    |
         S5P4418_CLKDIV_MCLK(0)     |
         S5P4418_CLKDIV_MBCLK(1)    |
         S5P4418_CLKDIV_MPCLK(1),
         &reg->clkdivreg2);

  // PLL2
  // FIXME
  //

  //
  // PLL3
}

void
s5p4418_board_memory_init(void)
{
  // nanopi2 uses 2 x K4B4G1646D-BCK0, which provides total 1 GB of memory
  //
  // the SDRAM is 256Mx16 with the following characteristics.
  // - 8 Banks
  // - 15 bit row address
  // - 10 bit column address
  // - 6-6-6 DDR3-800 timing
  //

  // mem control
  // 0x0000020a
  // mrr_byte     : don't know
  // pzq_en       : don't know
  // rsvd         : 0
  // bl           : 0x03,     8 bit burst
  // num_chip     : 0x01,     1
  // mem_width    : 0x02,     32 bit
  // add_lat_pall : don't know
  // dsref_en     : don't know
  // tp_en        : don't know
  // dpwrdn_type  : don't know
  // dpwrdn_en    : don't know
  // clk_stop_en  : don't know
  // 
  //
  // mem config 0
  // 0x00001333
  // chip map   : 0x01, interleaved
  // chip col   : 0x03, 10 bit
  // chip row   : 0x03, 15 bit
  // chip bank  : 0x03, 8 bank
  //
  // mem config 1
  // not used

}
