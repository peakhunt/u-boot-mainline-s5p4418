#define DEBUG 1
#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

void
board_init_f(ulong dummy)
{
  // change pll0 to 400 Mhz
  // p 6
  // m 400
  // s 2
  //
  // accordingly
  //
  // fclk : 400 / 2       = 200
  // hclk : fclk / 2      = 100
  // bclk : 400 / 2       = 200
  // pclk: bclk / 2       = 100
  //
  writel(   (2 << 0)    |       // sdiv
            (400 << 8)  |       // mdiv
            (6 << 18)   |       // pdiv
            (0 << 24)   |       // outdiv
            (1 << 28)           // normal output
            , 0xC0010008);

  // update pll0
  writel(   (1 << 0), 0xC0010000);

  while(readl(0xC0010000) & 0x80000000)
  {
  }

#if 0
  //
  // enable writing to alive register
  // set vddctrlsetreg
  //
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
#endif

  // GPIO B12 is a LED pin
  // set it to output mode
  // drive it to high to turn off the LED
  //
  // ball W24 should be set to ALTF2 for GPIO use
  //
  writel((0x02 << 24), 0xc001b020);        // alt func setup
  writel((0x01 << 12), 0xc001b004);        // output enable
  writel((0x01 << 12), 0xc001b000);        // set high

  //
  // UART0 pin  mux
  // AD19   : TX, GPIOD18, AF1
  // AE19   : RX, GPIOD14, AF1
  writel((0x1 << 4),  0xc001d024);
  writel((0x1 << 28), 0xc001d020);

  // reset everything
  //writel(~(1 << 17), 0xc0012004);
  writel(0, 0xc0012000);
  writel(0, 0xc0012004);
  writel(0, 0xc0012008);
  writel(0xffffffff, 0xc0012004);
  writel(0xffffffff, 0xc0012000);
  writel(0xffffffff, 0xc0012008);


  // set up 50 Mhz uart clock out of 400 Mhz PLL0 using divider 8
  writel(   (0 << 15)|        // out clock enable
            (7 << 5) |        // clock divider
            (0 << 2) |        // clock source
            (0 << 1)          // clock invert
            , 0xC00A9004);
  writel(1 << 2, 0xC00A9000);         // enable uart clock

  debug_uart_init();

  debug("debug: board_init_f\n");

#if 0
  //
  // let's do some verification
  //
  {
    u32   tmp;

    // PLLSETREG0 : 0xc0010008
    tmp = readl(0xc0010008);
    if(tmp != 0x101A2602)
    {
      hang();
    }

    // PLLSETREG1
    tmp = readl(0xc001000c);
   if(tmp != 0x101A4E04)
   {
     hang();
   }

#if 0
   // PLLSETREG2
   tmp = readl(0xc0010010);
   if(tmp != 0x100CC004)
   {
     hang();
   }

   // PLLSETREG3
   // XXX
   // this guy's reset value seems to be different from the one specified in datasheet
   //
   tmp = readl(0xc0010014);
   if(tmp != 0x100C0FA4)
   {
     hang();
   }
#endif

   //
   // CLKDIVREG0
   //
   tmp = readl(0xc0010020);
   if(tmp != 0x00008208)
   {
     hang();
   }

#if 1
   // CLKDIVREG1
   tmp = readl(0xc0010024);
   if(tmp != 0x00008208)
   {
     hang();
   }
#endif

#if 1
   //
   // check UART0 enabled
   //
   tmp = readl(0xC00A1030);
   if(!(tmp & (1 << 0 | 1 << 8 | 1 << 9)))
   {
     hang();
   }

   if(tmp & (1 << 1))
   {
     hang();
   }
#endif
  }
#endif

#if 1
  {
    const int interval = 500000;
    int cnt = 0;

    while(1)
    {

      for(volatile int i = 0; i < interval; i++) { }
      writel(0, 0xc001b000);        // set low
      for(volatile int i = 0; i < interval; i++) { }
      writel((0x01 << 12), 0xc001b000);        // set high

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
