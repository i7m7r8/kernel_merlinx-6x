// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek MT6768/MT6769 Pin Controller Driver (minimal stub)
 * Based on: pinctrl-mt6765.c (mainline) + vendor 4.14
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/pinctrl/mtk-mtk.h>
#include <linux/regmap.h>

static const struct mtk_pin_desc mt6768_pins[] = {
	MTK_PIN(0, "GPIO0",
		MTK_EINT_FUNCTION(NO_EINT_SUPPORT, NO_EINT_SUPPORT),
		DRIVING_DEFAULT(0x4),
		MTK_FUNCTION(0, "GPIO"),
	),
	MTK_PIN(63, "UART0_TXD",
		DRIVING_DEFAULT(0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "UART0_TXD"),
	),
	MTK_PIN(64, "UART0_RXD",
		DRIVING_DEFAULT(0x4),
		MTK_FUNCTION(0, "GPIO"),
		MTK_FUNCTION(1, "UART0_RXD"),
	),
};

static const struct mtk_pin_soc mt6768_data = {
	.pins = mt6768_pins,
	.npins = ARRAY_SIZE(mt6768_pins),
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.ies_get = mtk_pinconf_ies_get,
	.ies_set = mtk_pinconf_ies_set,
};

static const struct of_device_id mt6768_pinctrl_of_match[] = {
	{ .compatible = "mediatek,mt6768-pinctrl", .data = &mt6768_data },
	{ }
};
MODULE_DEVICE_TABLE(of, mt6768_pinctrl_of_match);

static int mt6768_pinctrl_probe(struct platform_device *pdev)
{
	struct mtk_pinctrl *pctl;
	struct regmap *regmap;

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;

	regmap = syscon_node_to_regmap(pdev->dev.parent->of_node);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	pctl->dev = &pdev->dev;
	pctl->soc = &mt6768_data;
	((struct mtk_pin_soc *)pctl->soc)->regmap = regmap;

	return mtk_pinctrl_probe(pdev, pctl->soc);
}

static struct platform_driver mt6768_pinctrl_driver = {
	.probe = mt6768_pinctrl_probe,
	.driver = {
		.name = "mt6768-pinctrl",
		.of_match_table = mt6768_pinctrl_of_match,
	},
};
builtin_platform_driver(mt6768_pinctrl_driver);
