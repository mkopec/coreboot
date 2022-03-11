/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8625e/it8625e.h>
#include <soc/gpio.h>
#include "include/gpio.h"

#define GPIO_DEV PNP_DEV(0x2e, IT8625E_GPIO)
#define UART_DEV PNP_DEV(0x2e, IT8625E_SP1)

static void early_config_gpio(void)
{
	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));
}

void bootblock_mainboard_init(void)
{
	early_config_gpio();
}

void bootblock_mainboard_early_init(void)
{
    ite_conf_clkin(GPIO_DEV, ITE_UART_CLK_PREDIVIDE_24);
    ite_enable_3vsbsw(GPIO_DEV);
    ite_kill_watchdog(GPIO_DEV);
    ite_enable_serial(UART_DEV, CONFIG_TTYS0_BASE);
}