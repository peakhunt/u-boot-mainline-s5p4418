#ifndef _S5P4418_DMC_H
#define _S5P4418_DMC_H

#include <asm/types.h>
#include <asm/arch/s5p4418_common.h>

typedef struct s5p4418_drex {
  u32   concontrol;
  u32   memcontrol;
  u32   memconfig0;
  u32   memconfig1;
  u32   directcmd;
  u32   prechconfig;
  u32   phycontrol0;
  u32   reserved0[3];
  u32   pwrdnconfig;
  u32   timingpzq;
  u32   timingref;
  u32   timingrow;
  u32   timingdata;
  u32   timingpower;
  u32   phystatus;
  u32   reserved1;
  u32   chipstatus;
  u32   reserved2[2];
  u32   mrstatus;
  u32   reserved3[2];
	u32   qoscontrol0;
	u32   qosconfig0;
	u32   qoscontrol1;
	u32   qosconfig1;
	u32   qoscontrol2;
	u32   qosconfig2;
	u32   qoscontrol3;
	u32   qosconfig3;
	u32   qoscontrol4;
	u32   qosconfig4;
	u32   qoscontrol5;
	u32   qosconfig5;
	u32   qoscontrol6;
	u32   qosconfig6;
	u32   qoscontrol7;
	u32   qosconfig7;
	u32   qoscontrol8;
	u32   qosconfig8;
	u32   qoscontrol9;
	u32   qosconfig9;
	u32   qoscontrol10;
	u32   qosconfig10;
	u32   qoscontrol11;
	u32   qosconfig11;
	u32   qoscontrol12;
	u32   qosconfig12;
	u32   qoscontrol13;
	u32   qosconfig13;
	u32   qoscontrol14;
	u32   qosconfig14;
	u32   qoscontrol15;
	u32   qosconfig15;
	u32   qostimeout0;
	u32   qostimeout1;
  u32   reserved4[6];
  u32   wrtraconfig;
  u32   rdlvlconfig;
  u32   reserved5;
  u32   brbrsvcontrol;
  u32   brbrsvconfig;
  u32   brbqosconfig;
  u32   membaseconfig0;
  u32   membaseconfig1;
  u32   reserved6[3];
  u32   wrlvlconfig0;
  u32   wrlvlconfig1;
  u32   wrlvlstatus;
  u32   reserved7[6];
  u32   ctrl_io_rdata;
  u32   reserved8[3];
  u32   cacal_config0;
  u32   cacal_config1;
  u32   cacal_status;
} s5p4418_drex_t;


enum ddr_mode {
  DDR_MODE_DDR2,
	DDR_MODE_DDR3,
	DDR_MODE_LPDDR2,
	DDR_MODE_LPDDR3,

	DDR_MODE_COUNT,
};

/* CONCONTROL register fields */
#define CONCONTROL_DFI_INIT_START_SHIFT	28
#define CONCONTROL_RD_FETCH_SHIFT	12
#define CONCONTROL_RD_FETCH_MASK	(0x7 << CONCONTROL_RD_FETCH_SHIFT)
#define CONCONTROL_AREF_EN_SHIFT	5
#define CONCONTROL_UPDATE_MODE		(1 << 3)

/* PRECHCONFIG register field */
#define PRECHCONFIG_TP_CNT_SHIFT	24

/* PWRDNCONFIG register field */
#define PWRDNCONFIG_DPWRDN_CYC_SHIFT	0
#define PWRDNCONFIG_DSREF_CYC_SHIFT	16

/* PHY_CON0 register fields */
#define PHY_CON0_T_WRRDCMD_SHIFT	17
#define PHY_CON0_T_WRRDCMD_MASK		(0x7 << PHY_CON0_T_WRRDCMD_SHIFT)
#define PHY_CON0_CTRL_DDR_MODE_SHIFT	11
#define PHY_CON0_CTRL_DDR_MODE_MASK	0x3

/* PHY_CON1 register fields */
#define PHY_CON1_RDLVL_RDDATA_ADJ_SHIFT	0

/* PHY_CON4 rgister fields */
#define PHY_CON10_CTRL_OFFSETR3		(1 << 24)

/* PHY_CON12 register fields */
#define PHY_CON12_CTRL_START_POINT_SHIFT	24
#define PHY_CON12_CTRL_INC_SHIFT	16
#define PHY_CON12_CTRL_FORCE_SHIFT	8
#define PHY_CON12_CTRL_START_SHIFT	6
#define PHY_CON12_CTRL_START_MASK	(1 << PHY_CON12_CTRL_START_SHIFT)
#define PHY_CON12_CTRL_DLL_ON_SHIFT	5
#define PHY_CON12_CTRL_DLL_ON_MASK	(1 << PHY_CON12_CTRL_DLL_ON_SHIFT)
#define PHY_CON12_CTRL_REF_SHIFT	1

/* PHY_CON16 register fields */
#define PHY_CON16_ZQ_MODE_DDS_SHIFT	24
#define PHY_CON16_ZQ_MODE_DDS_MASK	(0x7 << PHY_CON16_ZQ_MODE_DDS_SHIFT)

#define PHY_CON16_ZQ_MODE_TERM_SHIFT 21
#define PHY_CON16_ZQ_MODE_TERM_MASK	(0x7 << PHY_CON16_ZQ_MODE_TERM_SHIFT)

#define PHY_CON16_ZQ_MODE_NOTERM_MASK	(1 << 19)

/* PHY_CON42 register fields */
#define PHY_CON42_CTRL_BSTLEN_SHIFT	8
#define PHY_CON42_CTRL_BSTLEN_MASK	(0xff << PHY_CON42_CTRL_BSTLEN_SHIFT)

#define PHY_CON42_CTRL_RDLAT_SHIFT	0
#define PHY_CON42_CTRL_RDLAT_MASK	(0x1f << PHY_CON42_CTRL_RDLAT_SHIFT)

#endif /* !_S5P4418_DMC_H */
