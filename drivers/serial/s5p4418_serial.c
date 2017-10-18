#include <common.h>
#include <dm.h>
#include <errno.h>
#include <serial.h>
#include <linux/compiler.h>

#include <asm/io.h>

#ifndef CONFIG_DM_SERIAL
static void s5p4418_serial_setbrg(void)
{
}

static int s5p4418_serial_init(void)
{
	return 0;
}

static void s5p4418_serial_putc(char c)
{
}

static int s5p4418_serial_getc(void)
{
  //
  // blocking function
  //
  return 0;
}

static int s5p4418_serial_tstc(void)
{
  return 9;
}

static struct serial_device s5p4418_serial_drv = {
	.name	= "s5p4418_serial",
	.start	= s5p4418_serial_init,
	.stop	= NULL,
	.setbrg	= s5p4418_serial_setbrg,
	.putc	= s5p4418_serial_putc,
	.puts	= default_serial_puts,
	.getc	= s5p4418_serial_getc,
	.tstc	= s5p4418_serial_tstc,
};

void s5p4418_serial_initialize(void)
{
	serial_register(&s5p4418_serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &s5p4418_serial_drv;
}
#endif

#ifdef CONFIG_DM_SERIAL
int s5p4418_serial_setbrg(struct udevice *dev, int baudrate)
{
	return 0;
}

static int s5p4418_serial_getc(struct udevice *dev)
{
  return 0;
}

static int s5p4418_serial_putc(struct udevice *dev, const char ch)
{
	return 0;
}

static int s5p4418_serial_pending(struct udevice *dev, bool input)
{
  return 0;
}

static const struct dm_serial_ops s5p4418_serial_ops = {
	.putc = s5p4418_serial_putc,
	.pending = s5p4418_serial_pending,
	.getc = s5p4418_serial_getc,
	.setbrg = s5p4418_serial_setbrg,
};

static int s5p4418_serial_probe(struct udevice *dev)
{
	return 0;
}

U_BOOT_DRIVER(serial_s5p4418) = {
	.name	= "serial_s5p4418",
	.id	= UCLASS_SERIAL,
	.probe = s5p4418_serial_probe,
	.ops	= &s5p4418_serial_ops,
	.flags = DM_FLAG_PRE_RELOC,
	.priv_auto_alloc_size	= 0,
};
#endif
