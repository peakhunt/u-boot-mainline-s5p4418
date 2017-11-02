#define DEBUG 1
#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

#include <asm/arch/s5p4418.h>
#include <asm/arch/s5p4418_syscon.h>
#include <asm/arch/s5p4418_gpio.h>

static inline void
update_pll(s5p4418_syscon_t* reg, u8 pll_num)
{
  writel(S5P4418_UPDATE_PLL(pll_num), &reg->clkmodereg0);

  while(readl(&reg->clkmodereg0) & S5P4418_WAIT_UPDATE_PLL)
    ;
}

static void
setup_pll_clock(void)
{
  //////////////////////////////////////////////////////////////////////////
  //
  // PLL0 : 1 GHz for f/h/b/p clk
  // PLL1 : 800 Mhz for DDR3
  // PLL2 :
  // PLL3 :
  //
  // fclk : 1 Ghz
  // hclk : 250 Mhz
  // bclk : 333 Mhz
  // pclk : 166
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

  update_pll(reg, 0);

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

  update_pll(reg, 1);

  // PLL2
  // FIXME
  //

  //
  // PLL3
  // FIXME
}

void
board_init_f(ulong dummy)
{
  setup_pll_clock();

  //
  // perform entire IP peripheral reset
  //
  s5p4418_ip_reset(0, 0xffffffff);
  s5p4418_ip_reset(1, 0xffffffff);
  s5p4418_ip_reset(2, 0xffffffff);

	board_early_init_f();     // after this, you can call debug()

  debug("debug: board_init_f\n");

#if 1
  {
    const u32 interval = 0x00ffffff;
    int cnt = 0;
    s5p4418_gpio_t*   gpiob = (s5p4418_gpio_t*)S5P4418_BASE_GPIO_B;

    while(1)
    {
      for(u32 i = 0; i < interval; i++) { asm("nop"); }
      s5p4418_gpio_set_output(gpiob, 12, 0);
      for(u32 i = 0; i < interval; i++) { asm("nop"); }
      s5p4418_gpio_set_output(gpiob, 12, 1);

      debug("testing ...... %d\n", cnt);
      cnt++;
    }
  }
#endif

#if 0
	switch_to_main_crystal_osc();

#ifdef CONFIG_SAMA5D2
	configure_2nd_sram_as_l2_cache();
#endif

	/* disable watchdog */
	at91_disable_wdt();

	/* PMC configuration */
	at91_pmc_init();

	at91_clock_init(CONFIG_SYS_AT91_MAIN_CLOCK);

	matrix_init();

	redirect_int_from_saic_to_aic();

	timer_init();

	board_early_init_f();

	mem_init();
#endif
  if(spl_init() != 0)
  {
		debug("spl_init() failed: \n");
		hang();
	}

  printf("S5P4418: board_init_f()\n");

	preloader_console_init();

  printf("S5P4418: board_init_f()\n");
}

u32
spl_boot_device(void)
{
  return 0;
}

u32 spl_boot_mode(const u32 boot_device)
{
  return 0;
}
