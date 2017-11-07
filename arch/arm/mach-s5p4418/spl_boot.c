#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

#include <asm/arch/s5p4418.h>
#include <asm/arch/s5p4418_syscon.h>
#include <asm/arch/s5p4418_gpio.h>

extern void s5p4418_ddr3_init(void);
extern void mem_init(void);
extern unsigned long timer_read_counter(void);

void
board_init_f(ulong dummy)
{
  s5p4418_board_pll_clk_init();

  //
  // perform entire IP peripheral reset
  //
  s5p4418_ip_reset(0, 0xffffffff);
  s5p4418_ip_reset(1, 0xffffffff);
  s5p4418_ip_reset(2, 0xffffffff);

	board_early_init_f();     // after this, you can call debug()
  timer_init();

  debug("debug: board_init_f\n");

  //s5p4418_board_memory_init();

  //s5p4418_ddr3_init();    // test code
  mem_init();

  debug("debug: ddr3 init done\n");

#if 0
  debug("concontrol %x\n", readl(0xc00e0000));
  debug("memcontrol %x\n", readl(0xc00e0004));
  debug("memconfig  %x\n", readl(0xc00e0008));
  debug("phycontrol %x\n", readl(0xc00e0018));
  debug("phystatus  %x\n", readl(0xc00e0040));
  debug("membase    %x\n", readl(0xc00e010c));
  debug("PHY_CON0   %x\n", readl(0xc00e1000));
  debug("PHY_CON12  %x\n", readl(0xc00e1030));
  debug("PHY_CON14  %x\n", readl(0xc00e1038));
#endif

#if 1
  {
    int cnt = 0;
    s5p4418_gpio_t*   gpiob = (s5p4418_gpio_t*)S5P4418_BASE_GPIO_B;
    volatile u32*   ptr = (volatile u32*)(0x40000000);
    unsigned long     prev;
    u8    on_off = 0;
    u32 cycle = 0;

    // we have 1 GB memory

    prev = timer_read_counter();
    while(1)
    {
      if((timer_read_counter() - prev) >= 1000 * 100)
      {
        on_off = !on_off;
        s5p4418_gpio_set_output(gpiob, 12, on_off);
        prev = timer_read_counter();
      }

      //debug("testing ...... %d\n", cnt);
      cnt++;

      *ptr = (u32)cnt;
      if(*ptr != (u32)cnt)
      {
        while(1)
        {
          debug("ddr test failed %x, %x, %x\n", (u32)ptr, *ptr, cnt);
        }
      }
      //debug("addr : %x\n", (u32)ptr);

      ptr++;

      if((u32)ptr >= (0x40000000U + 0x40000000U))
      {
        ptr = (volatile u32*)(0x40000000);
        debug("cycle %d finished\n", cycle++);
      }
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
