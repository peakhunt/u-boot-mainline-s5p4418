#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

void
board_init_f(ulong dummy)
{
  //
  // upon system reset
  // pll0 : 550 Mhz
  // bclk : pll0 / 2 = 225 Mhz
  // pclk : bclk / 2 = 112.5 Mhz
  //

  writel(0xffffffff, 0xc0012000);
  writel(0xffffffff, 0xc0012004);
  writel(0xffffffff, 0xc0012008);

  //
  // enable writing to alive register
  // set vddctrlsetreg
  writel(0x01,  0xc0010800);
  writel(0x3fc, 0xc001089c);

  //
  //  rtc or wdt or whatever
  //
  writel(0x01,       0xc0010800);
  writel(0xffffffff, 0xc0010c1c);

  //
  // unknown
  //
  //(void)readl(0xc001027c);

  //
  // clear reset on UART0
  //
  //writel((0x01 << 17), 0xc0012004);

  // GPIO B12 is a LED pin
  // set it to output mode
  // drive it to high to turn off the LED
  //
  // ball W24 should be confitured to ALTF2 for GPIO use
  //
  writel((0x02 << 24), 0xc001b020);        // alt func setup
  writel((0x01 << 12), 0xc001b004);        // output enable
  writel((0x01 << 12), 0xc001b000);        // set high

  while(1)
  {
    for(volatile int i = 0; i < 500000; i++) { }
    writel(0, 0xc001b000);        // set low
    for(volatile int i = 0; i < 500000; i++) { }
    writel((0x01 << 12), 0xc001b000);        // set high
  }

  //
  // UART0 pin  mux
  // AD19   : TX, GPIOD18, AF1
  // AE19   : RX, GPIOD14, AF1
  writel((0x1 << 4),  0xc001d024);
  writel((0x1 << 28), 0xc001d020);

  // set up 50 Mhz uart clock
  // default pll0 runs at 550 Mhz. so we use clock divider 11
  writel(0x00000140, 0xC00A9004);

  // enable uart clock
  writel(0x00000004, 0xC00A9000);

  debug_uart_init();

  printch('*');

  debug("debug: board_init_f\n");

  while(1)
  {
  }

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
