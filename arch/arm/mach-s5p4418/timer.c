#include <common.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

int timer_init(void)
{
  // PCLK is 166 Mhz
  // so using 166 prescaler, we can get 1 Mhz timer
  writel(165, 0xc0017000);

  // TCNTB0 = 0xffffffff
  writel(0xffffffff, 0xc001700c);

  // TCMPB0 = 0x0
  writel(0x00, 0xc0017010);

  // TCNTO0 will be read by system

  // TCON. start timer in interval mode
  writel(   (1 << 1), 0xc0017008);
  writel(   (1 << 0)          |       // timer0 start
            (1 << 3)                  // auto reload enable
            , 0xc0017008);

  gd->arch.timer_rate_hz = 1000 * 1000;

  return 0;
}

/*
    * Return the number of timer ticks per second.
     */
ulong get_tbclk(void)
{
  return gd->arch.timer_rate_hz;
}

unsigned long
timer_read_counter(void)
{
  u32 l;

  l = readl(0xc0017014);
  l = 0xffffffff - l;

  return l;
}
