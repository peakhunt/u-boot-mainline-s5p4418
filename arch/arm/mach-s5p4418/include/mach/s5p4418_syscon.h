#ifndef _S5P4418_SYSCON_H
#define _S5P4418_SYSCON_H

#include <asm/types.h>

#include <asm/arch/s5p4418_common.h>
#include <asm/arch/s5p4418.h>

typedef struct s5p4418_syscon {
  u32 clkmodereg0;
  u32 clkmodereg1;
  u32 pllsetreg0;
  u32 pllsetreg1;
  u32 pllsetreg2;
  u32 pllsetreg3;
  u32 reserved0[2];
  u32 clkdivreg0;
  u32 clkdivreg1;
  u32 clkdivreg2;
  u32 clkdivreg3;
  u32 clkdivreg4;
} s5p4418_syscon_t;

/* CLKMODEREG0 */
#define S5P4418_UPDATE_PLL_OFF            0
#define S5P4418_UPDATE_PLL_MASK           0xf
#define S5P4418_UPDATE_PLL(x)             (1 << (x & S5P4418_UPDATE_PLL_MASK))
#define S5P4418_WAIT_UPDATE_PLL           0x80000000

/* PLLSETREGx */
#define S5P4418_PLL_SDIV_OFF              0
#define S5P4418_PLL_MDIV_OFF              8
#define S5P4418_PLL_PDIV_OFF              18
#define S5P4418_PLL_OUTDIV_OFF            24
#define S5P4418_PLL_BYPASS_OFF            28
#define S5P4418_PLL_PD_OFF                29
#define S5P4418_PLL_SSCG_EN_OFF           30

#define S5P4418_PLL_SDIV_MASK             0xff
#define S5P4418_PLL_MDIV_MASK             0x3ff
#define S5P4418_PLL_PDIV_MASK             0x3f
#define S5P4418_PLL_OUTDIV_MASK           0xf
#define S5P4418_PLL_BYPASS_MASK           0x1
#define S5P4418_PLL_PD_MASK               0x1
#define S5P4418_PLL_SSCG_EN_MASK          0x1

#define S5P4418_PLL_SDIV(x)               S5P4418_DEFINE_FIELD(x, PLL_SDIV)
#define S5P4418_PLL_MDIV(x)               S5P4418_DEFINE_FIELD(x, PLL_MDIV)
#define S5P4418_PLL_PDIV(x)               S5P4418_DEFINE_FIELD(x, PLL_PDIV)
#define S5P4418_PLL_OUTDIV(x)             S5P4418_DEFINE_FIELD(x, PLL_OUTDIV)
#define S5P4418_PLL_BYPASS(x)             S5P4418_DEFINE_FIELD(x, PLL_BYPASS)
#define S5P4418_PLL_PD(x)                 S5P4418_DEFINE_FIELD(x, PLL_PD)
#define S5P4418_PLL_SSCG_EN(x)            S5P4418_DEFINE_FIELD(x, PLL_SSCG_EN)

/* CLKDIVREGx */
#define S5P4418_CLKSEL_FCLKCPU0_OFF       0
#define S5P4418_CLKDIV_FCLKCPU0_OFF       3
#define S5P4418_CLKDIV_HCLKCPU0_OFF       9

#define S5P4418_CLKSEL_BCLK_OFF           0
#define S5P4418_CLKDIV_BCLK_OFF           3
#define S5P4418_CLKDIV_PCLK_OFF           9

#define S5P4418_CLKSEL_MDCLK_OFF          0
#define S5P4418_CLKDIV_MDCLK_OFF          3
#define S5P4418_CLKDIV_MCLK_OFF           9
#define S5P4418_CLKDIV_MBCLK_OFF          15
#define S5P4418_CLKDIV_MPCLK_OFF          21

#define S5P4418_CLKSET_GR3DBCLK_OFF       0
#define S5P4418_CLKDIV_GR3DBCLK_OFF       3
#define S5P4418_CLKDIV_GR3DPCLK_OFF       9

#define S5P4418_CLKSET_MPEGBCLK_OFF       0
#define S5P4418_CLKDIV_MPEGBCLK_OFF       3
#define S5P4418_CLKDIV_MPEGPCLK_OFF       9

#define S5P4418_CLKSEL_FCLKCPU0_MASK      0x07
#define S5P4418_CLKDIV_FCLKCPU0_MASK      0x3f
#define S5P4418_CLKDIV_HCLKCPU0_MASK      0x3f

#define S5P4418_CLKSEL_BCLK_MASK          0x07
#define S5P4418_CLKDIV_BCLK_MASK          0x3f
#define S5P4418_CLKDIV_PCLK_MASK          0x3f

#define S5P4418_CLKSEL_MDCLK_MASK         0x07
#define S5P4418_CLKDIV_MDCLK_MASK         0x3f
#define S5P4418_CLKDIV_MCLK_MASK          0x3f
#define S5P4418_CLKDIV_MBCLK_MASK         0x3f
#define S5P4418_CLKDIV_MPCLK_MASK         0x3f

#define S5P4418_CLKSET_GR3DBCLK_MASK      0x07
#define S5P4418_CLKDIV_GR3DBCLK_MASK      0x3f
#define S5P4418_CLKDIV_GR3DPCLK_MASK      0x3f

#define S5P4418_CLKSET_MPEGBCLK_MASK      0x07
#define S5P4418_CLKDIV_MPEGBCLK_MASK      0x3f 
#define S5P4418_CLKDIV_MPEGPCLK_MASK      0x3f

#define S5P4418_CLKSEL_FCLKCPU0(x)        S5P4418_DEFINE_FIELD(x, CLKSEL_FCLKCPU0)
#define S5P4418_CLKDIV_FCLKCPU0(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_FCLKCPU0)
#define S5P4418_CLKDIV_HCLKCPU0(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_HCLKCPU0)

#define S5P4418_CLKSEL_BCLK(x)            S5P4418_DEFINE_FIELD(x, CLKSEL_BCLK)
#define S5P4418_CLKDIV_BCLK(x)            S5P4418_DEFINE_FIELD(x, CLKDIV_BCLK)
#define S5P4418_CLKDIV_PCLK(x)            S5P4418_DEFINE_FIELD(x, CLKDIV_PCLK)

#define S5P4418_CLKSEL_MDCLK(x)           S5P4418_DEFINE_FIELD(x, CLKSEL_MDCLK)
#define S5P4418_CLKDIV_MDCLK(x)           S5P4418_DEFINE_FIELD(x, CLKDIV_MDCLK)
#define S5P4418_CLKDIV_MCLK(x)            S5P4418_DEFINE_FIELD(x, CLKDIV_MCLK)
#define S5P4418_CLKDIV_MBCLK(x)           S5P4418_DEFINE_FIELD(x, CLKDIV_MBCLK)
#define S5P4418_CLKDIV_MPCLK(x)           S5P4418_DEFINE_FIELD(x, CLKDIV_MPCLK)

#define S5P4418_CLKSET_GR3DBCLK(x)        S5P4418_DEFINE_FIELD(x, CLKSET_GR3DBCLK)
#define S5P4418_CLKDIV_GR3DBCLK(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_GR3DBCLK)
#define S5P4418_CLKDIV_GR3DPCLK(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_GR3DPCLK)

#define S5P4418_CLKSET_MPEGBCLK(x)        S5P4418_DEFINE_FIELD(x, CLKSET_MPEGBCLK)
#define S5P4418_CLKDIV_MPEGBCLK(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_MPEGBCLK)
#define S5P4418_CLKDIV_MPEGPCLK(x)        S5P4418_DEFINE_FIELD(x, CLKDIV_MPEGPCLK)

typedef struct s5p4418_ip_reset {
  u32     ip_reset[3];
} s5p4418_ip_reset_t;

#define S5P4418_IP_RESET_MIPITOP_I_PHY_S_RESETN         (1 << 31)
#define S5P4418_IP_RESET_MIPITOP_I_CSI_I_PRESETN        (1 << 30)
#define S5P4418_IP_RESET_MIPITOP_I_DSI_I_PRESETN        (1 << 29)
#define S5P4418_IP_RESET_MIPITOP_I_nRST                 (1 << 28)
#define S5P4418_IP_RESET_MCUYZTOP_NPRST                 (1 << 27)
#define S5P4418_IP_RESET_MCUYZTOP_ARESETN               (1 << 26)
#define S5P4418_IP_RESET_MCUYZTOP_CRESETN               (1 << 25)
#define S5P4418_IP_RESET_I2S2_PRESETN                   (1 << 24)
#define S5P4418_IP_RESET_I2S1_PRESETN                   (1 << 23)
#define S5P4418_IP_RESET_I2S0_PRESETN                   (1 << 22)
#define S5P4418_IP_RESET_I2C2_PRESETN                   (1 << 21)
#define S5P4418_IP_RESET_I2C1_PRESETN                   (1 << 20)
#define S5P4418_IP_RESET_I2C0_PRESETN                   (1 << 19)
#define S5P4418_IP_RESET_DISPLAYTOP_I_LVDS_NRST         (1 << 18)
#define S5P4418_IP_RESET_DISPLAYTOP_I_HDMI_PHY_NRST     (1 << 17)
#define S5P4418_IP_RESET_DISPLAYTOP_I_HDMI_TMDS_NRST    (1 << 16)
#define S5P4418_IP_RESET_DISPLAYTOP_I_HDMI_SPDIF_NRST   (1 << 15)
#define S5P4418_IP_RESET_DISPLAYTOP_I_HDMI_VIDEO_NRST   (1 << 14)
#define S5P4418_IP_RESET_DISPLAYTOP_I_HDMI_NRST         (1 << 13)
// bit 12 should be always 1
// bit 11 should be always 1
#define S5P4418_IP_RESET_DISPLAYTOP_I_DUALDISPLAY_NRST  (1 << 10)
#define S5P4418_IP_RESET_DISPLAYTOP_I_TOP_NRST          (1 << 9)
#define S5P4418_IP_RESET_DEINTERLACE_I_NRST             (1 << 8)
#define S5P4418_IP_RESET_CRYPTO_I_NRST                  (1 << 7)
#define S5P4418_IP_RESET_ARMTOP_NWDRESET3               (1 << 6)
#define S5P4418_IP_RESET_ARMTOP_NWDRESET2               (1 << 5)
#define S5P4418_IP_RESET_ARMTOP_NWDRESET1               (1 << 4)
#define S5P4418_IP_RESET_ARMTOP_NCPURESET3              (1 << 3)
#define S5P4418_IP_RESET_ARMTOP_NCPURESET2              (1 << 2)
#define S5P4418_IP_RESET_ARMTOP_NCPURESET1              (1 << 1)
#define S5P4418_IP_RESET_AC970_PRESETN                  (1 << 0)

#define S5P4418_IP_RESET_GMAC0_ARESETN_I                (1 << 31)
#define S5P4418_IP_RESET_CODA960_I_CRESET_N             (1 << 30)
#define S5P4418_IP_RESET_CODA960_I_PRESET_N             (1 << 29)
#define S5P4418_IP_RESET_CODA960_I_ARESET_N             (1 << 28)
#define S5P4418_IP_RESET_ADC_NRST                       (1 << 27)
#define S5P4418_IP_RESET_WDT00_NPOR                     (1 << 26)
#define S5P4418_IP_RESET_WDT00_PRESETN                  (1 << 25)
#define S5P4418_IP_RESET_USB20OTG0_I_NRST               (1 << 24)
#define S5P4418_IP_RESET_USB20HOST0_I_NRST              (1 << 23)
#define S5P4418_IP_RESET_UART04_NUARTRST                (1 << 21)
#define S5P4418_IP_RESET_UART03_NUARTRST                (1 << 20)
#define S5P4418_IP_RESET_UART02_NUARTRST                (1 << 19)
#define S5P4418_IP_RESET_UART01_NUARTRST                (1 << 18)
#define S5P4418_IP_RESET_UART00_NUARTRST                (1 << 17)
#define S5P4418_IP_RESET_SSP2_NSSPRST                   (1 << 16)
#define S5P4418_IP_RESET_SSP2_PRESETN                   (1 << 15)
#define S5P4418_IP_RESET_SSP1_NSSPRST                   (1 << 14)
#define S5P4418_IP_RESET_SSP1_PRESETN                   (1 << 13)
#define S5P4418_IP_RESET_SSP0_NSSPRST                   (1 << 12)
#define S5P4418_IP_RESET_SSP0_PRESETN                   (1 << 11)
#define S5P4418_IP_RESET_SPDIFTX00_PRESETN              (1 << 10)
#define S5P4418_IP_RESET_SPDIFRX00_PRESETN              (1 << 9)
#define S5P4418_IP_RESET_SDMMC2_I_NRST                  (1 << 8)
#define S5P4418_IP_RESET_SDMMC1_I_NRST                  (1 << 7)
#define S5P4418_IP_RESET_SDMMC0_I_NRST                  (1 << 6)
#define S5P4418_IP_RESET_SCALER_I_NRST                  (1 << 5)
#define S5P4418_IP_RESET_PWMTIMER1_PRESETN              (1 << 4)
#define S5P4418_IP_RESET_PWMTIMER0_PRESETN              (1 << 3)
#define S5P4418_IP_RESET_PDM_I_NRST                     (1 << 2)
#define S5P4418_IP_RESET_MPEGTSI00_I_NRST               (1 << 1)
#define S5P4418_IP_RESET_MIPITOP_I_PHY_M_RESETN         (1 << 0)

#define S5P4418_IP_RESET_VIP001_I_NRST                  (1 << 3)
#define S5P4418_IP_RESET_VIP000_I_NRST                  (1 << 2)
#define S5P4418_IP_RESET_PPM_I_NRST                     (1 << 1)
#define S5P4418_IP_RESET_3D_GPU_NRST                    (1 << 0)

static inline void
s5p4418_ip_reset(u8 ndx, u32 bits)
{
  s5p4418_ip_reset_t* reg = (s5p4418_ip_reset_t*)S5P4418_BASE_IP_RESET;
  u32 tmp;
  u32* ptr;

  ptr = &(reg->ip_reset[ndx]);

  tmp = readl(ptr);

  // set reset 
  tmp &= ~bits;
  writel(tmp, ptr);

  // clear reset
  tmp |= bits;
  writel(tmp, ptr);
}

static inline void
s5p4418_update_pll(s5p4418_syscon_t* reg, u8 pll_num)
{
  writel(S5P4418_UPDATE_PLL(pll_num), &reg->clkmodereg0);

  while(readl(&reg->clkmodereg0) & S5P4418_WAIT_UPDATE_PLL)
    ;
}

#endif /* !_S5P4418_SYSCON_H */
