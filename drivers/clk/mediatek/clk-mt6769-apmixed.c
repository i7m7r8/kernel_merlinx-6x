// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek MT6768/MT6769/MT6769Z APMixed PLL Clock Driver
 * Based on: vendor 4.14 + mainline clk-mt6779-apmixed.c
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "clk-mtk.h"
#include "clk-pll.h"

#include <dt-bindings/clock/mt6769-clk.h>

static DEFINE_SPINLOCK(mt6769_pll_lock);

static const struct mtk_pll_data apmixed_plls[] = {
	{
		.id = CLK_APMIXED_ARMPLL,
		.name = "armpll",
		.reg = 0x0200,
		.pwr_reg = 0x0204,
		.en_mask = BIT(0),
		.pcw_reg = 0x0208,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0208,
		.pd_shift = 14,
		.vco_reg = 0x0208,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_MAINPLL,
		.name = "mainpll",
		.reg = 0x0210,
		.pwr_reg = 0x0214,
		.en_mask = BIT(0),
		.pcw_reg = 0x0218,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0218,
		.pd_shift = 14,
		.vco_reg = 0x0218,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_UNIVPLL,
		.name = "univpll",
		.reg = 0x0220,
		.pwr_reg = 0x0224,
		.en_mask = BIT(0),
		.pcw_reg = 0x0228,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0228,
		.pd_shift = 14,
		.vco_reg = 0x0228,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_MMPLL,
		.name = "mmpll",
		.reg = 0x0230,
		.pwr_reg = 0x0234,
		.en_mask = BIT(0),
		.pcw_reg = 0x0238,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0238,
		.pd_shift = 14,
		.vco_reg = 0x0238,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_MSDCPLL,
		.name = "msdcpll",
		.reg = 0x0250,
		.pwr_reg = 0x0254,
		.en_mask = BIT(0),
		.pcw_reg = 0x0258,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0258,
		.pd_shift = 14,
		.vco_reg = 0x0258,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_NET1PLL,
		.name = "net1pll",
		.reg = 0x0260,
		.pwr_reg = 0x0264,
		.en_mask = BIT(0),
		.pcw_reg = 0x0268,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0268,
		.pd_shift = 14,
		.vco_reg = 0x0268,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_APLL1,
		.name = "apll1",
		.reg = 0x0270,
		.pwr_reg = 0x0274,
		.en_mask = BIT(0),
		.pcw_reg = 0x0278,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0278,
		.pd_shift = 14,
		.vco_reg = 0x0278,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_APLL2,
		.name = "apll2",
		.reg = 0x0280,
		.pwr_reg = 0x0284,
		.en_mask = BIT(0),
		.pcw_reg = 0x0288,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0288,
		.pd_shift = 14,
		.vco_reg = 0x0288,
		.vco_mask = GENMASK(13, 12),
	},
	{
		.id = CLK_APMIXED_CCIPLL,
		.name = "ccipll",
		.reg = 0x0290,
		.pwr_reg = 0x0294,
		.en_mask = BIT(0),
		.pcw_reg = 0x0298,
		.pcw_bits = GENMASK(23, 0),
		.pd_reg = 0x0298,
		.pd_shift = 14,
		.vco_reg = 0x0298,
		.vco_mask = GENMASK(13, 12),
	},
};

static const struct mtk_clk_desc apmixed_desc = {
	.plls = apmixed_plls,
	.num_plls = ARRAY_SIZE(apmixed_plls),
	.clk_lock = &mt6769_pll_lock,
};

static const struct of_device_id of_match_clk_mt6769_apmixed[] = {
	{ .compatible = "mediatek,mt6769-apmixedsys", .data = &apmixed_desc },
	{ .compatible = "mediatek,mt6769z-apmixedsys", .data = &apmixed_desc },
	{ .compatible = "mediatek,mt6768-apmixedsys", .data = &apmixed_desc },
	{ }
};

static struct platform_driver clk_mt6769_apmixed_drv = {
	.probe = mtk_clk_simple_probe,
	.driver = {
		.name = "clk-mt6769-apmixed",
		.of_match_table = of_match_clk_mt6769_apmixed,
	},
};

builtin_platform_driver(clk_mt6769_apmixed_drv);
