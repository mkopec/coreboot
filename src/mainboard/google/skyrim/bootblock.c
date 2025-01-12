/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <baseboard/variants.h>

void bootblock_mainboard_early_init(void)
{
	size_t num_gpios, override_num_gpios;
	const struct soc_amd_gpio *gpios, *override_gpios;

	variant_tpm_gpio_table(&gpios, &num_gpios);
	gpio_configure_pads(gpios, num_gpios);

	variant_early_gpio_table(&gpios, &num_gpios);
	variant_early_override_gpio_table(&override_gpios, &override_num_gpios);
	gpio_configure_pads_with_override(gpios, num_gpios, override_gpios, override_num_gpios);
}

void bootblock_mainboard_init(void)
{
	size_t num_gpios;
	const struct soc_amd_gpio *gpios;

	variant_bootblock_gpio_table(&gpios, &num_gpios);
	gpio_configure_pads(gpios, num_gpios);
}
