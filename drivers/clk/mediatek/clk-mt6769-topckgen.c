// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek MT6768/MT6769/MT6769Z Top Clock Generator Driver
 * Based on: clk-mt6779.c (mainline 6.12) + vendor 4.14
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "clk-gate.h"
#include "clk-mtk.h"
#include "clk-mux.h"

#include <dt-bindings/clock/mt6769-clk.h>

static DEFINE_SPINLOCK(mt6769_clk_lock);
FACTOR(CLK_TOP_MAINPLL_D2, "mainpll_d2", "mainpll", 1, 2),
	FACTOR(CLK_TOP_MAINPLL_D3, "mainpll_d3", "mainpll", 1, 3),

/* Fixed factor clocks */
static const struct mtk_fixed_factor top_factor_clks[] = {
	FACTOR(CLK_TOP_CLK13M, "clk13m", "clk26m", 1, 2),
	FACTOR(CLK_TOP_OSC_D2, "osc_d2", "clk26m", 1, 2),
	FACTOR(CLK_TOP_OSC_D4, "osc_d4", "clk26m", 1, 4),
	FACTOR(CLK_TOP_OSC_D8, "osc_d8", "clk26m", 1, 8),
	FACTOR(CLK_TOP_ARMPLL_D3, "armpll_d3", "armpll", 1, 3),
	FACTOR(CLK_TOP_CCIPLL_D3, "ccipll_d3", "ccipll", 1, 3),
	FACTOR(CLK_TOP_MMPLL_D3, "mmpll_d3", "mmpll", 1, 3),
	FACTOR(CLK_TOP_MMPLL_D4, "mmpll_d4", "mmpll", 1, 4),
	FACTOR(CLK_TOP_MMPLL_D5, "mmpll_d5", "mmpll", 1, 5),
	FACTOR(CLK_TOP_UNIVPLL_D2, "univpll_d2", "univpll", 1, 2),
	FACTOR(CLK_TOP_UNIVPLL_D3, "univpll_d3", "univpll", 1, 3),
	FACTOR(CLK_TOP_UNIVPLL_D5, "univpll_d5", "univpll", 1, 5),
	FACTOR(CLK_TOP_UNIVPLL_D5_D4, "univpll_d5_d4", "univpll_d5", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL_D6, "univpll_d6", "univpll", 1, 6),
	FACTOR(CLK_TOP_UNIVPLL_D7, "univpll_d7", "univpll", 1, 7),
	FACTOR(CLK_TOP_UNIVPLL_D2_D4, "univpll_d2_d4", "univpll_d2", 1, 4),
	FACTOR(CLK_TOP_UNIVPLL_D2_D8, "univpll_d2_d8", "univpll_d2", 1, 8),
	FACTOR(CLK_TOP_UNIVPLL_D2_D16, "univpll_d2_d16", "univpll_d2", 1, 16),
	FACTOR(CLK_TOP_UNIVPLL_D3_D4, "univpll_d3_d4", "univpll_d3", 1, 4),
	FACTOR(CLK_TOP_NET1PLL_D4, "net1pll_d4", "net1pll", 1, 4),
	FACTOR(CLK_TOP_APLL1_D4, "apll1_d4", "apll1", 1, 4),
	FACTOR(CLK_TOP_APLL2_D4, "apll2_d4", "apll2", 1, 4),
	FACTOR(CLK_TOP_USB_PHY_48M, "usb_phy_48m", "univpll", 1, 25),
};

/* MUX parent arrays - proper C string arrays */
static const char * const armpll_parents[] __initconst = {
	"armpll", "armpll_d3"
};

static const char * const mainpll_parents[] __initconst = {
	"mainpll", "mainpll_d2", "mainpll_d3"
};

static const char * const univpll_parents[] __initconst = {
	"univpll", "univpll_d2", "univpll_d3"
};

static const char * const mmpll_parents[] __initconst = {
	"mmpll", "mmpll_d3"
};

/* MUX clocks */
static const struct mtk_mux top_mux_clks[] = {
	MUX(CLK_TOP_ARMPLL, "armpll_sel", armpll_parents, 0x0000, 0, 1),
	MUX(CLK_TOP_MAINPLL, "mainpll_sel", mainpll_parents, 0x0004, 0, 2),
	MUX(CLK_TOP_UNIVPLL, "univpll_sel", univpll_parents, 0x0008, 0, 2),
	MUX(CLK_TOP_MMPLL, "mmpll_sel", mmpll_parents, 0x000c, 0, 1),
};

static const struct mtk_clk_desc topckgen_desc = {
	.factor_clks = top_factor_clks,
	.num_factor_clks = ARRAY_SIZE(top_factor_clks),
	.mux_clks = top_mux_clks,
	.num_mux_clks = ARRAY_SIZE(top_mux_clks),
	.clk_lock = &mt6769_clk_lock,
};

static const struct of_device_id of_match_clk_mt6769_topckgen[] = {
	{ .compatible = "mediatek,mt6769-topckgen", .data = &topckgen_desc },
	{ .compatible = "mediatek,mt6769z-topckgen", .data = &topckgen_desc },
	{ .compatible = "mediatek,mt6768-topckgen", .data = &topckgen_desc },
	{ }
};

static struct platform_driver clk_mt6769_topckgen_drv = {
	.probe = mtk_clk_simple_probe,
	.driver = {
		.name = "clk-mt6769-topckgen",
		.of_match_table = of_match_clk_mt6769_topckgen,
	},
};

builtin_platform_driver(clk_mt6769_topckgen_drv);
