#ifndef _S5P4418_COMMON_H
#define _S5P4418_COMMON_H

#define S5P4418_DEFINE_FIELD(x, name)       ((x & S5P4418_ ## name ## _MASK) << S5P4418_ ## name ## _OFF)

//
//
// S5P4418 u-boot core code expects board to supply the following common functions
//
extern void s5p4418_board_pll_clk_init(void);
extern void s5p4418_board_memory_init(void);

#endif /* !_S5P4418_COMMON_H */
