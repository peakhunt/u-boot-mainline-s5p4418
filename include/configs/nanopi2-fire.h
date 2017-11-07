#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef CONFIG_SPL_BUILD
#undef CONFIG_DM_MMC
#undef CONFIG_CMD_MMC
#endif

#define CONFIG_SPL_TEXT_BASE    0xffff0000
#define CONFIG_SPL_STACK        0xffff8000

#define CONFIG_SPL_MAX_FOOTPRINT    0x4000    /* 16K max */
#define CONFIG_SPL_MAX_SIZE         0x4000
#define CONFIG_SPL_BSS_MAX_SIZE     0x400
#define CONFIG_SPL_BSS_START_ADDR   0xffff6000

#define CONFIG_SYS_TEXT_BASE    0x34800000
#define CONFIG_SYS_LOAD_ADDR    0x22000000

/* nanopi2-fire has 2 banks of DRAM, but swap the bank */
#define CONFIG_NR_DRAM_BANKS	2

/* FLASH and environment organization */
#define CONFIG_MMC_DEFAULT_DEV	  0
#define CONFIG_SYS_MMC_ENV_DEV		CONFIG_MMC_DEFAULT_DEV
#define CONFIG_ENV_SIZE           4096
#define CONFIG_ENV_OFFSET		      ((32 - 4) << 10) /* 32KiB - 4KiB */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_MALLOC_LEN   (CONFIG_ENV_SIZE + (80 << 20))

#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_LOAD_ADDR - 0x1000000)

#define CONFIG_SPL_FRAMEWORK  

#define CONFIG_CONS_INDEX   0
#define CONFIG_PL01X_SERIAL
#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK    50000000
#define CONFIG_PL01x_PORTS    { (void*)0xc00a1000}

/*
#define CONFIG_PL011_SERIAL
#define CONFIG_CONS_INDEX       CFG_UART_DEBUG_CH
#define CONFIG_PL011_CLOCK        CFG_UART_CLKGEN_CLOCK_HZ
#define CONFIG_PL01x_PORTS        { (void *)IO_ADDRESS(PHY_BASEADDR_UART0),   \
                      (void *)IO_ADDRESS(PHY_BASEADDR_UART1) }
*/
/* #define CONFIG_SYS_TIMER_COUNTER        0xc0017014   */

#endif /* !__CONFIG_H */
