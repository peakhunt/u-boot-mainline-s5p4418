#include <common.h>
#include <dm.h>
#include <errno.h>
#include <spl.h>
#include <serial.h>

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

