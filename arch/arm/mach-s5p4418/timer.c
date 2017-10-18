#include <common.h>
#include <asm/io.h>

int timer_init(void)
{
#if 0
  at91_pit_t *pit = (at91_pit_t *)ATMEL_BASE_PIT;

  /* Enable PITC Clock */
  at91_periph_clk_enable(ATMEL_ID_PIT);

  /* Enable PITC */
  writel(TIMER_LOAD_VAL | AT91_PIT_MR_EN , &pit->mr);

  gd->arch.timer_rate_hz = get_pit_clk_rate() / 16;
#endif

  return 0;
}

/*
    * Return the number of timer ticks per second.
     */
ulong get_tbclk(void)
{
  /*
  return gd->arch.timer_rate_hz;
  */
  return 0;
}

unsigned long
timer_read_counter(void)
{
  return 0;
}
