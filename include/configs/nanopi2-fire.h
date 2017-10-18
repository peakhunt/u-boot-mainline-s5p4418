#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SPL_TEXT_BASE    0xffff0000
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

#endif /* !__CONFIG_H */
