#include <common.h>
#include <asm/io.h>

#if 0
int arch_cpu_init(void)
{
  return 0;
}

void arch_preboot_os(void)
{
}

int arch_misc_init(void)
{
  return 0;
}

void enable_caches(void)
{
  icache_enable();
  dcache_enable();
}

unsigned int get_chip_id(void)
{
  return 0;
}

unsigned int get_extension_chip_id(void)
{
  return 0;
}
#endif



#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo(void)
{
  /*
  char buf[32];

  printf("CPU: %s\n", get_cpu_name());
  printf("Crystal frequency: %8s MHz\n",
      strmhz(buf, get_main_clk_rate()));
  printf("CPU clock        : %8s MHz\n",
      strmhz(buf, get_cpu_clk_rate()));
  printf("Master clock     : %8s MHz\n",
      strmhz(buf, get_mck_clk_rate()));
  */

  return 0;
}
#endif
