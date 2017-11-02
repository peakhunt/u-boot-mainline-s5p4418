#ifndef _S5P4418_GPIO_H
#define _S5P4418_GPIO_H

#include <asm/types.h>

typedef struct s5p4418_gpio {
  u32   out;
  u32   out_enb;
  u32   detmode0;
  u32   detmode1;
  u32   intenb;
  u32   det;
  u32   pad;
  u32   reserved;
  u32   altfn0;
  u32   altfn1;
  u32   detmodex;
  u32   det_enb;
  u32   slew;
  u32   slew_disable_def;
  u32   drv1;
  u32   drv1_disable_def;
  u32   drv0;
  u32   drv0_disable_def;
  u32   pullsel;
  u32   pullsel_disable_def;
  u32   pull_enb;
  u32   pull_enb_disable_def;
} s5p4418_gpio_t;

// GPIOxOUT

// GPIOxOUTENB

// GPIOxALTFN0/1
#define S5P4418_GPIO_ALTFN_OFF(n)     (2 * ((n < 16) ? n : (n-16)))
#define S5P4418_GPIO_ALTFN_MASK       0x03
#define S5P4418_GPIO_ALTFN(n, v)      ((v & 0x3) << S5P4418_GPIO_ALTFN_OFF(n))


static inline void
s5p4418_gpio_set_altfn(s5p4418_gpio_t* reg, u8 pin, u8 fn)
{
  u32   tmp;
  u32*  ptr;

  if(pin < 16)
  {
    ptr = &reg->altfn0;
  }
  else
  {
    ptr = &reg->altfn1;
  }

  tmp =   readl(ptr);
  tmp &= ~(S5P4418_GPIO_ALTFN_MASK << S5P4418_GPIO_ALTFN_OFF(pin));
  tmp |=  S5P4418_GPIO_ALTFN(pin, fn);

  writel(tmp, ptr);
}

static inline void
s5p4418_gpio_set_io_mode(s5p4418_gpio_t* reg, u8 pin, u8 is_out)
{
  u32   tmp;

  tmp = readl(&reg->out_enb);

  if(is_out)
  {
    tmp |= (1 << pin);
  }
  else
  {
    tmp &= ~(1 << pin);
  }

  writel(tmp, &reg->out_enb);
}

static inline void
s5p4418_gpio_set_output(s5p4418_gpio_t* reg, u8 pin, u8 high)
{
  u32   tmp;

  tmp = readl(&reg->out);

  if(high)
  {
    tmp |= (1 << pin);
  }
  else
  {
    tmp &= ~(1 << pin);
  }

  writel(tmp, &reg->out);
}

#endif /* !_S5P4418_GPIO_H */
