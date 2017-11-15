#include <common.h>
#include <dm.h>
#include <dwmmc.h>
#include <malloc.h>
#include <errno.h>
#include <linux/err.h>

DECLARE_GLOBAL_DATA_PTR;

struct s5p4418_dwmci_plat {
  struct mmc_config   cfg;
  struct mmc          mmc;

  void*               base;
  u8                  buswidth;
  u8                  dev_index;
};

struct dwmci_s5p4418_priv_data {
  struct dwmci_host   host;
};

__weak
void s5p4418_dwmci_board_setup(struct dwmci_host* host)
{
  debug("fuck\n");
}

static void s5p4418_dwmci_clksel(struct dwmci_host* host)
{
#if 0
  struct dwmci_s5p4418_priv_data* priv = host->priv;

  /* FIXME */
  (void)priv;
#else
  u32 val;

  val = (0 << 0)      |     // shift
    (0 << 16)     |     // drive clock
    (3 << 24)     ;     // div ratio

  dwmci_writel(host, 0x09c, val);
#endif
}

#if CONFIG_IS_ENABLED(DM_MMC)
static int s5p4418_dwmmc_ofdata_to_platdata(struct udevice* dev)
{
  /*DTB support is not yet implemented */
  /* XXX what about clock and pinmux? */
  debug("Warning : DTB support is not yet implemented\n");

  return 0;
}

static int s5p4418_dwmmc_probe(struct udevice* dev)
{
#ifdef CONFIG_BLK
  struct s5p4418_dwmci_plat *plat = dev_get_platdata(dev);
#endif
  struct mmc_uclass_priv *upriv   = dev_get_uclass_priv(dev);
  struct dwmci_s5p4418_priv_data *priv = dev_get_priv(dev);
  struct dwmci_host *host = &priv->host;

#ifdef CONFIG_BLK
  host->name        = dev->name;

  host->ioaddr      = plat->base;
  host->buswidth    = plat->buswidth;
  host->dev_index   = plat->dev_index;
  host->clksel      = s5p4418_dwmci_clksel;
  host->board_init  = s5p4418_dwmci_board_setup;

  host->fifo_mode   = 1;    // FIXME
  host->bus_hz      = 200000000;

  debug("%x, %d, %d\n", (u32)plat->base, plat->buswidth, host->bus_hz);

  dwmci_setup_cfg(&plat->cfg, host, 50000000, 400000);
  host->mmc = &plat->mmc;
#else
  int ret;

  ret = add_dwmci(host, 50000000,, 400000);
  if (ret)
    return ret;
#endif
  host->mmc->priv = &priv->host;
  upriv->mmc = host->mmc;
  host->mmc->dev = dev;

  return dwmci_probe(dev);
}

static int s5p4418_dwmmc_bind(struct udevice* dev)
{
#ifdef CONFIG_BLK
  struct s5p4418_dwmci_plat *plat = dev_get_platdata(dev);
  int ret;

  ret = dwmci_bind(dev, &plat->mmc, &plat->cfg);
  if (ret)
    return ret;
#endif

  return 0;
}

static const struct udevice_id s5p4418_dwmmc_ids[] = {
	{ .compatible = "samsung,s5p4418-dw-mshc" },
	{ }
};

U_BOOT_DRIVER(s5p4418_dwmmc_drv) = {
	.name		                  = "s5p4418_dwmmc",
	.id		                    = UCLASS_MMC,
	.of_match	                = s5p4418_dwmmc_ids,
	.ofdata_to_platdata       = s5p4418_dwmmc_ofdata_to_platdata,
	.ops		                  = &dm_dwmci_ops,
	.bind		                  = s5p4418_dwmmc_bind,
	.probe		                = s5p4418_dwmmc_probe,
	.priv_auto_alloc_size     = sizeof(struct dwmci_s5p4418_priv_data),
	.platdata_auto_alloc_size = sizeof(struct s5p4418_dwmci_plat),
};

#else

void
s5p4418_dwmmc_init(const struct s5p4418_dwmci_plat* plat, struct dwmci_host* host)
{
  host->name      = "s5p4418_mmc";

  host->ioaddr      = plat->base;
  host->buswidth    = plat->buswidth;
  host->dev_index   = plat->dev_index;
  host->clksel      = s5p4418_dwmci_clksel;
  host->board_init  = s5p4418_dwmci_board_setup;

  host->fifo_mode   = 1;    // FIXME
  host->bus_hz      = 200000000;

  dwmci_setup_cfg((struct mmc_config*)&plat->cfg, host, 50000000, 400000);
  host->mmc = mmc_create(&plat->cfg, host);
}
#endif
