/*
 * Copyright (C) FIXME
 * Copyright (C) 2007 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef DEVICE_PNP_H
#define DEVICE_PNP_H

#include <arch/types.h>
#include <device/device.h>
#include <device/pnp_def.h>

/* Primitive pnp resource manipulation */
void    pnp_write_config(struct device * dev, u8 reg, u8 value);
u8 pnp_read_config(struct device * dev, u8 reg);
void    pnp_set_logical_device(struct device * dev);
void    pnp_set_enable(struct device * dev, int enable);
int     pnp_read_enable(struct device * dev);
void    pnp_set_iobase(struct device * dev, unsigned index, unsigned iobase);
void    pnp_set_irq(struct device * dev, unsigned index, unsigned irq);
void    pnp_set_drq(struct device * dev, unsigned index, unsigned drq);

/* PNP device operations */
void pnp_read_resources(struct device * dev);
void pnp_set_resources(struct device * dev);
void pnp_enable_resources(struct device * dev);
void pnp_enable(struct device * dev);

extern struct device_operations pnp_ops;

/* PNP helper operations */

struct io_info {
	unsigned mask, set;
};

struct pnp_info {
	struct device_operations *ops;
	unsigned function;
	unsigned flags;
#define PNP_IO0  0x01
#define PNP_IO1  0x02
#define PNP_IO2  0x04
#define PNP_IO3  0x08
#define PNP_IRQ0 0x10
#define PNP_IRQ1 0x20
#define PNP_DRQ0 0x40
#define PNP_DRQ1 0x80
	struct io_info io0, io1, io2, io3;
};
struct resource *pnp_get_resource(struct device * dev, unsigned index);
void pnp_enable_devices(struct device *dev, struct device_operations *ops,
	unsigned functions, struct pnp_info *info);

#endif /* DEVICE_PNP_H */
