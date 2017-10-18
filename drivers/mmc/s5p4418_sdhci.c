/*
 * Copyright (C) 2015 Atmel Corporation
 *		      Wenyou.Yang <wenyou.yang@atmel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <malloc.h>
#include <sdhci.h>

#ifndef CONFIG_DM_MMC
int s5p4418_sdhci_init(void *regbase, u32 id)
{
#if 0
	struct sdhci_host *host;
	u32 max_clk, min_clk = ATMEL_SDHC_MIN_FREQ;

	host = (struct sdhci_host *)calloc(1, sizeof(struct sdhci_host));
	if (!host) {
		printf("%s: sdhci_host calloc failed\n", __func__);
		return -ENOMEM;
	}

	host->name = "atmel_sdhci";
	host->ioaddr = regbase;
	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD;
	max_clk = at91_get_periph_generated_clk(id);
	if (!max_clk) {
		printf("%s: Failed to get the proper clock\n", __func__);
		free(host);
		return -ENODEV;
	}
	host->max_clk = max_clk;

	add_sdhci(host, 0, min_clk);
#endif
	return 0;
}

#else


static int s5p4418_sdhci_probe(struct udevice *dev)
{
  return 0;
}

static int s5p4418_sdhci_bind(struct udevice *dev)
{
  return 0;
}

static const struct udevice_id s5p4418_sdhci_ids[] = {
	{ .compatible = "samsung,s5p4418-sdhci" },
	{ }
};

U_BOOT_DRIVER(s5p4418_sdhci_drv) = {
	.name		= "s5p4418_sdhci",
	.id		= UCLASS_MMC,
	.of_match	= s5p4418_sdhci_ids,
	.ops		= &sdhci_ops,
	.bind		= s5p4418_sdhci_bind,
	.probe		= s5p4418_sdhci_probe,
	.priv_auto_alloc_size = 0,
	.platdata_auto_alloc_size = 0,
};
#endif
