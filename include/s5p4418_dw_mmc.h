#ifndef _S5P4418_DW_MMC_H
#define _S5P4418_DW_MMC_H

struct s5p4418_dwmci_plat {
  struct mmc_config   cfg;
  struct mmc          mmc;

  void*               base;
  u8                  buswidth;
  u8                  dev_index;
};

#if !CONFIG_IS_ENABLED(DM_MMC)
extern void s5p4418_dwmmc_init(const struct s5p4418_dwmci_plat* plat, struct dwmci_host* host);
#endif

#endif /* !_S5P4418_DW_MMC_H */

