#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

#include <asm/arch/s5p4418.h>
#include <asm/arch/s5p4418_syscon.h>
#include <asm/arch/s5p4418_gpio.h>

extern void s5p4418_ddr3_init(void);
extern void mem_init(void);

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

  //
  // looks like the max load size is 29184, which is 28.5KB
  // quite funny
  //
  debug("debug: board_init_f\n");
  //s5p4418_board_memory_init();

  mem_init();

  debug("debug: ddr3 init done\n");
#if 0

  if(spl_init() != 0)
  {
    debug("spl_init() failed: \n");
    hang();
  }

  debug("spl_init() done: \n");

  preloader_console_init();
#endif
}
