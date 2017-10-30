/*
   totoally undocumented!
*/

	.word 0xffff0200      /* dummy sram vector */
  .word 0xffff0204
  .word 0xffff0208
  .word 0xffff020C
  .word 0xffff0210
  .word 0xffff0214
  .word 0xffff0218
  .word 0xffff021C

  .word 0x00000800    /* header whatever: device read address */
  .word 0x00040000    /* header whatever: load size */
  .word 0xffff0000    /* header whatever: load address */
  .word 0xffff0000    /* header whatever: launch address */
  .word 0x00000000    /* header whatever: boot from usb */
  .word 0x03000000    /* header whatever: boot from usb */
  .word 0x00000000    /* header whatever: boot from usb */

  .word 0x10199001    /* pll0 : 800 Mhz */
  .word 0x10119001    /* pll0 : 1200 Mhz */
  .word 0x100D1302    /* pll0 : 550 Mhz */
  .word 0x100CFA02    /* pll0 : 500 Mhz */
  .word 0x00000104    /* pll2 : spread */
  .word 0x00000104    /* pll3 : spread */
  .word 0x00000A01    /* cpu0 : PLL1  /FCLK:1200  /HCLK:200 */
  .word 0x0000020B    /* bus  : PLL3  /BCLK:250 /PCLK:125 */
  .word 0x00208000    /* MEM    PLL0  /MDCLK:800  /MCLK:800 /MBCLK:400  /MPCLK:200 */
  .word 0x00000203    /* GR3D   PLL3  /GR3DBCLK:500 */
  .word 0x0000020B    /* 0x084 : MPEG   PLL3  /MPEGBCLK:250 /MPEGPCLK:125 */

  .word 0x00000301    /* /Chip Num:1 /Chip Row:15  /Bus Width:16 */
  .word 0x004007C0
  .word 0x1C0B0803    /* 0x090  /CWL:8  /WL:8 /RL,CL:11 */
  .word 0x0C0C0C0C
  .word 0x02020202
  .word 0x00000618    /* /Refresh Interval:7.8us */
  .word 0x6846650F    /* /tRFC:104nCK  /tRRD:4nCK  /tRP:6nCK /tRCD:6nCK  /tRC:20nCK  /tRAS:15nCK */
  .word 0x4641880B    /*  0x0A4  /tWTR:4nCK  /tWR:6nCK /tRTP:4nCK */
  .word 0x32000334    /* /tFAW:12nCK /tXSR:512nCK  /tXP:3nCK /tCKE:3nCK */

  .skip 336
  /* .word 0x44180600 */
  .word 0x4849534e
