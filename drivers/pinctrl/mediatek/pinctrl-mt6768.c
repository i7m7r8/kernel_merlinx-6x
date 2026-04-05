// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek MT6768/MT6769 Pin Controller Driver (minimal stub)
 * Based on: pinctrl-mt6765.c (mainline 6.12)
 * Adapted for Linux 6.12
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

#include "pinctrl-paris.h"
#include "pinctrl-mtk-common-v2.h"

/* MT6768 pin definitions - minimal set for initial boot
 * Bug 1 fix: correct includes, Bug 5 fix: key pins defined
 */
static const struct mtk_pin_desc mt6768_pins[] = {
	MTK_PIN(0, "GPIO0",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
	),
	MTK_PIN(63, "UART0_TXD",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "UART0_TXD"),
	),
	MTK_PIN(64, "UART0_RXD",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "UART0_RXD"),
	),
	MTK_PIN(65, "MSDC0_CLK",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_CLK"),
	),
	MTK_PIN(66, "MSDC0_CMD",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_CMD"),
	),
	MTK_PIN(67, "MSDC0_D0",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_D0"),
	),
	MTK_PIN(68, "MSDC0_D1",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_D1"),
	),
	MTK_PIN(69, "MSDC0_D2",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_D2"),
	),
	MTK_PIN(70, "MSDC0_D3",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		MTK_PUPD_MASK_R1R0(0x80, 0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "MSDC0_D3"),
	),
};

static const struct mtk_pin_soc mt6768_data = {
	.pins = mt6768_pins,
	.npins = ARRAY_SIZE(mt6768_pins),
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.ies_get = mtk_pinconf_ies_get,
	.ies_set = mtk_pinconf_ies_set,
};

static const struct of_device_id mt6768_pinctrl_of_match[] = {
	{ .compatible = "mediatek,mt6768-pinctrl", .data = &mt6768_data },
	{ }
};
MODULE_DEVICE_TABLE(of, mt6768_pinctrl_of_match);

static struct platform_driver mt6768_pinctrl_driver = {
	.driver = {
		.name = "mt6768-pinctrl",
		.of_match_table = mt6768_pinctrl_of_match,
	},
	.probe = mtk_paris_pinctrl_probe,
};

static int __init mt6768_pinctrl_init(void)
{
	return platform_driver_register(&mt6768_pinctrl_driver);
}
arch_initcall(mt6768_pinctrl_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek MT6768 Pinctrl Driver");
