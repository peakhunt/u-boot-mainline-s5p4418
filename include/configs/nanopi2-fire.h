#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_DM_WARN          1
#define CONFIG_BOUNCE_BUFFER    1

#define CONFIG_SPL_TEXT_BASE    0xffff0000
#define CONFIG_SPL_STACK        0xffffffff

#define CONFIG_SPL_MAX_SIZE         0x8000

#define CONFIG_SYS_LOAD_ADDR        0x42c00000
#define CONFIG_SYS_TEXT_BASE        CONFIG_SYS_LOAD_ADDR
#define CONFIG_SYS_INIT_SP_ADDR     CONFIG_SYS_TEXT_BASE

#define CONFIG_SYS_SDRAM_BASE       0x40000000
#define CONFIG_SYS_SDRAM_SIZE       0x40000000

#define CONFIG_SYS_MALLOC_LEN       (32*1024*1024)    /* 32 MB. big enough */

/* nanopi2-fire has 2 banks of DRAM, but swap the bank */
#define CONFIG_NR_DRAM_BANKS	2

/* FLASH and environment organization */
#define CONFIG_MMC_DEFAULT_DEV	  0
#define CONFIG_SYS_MMC_ENV_DEV		CONFIG_MMC_DEFAULT_DEV
#define CONFIG_ENV_SIZE           4096
#define CONFIG_ENV_OFFSET		      ((32 - 4) << 10) /* 32KiB - 4KiB */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_USE_SECTOR         1
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR             64

#define CONFIG_SPL_FRAMEWORK  

#if !defined(CONFIG_SPL_BUILD) || defined(CONFIG_SPL_SERIAL_SUPPORT)
#define CONFIG_CONS_INDEX   0
#define CONFIG_PL01X_SERIAL
#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK    50000000
#define CONFIG_PL01x_PORTS    { (void*)0xc00a1000}
#endif

#ifdef CONFIG_SPL_BUILD
#undef CONFIG_DM_MMC        /* too many bugs not using CONFIG_IS_ENABLED */
#endif

#endif /* !__CONFIG_H */
