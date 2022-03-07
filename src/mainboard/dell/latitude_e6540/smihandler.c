/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/io.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <ec/acpi/ec.h>
#include <southbridge/intel/lynxpoint/pch.h>

#define GPE_EC_SCI	0x10

/* lynxpoint doesn't have gpi_route_interrupt, so add it */
#define GPI_DISABLE 0x00
#define GPI_IS_SMI 0x01
#define GPI_IS_SCI 0x02
#define GPI_IS_NMI 0x03

static void gpi_route_interrupt(u8 gpi, u8 mode)
{
	u32 gpi_rout;

	gpi_rout = pci_read_config32(PCI_DEV(0, 0x1f, 0), GPIO_ROUT);
	gpi_rout &= ~(3 << (2 * gpi));
	gpi_rout |= ((mode & 3) << (2 * gpi));
	pci_write_config32(PCI_DEV(0, 0x1f, 0), GPIO_ROUT, gpi_rout);
}

int mainboard_smi_apmc(u8 data)
{
	switch (data) {
	case APM_CNT_ACPI_ENABLE:
		/* use 0x1600/0x1604 to prevent races with userspace */
		ec_set_ports(0x934, 0x930);
		/* route EC_SCI to SCI */
		gpi_route_interrupt(GPE_EC_SCI, GPI_IS_SCI);
		/* discard all events, and enable attention */
		ec_write(0x80, 0x01);
		break;
	case APM_CNT_ACPI_DISABLE:
		/* we have to use port 0x62/0x66, as 0x1600/0x1604 doesn't
		   provide a EC query function */
		ec_set_ports(0x66, 0x62);
		/* route EC_SCI to SMI */
		gpi_route_interrupt(GPE_EC_SCI, GPI_IS_SMI);
		/* discard all events, and enable attention */
		ec_write(0x80, 0x01);
		break;
	default:
		break;
	}
	return 0;
}
