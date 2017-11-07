#include <common.h>
#include <asm/io.h>
#include <spl.h>
#include <debug_uart.h>

/* Direct Command */
#define DIRECT_CMD_NOP      0x07000000
#define DIRECT_CMD_PALL     0x01000000
#define DIRECT_CMD_ZQINIT   0x0a000000

#define DIRECT_CMD1 0x00020018
#define DIRECT_CMD2 0x00030000
#define DIRECT_CMD3 0x00010040        //  rzq/4, rzq/6
#define DIRECT_CMD4 0x00001578

extern void sdelay(unsigned long);

static void
s5p4418_mrs_command(void)
{
  /* Issue a NOP command using the DirectCmd register to assert and to hold CKE to
     a logic high level. */
  writel(DIRECT_CMD_NOP, 0xc00e0010);

  /* Wait for Txpr (Max. (5nCK,tRFC(min)+10ns)) or
     set tXP to tXPR value before step 17.
     If the system set tXP to tXPR, then the system must set tXP to proper
     value before normal memory operation.
  */
  sdelay(0x10000);

  /* Issue an MR2 command using the DirectCmd register to
     program the operating parameters. Dynamic ODT should be
     disabled. A10 and A9 should be low.
  */
  //
  // DIRECT_CMD1 :
  // MR2
  // 0x18     : 0000 0000 0001 1000
  // A2-A0    : full array refresh
  // A3-A5    : 011 : CWL=8
  // A6       : 0     Manual SR reference
  // A7       : 0     Normal operating temperature
  // A9-A10   : 00    Dynamic ODF off
  //
  writel(DIRECT_CMD1, 0xc00e0010);
  sdelay(0x10000);

  // MR3
  // A2 : 0 normal operation
  // A1-0 : 0 predefined pattern
  writel(DIRECT_CMD2, 0xc00e0010);
  sdelay(0x10000);

  // MR1
  // 0040         : 0000 0000 0100 0000
  // A0           : 0 DLL Enable
  // A9 A6 A2     : 0 1 0     RZQ/2   = 120 Ohm
  // A5 A1        : 0 0       RZQ/6   = 40 Ohm
  // A7           : 0         Write leveling disabled
  // A4 A3        : 0 0       Additive Latency disabled
  // A11          : 0         TDQS disabled
  // A12          : 1         Output Buffer disabled
  writel(DIRECT_CMD3, 0xc00e0010);
  sdelay(0x10000);

  // MR0
  // 1578       : 0001 0101 0111 1000
  // A1-A0      : 00    BL-8
  // A3         : 1    Interleave
  // A6 A5 A4 A2: 1110    CAS-11
  // A7         : 0       Normal mode
  // A8         : 1       DLL Reset Yes
  // A11 A10 A9 : 010     write recovery 6
  // A12        : 1       Slow Exit (DLL off)
  //
  writel(DIRECT_CMD4, 0xc00e0010);
  sdelay(0x10000);

  /* Issues a ZQINIT commands using the DirectCmd register. */
  writel(DIRECT_CMD_ZQINIT, 0xc00e0010);
  sdelay(10000);
}
  
static void
s5p4418_config_zq(void)
{
  u32 val, i;

  debug("zq : %x\n", readl(0xc00e1048));

  // set driver strength for CK, CKE, CS & CA to 0x7
  // set driver strength for data slice 0~3 to 0x07
  // PHY_CON39
  writel(0x00 << 25           |       // slice 3
         0x00 << 22           |       // slice 2
         0x00 << 19           |       // slice 2
         0x00 << 16           |       // slice 0
         0x00 << 9            |       // ck
         0x00 << 6            |       // cke
         0x00 << 3            |       // cs
         0x00 << 0                    // adct ???
         , 0xc00e10a0);

  // PHY_CON16
  val =   0x08000304;     // reset value
  val |=  (0x5 << 24);    // ohm impedance output driver -> 40 Ohm
  val |=  (0x1 << 21);    // ohm receiver termination -> 120 ohm
  val |=  (1 << 18);       // clock dividing enable
  val &=  ~(1 << 19);      // termination enabled
  writel(val, 0xc00e1040);

  // zq clock divider setting value
  //writel(0x0000ffff, 0xc00e10a4);

  // ZQ_MANUAL_START enable
  val |= (1 << 1);        // zq_manual_str enable
  writel(val, 0xc00e1040);


  // waitl until calibration complete
  i = 0x5000;
  while((readl(0xc00e1048) & 0x1) != 0x1 && i > 0)
  {
    sdelay(100);
    i--;
  }

  if(i == 0)
  {
    debug("zq calibration failed\n");
  }
  else
  {
    debug("zq : %x\n", readl(0xc00e1048));
  }

  // clear ZQ_MANUAL_START
  val &= ~(1 << 1);
  writel(val, 0xc00e1040);

  // disable ZQ_CLK_DIV_EN
  // PHY_CON16
  val = readl(0xc00e1040);
  val &= ~(1 << 18);
  writel(val, 0xc00e1040);
}


static void
s5p4418_update_reset_dll(void)
{
  u32 val;

  // ddr3
  val = (1 << 31)     |     // mem_term_en
        (1 << 30)     |     // phy_term_en
        (0 << 29);          // ctrl_shgate
  writel(val, 0xc00e0018);

  // update dll
  val = readl(0xc00e0018);
  val |= (1 << 3);          // fp_resync
  writel(val, 0xc00e0018);

  val = readl(0xc00e0018);
  val &= ~(1 << 3);
  writel(val, 0xc00e0018);
}

void
s5p4418_phy_init(void)
{
  u32 val;

  //specify the DDR mmeory type as DDR3 */
  // PHY_CON0
  val  = readl(0xc00e1000);
  val &= ~(0x3 << 11);
  val |=  (0x1 << 11);           // DDR3
  writel(val, 0xc00e1000);

  // set read latency and burst length for phy0 */
  // PHY_CON42
  val =   (11   << 0 |        // rl=11
           8    << 8);        // bl
  writel(val, 0xc00e10ac);

  // PHY_CON26
  val = readl(0xc00e106c);
  val &= ~(0x1f << 16);       // T_wrdata_en
  val |=  (8 << 16);          // wl=8
  writel(val, 0xc00e106c);

  s5p4418_config_zq();

  debug("zq calbration done\n");

  // PHY_CON14
  val = readl(0xc00e1038);
  val |= (0x0 << 8    |           // dq
          0xf << 0);              // dqs
  writel(val, 0xc00e1038);
}

void
mem_init(void)
{
  u32 val;

  debug("initializing ddr3\n");

  s5p4418_phy_init();

  sdelay(10000);
  
  // memory termination enable
  // phycontrol0
  val = (1 << 31)       |       // mem_term_en
        (1 << 30);              // phy_term_en
  writel(val, 0xc00e0018);

  // dfi_init_start
  // concontrol
  writel(   (1 << 28)     |       // dfi_init_start
            (0xfff << 16) |       // timeout_level0
            (1 << 12)     |       // rd_fetch
            (0 << 5),             // aref_en 
            0xc00e0000);
  do
  {
    val = readl(0xc00e0040);
  } while((val & ( 1 << 3)) == 0);

  // clear dfi_init_start
  val = readl(0xc00e0000);
  val &= ~(1 << 28);
  writel(val, 0xc00e0000);

  s5p4418_update_reset_dll();

  // memcontrol
  writel((0x00 << 25)           |   // memory dq[7:0]
         (0x03 << 20)           |   // bl 8
         (0x00 << 16)           |   // 1 chip
         (0x02 << 12)           |   // 32-bit
         (0x06 << 8)                // DDR3
         , 0xc00e0004);

  // membaseconfig0 : 0x000007c0, XXX: control variable point : membaseconfig0
  //
  // base [34-24] : 000 0000 0000 ( 40000000 -> translated to 0
  // mask 7c0       111 1100 0000   -> 1GB range
  //
  writel(0x000007c0, 0xc00e010c);

  // memcofig0 : 0x0001333   XXX: control variable point : memconfig0
  // chip_map     : interleaved
  // chip_col     : 10 bit
  // chip_row     : 15 bit
  // chip_bank    : 8 banks
  writel(0x0001333, 0xc00e0008);

  // PrechConfig : 0xff000000     XXX: control variable point : prechconfig
  // PwrdnConfig : 0xffff00ff     XXX: control variable point : pwrdnconfig
  writel(0xff000000, 0xc00e0014);
  writel(0xffff00ff, 0xc00e0028);

  // TimingAref : 0x00000618      XXX: control variable point : timingaref
  // TimingRow  : 0x6836650e      XXX: control variable point : timingrow
  // TimingData : 0x3631880b      XXX: control variable point : timingdata
  // TimingPower: 0x41000a26      XXX: control variable point : timingpower

  //
  // tREFI 7.8us
  // MPCLK: 200 Mhz
  // 7.8 * 200 = 1560
  writel(0x618,       0xc00e0030); 
  //    t_rfc       : 01101000      0x28
  //    t_rrd       : 0011          0x3
  //    t_rp        : 0110          0x06
  //    t_rcd       : 0110          0x06
  //    t_rc        : 010100        0x14
  //    t_ras       : 001110        0xe
  writel(0x6836650e,  0xc00e0034);
  // DDR3-1600 = 800 Mhz x 16 bit / 8
  //
  // rl 11
  // wl 8
  //
  // t_wtr      : 0011
  // t_wr       : 0110      -> 6
  // t_rtp      : 0011
  // t_w2w_c2c  : 1
  // t_r2r_c2c  : 1
  // dqsck      : 000
  // wl         : 1000      -> 8
  // rl         : 1011      -> 11
  //
  writel(0x3631880b,  0xc00e0038);
  // t_faw      : 010000
  // t_xsr      : 0100000000
  // t_xp       : 00001010
  // t_cke      : 0010
  // t_mrd      : 0110
  writel(0x41000a26,  0xc00e003c);

  // FIXME gate levling

  s5p4418_mrs_command();

  s5p4418_update_reset_dll();

  /* Set the ConControl to turn on an auto refresh counter. */
  val = readl(0xc00e0000);
  val |= (1 << 5);
  writel(val, 0xc00e0000);
}
