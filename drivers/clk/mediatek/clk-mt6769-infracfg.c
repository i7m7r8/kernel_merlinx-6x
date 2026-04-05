// SPDX-License-Identifier: GPL-2.0
/*
 * MediaTek MT6768/MT6769/MT6769Z Infrastructure Clock Driver
 * Based on: vendor 4.14 + mainline clk-mt6779-infracfg.c
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "clk-gate.h"
#include "clk-mtk.h"

#include <dt-bindings/clock/mt6769-clk.h>

static DEFINE_SPINLOCK(mt6769_clk_lock);

static const struct mtk_gate_regs infra_cg_regs = {
	.set_ofs = 0x40,
	.clr_ofs = 0x44,
	.sta_ofs = 0x48,
};

#define GATE_INFRA(_id, _name, _parent, _shift) \
	GATE_MTK(_id, _name, _parent, &infra_cg_regs, _shift, &mt6769_clk_lock)

static const struct mtk_gate infra_clks[] = {
	GATE_INFRA(CLK_INFRA_IPCORE, "infra_ipcore", "univpll_d2", 0),
	GATE_INFRA(CLK_INFRA_GCE, "infra_gce", "univpll_d2", 1),
	GATE_INFRA(CLK_INFRA_GCE_26M, "infra_gce_26m", "clk26m", 2),
	GATE_INFRA(CLK_INFRA_SCP_SPI, "infra_scp_spi", "univpll_d2", 3),
	GATE_INFRA(CLK_INFRA_SCPSYS, "infra_scpsys", "univpll_d2", 4),
	GATE_INFRA(CLK_INFRA_L2C_SRAM, "infra_l2c_sram", "univpll_d2", 5),
	GATE_INFRA(CLK_INFRA_CCI, "infra_cci", "univpll_d2", 6),
	GATE_INFRA(CLK_INFRA_CPUCFG, "infra_cpucfg", "univpll_d2", 7),
	GATE_INFRA(CLK_INFRA_PDA, "infra_pda", "univpll_d2", 8),
	GATE_INFRA(CLK_INFRA_APXGPU, "infra_apxgpu", "univpll_d2", 9),
	GATE_INFRA(CLK_INFRA_DBGOPT, "infra_dbgopt", "univpll_d2", 10),
	GATE_INFRA(CLK_INFRA_EMI, "infra_emi", "univpll_d2", 11),
	GATE_INFRA(CLK_INFRA_CPUCFG_N9, "infra_cpucfg_n9", "univpll_d2", 12),
	GATE_INFRA(CLK_INFRA_CONNMCU, "infra_connmcu", "univpll_d2", 13),
	GATE_INFRA(CLK_INFRA_MCU_BUS, "infra_mcu_bus", "univpll_d2", 14),
	GATE_INFRA(CLK_INFRA_MSDC0, "infra_msdc0", "univpll_d2", 15),
	GATE_INFRA(CLK_INFRA_MSDC1, "infra_msdc1", "univpll_d2", 16),
	GATE_INFRA(CLK_INFRA_MSDC2, "infra_msdc2", "univpll_d2", 17),
	GATE_INFRA(CLK_INFRA_NFI, "infra_nfi", "univpll_d2", 18),
	GATE_INFRA(CLK_INFRA_NFIECC, "infra_nfiecc", "univpll_d2", 19),
	GATE_INFRA(CLK_INFRA_SF, "infra_sf", "univpll_d2", 20),
	GATE_INFRA(CLK_INFRA_USB_SYS, "infra_usb_sys", "univpll_d2", 21),
	GATE_INFRA(CLK_INFRA_USB_66M, "infra_usb_66m", "clk26m", 22),
	GATE_INFRA(CLK_INFRA_UART0, "infra_uart0", "univpll_d2", 23),
	GATE_INFRA(CLK_INFRA_UART1, "infra_uart1", "univpll_d2", 24),
	GATE_INFRA(CLK_INFRA_UART2, "infra_uart2", "univpll_d2", 25),
	GATE_INFRA(CLK_INFRA_IRDA, "infra_irda", "univpll_d2", 26),
	GATE_INFRA(CLK_INFRA_BTIF, "infra_btif", "univpll_d2", 27),
	GATE_INFRA(CLK_INFRA_DISP_PWM, "infra_disp_pwm", "univpll_d2", 28),
	GATE_INFRA(CLK_INFRA_PMIC_SPI, "infra_pmic_spi", "clk26m", 29),
	GATE_INFRA(CLK_INFRA_PMIC_WRAP, "infra_pmic_wrap", "clk26m", 30),
	GATE_INFRA(CLK_INFRA_PMIC_AP_32K, "infra_pmic_ap_32k", "clk32k", 31),
};

/* Second register bank for bits 32-35 */
static const struct mtk_gate_regs infra_cg_regs_1 = {
	.set_ofs = 0x4C,
	.clr_ofs = 0x50,
	.sta_ofs = 0x54,
};

#define GATE_INFRA_1(_id, _name, _parent, _shift) \
	GATE_MTK(_id, _name, _parent, &infra_cg_regs_1, _shift, &mt6769_clk_lock)

static const struct mtk_gate infra_clks_1[] = {
	GATE_INFRA_1(CLK_INFRA_AUD, "infra_aud", "univpll_d2", 0),
	GATE_INFRA_1(CLK_INFRA_AUDIO_26M_B, "infra_audio_26m_b", "clk26m", 1),
	GATE_INFRA_1(CLK_INFRA_MD_32K, "infra_md_32k", "clk32k", 2),
	GATE_INFRA_1(CLK_INFRA_MD_SYS, "infra_md_sys", "univpll_d2", 3),
};

static const struct mtk_clk_desc infracfg_desc = {
	.clks = infra_clks,
	.num_clks = ARRAY_SIZE(infra_clks),
	.clk_lock = &mt6769_clk_lock,
};

/* Second bank descriptor */
static const struct mtk_clk_desc infracfg_desc_1 = {
	.clks = infra_clks_1,
	.num_clks = ARRAY_SIZE(infra_clks_1),
	.clk_lock = &mt6769_clk_lock,
};

static const struct of_device_id of_match_clk_mt6769_infracfg[] = {
	{ .compatible = "mediatek,mt6769-infracfg", .data = &infracfg_desc },
	{ .compatible = "mediatek,mt6769z-infracfg", .data = &infracfg_desc },
	{ .compatible = "mediatek,mt6768-infracfg", .data = &infracfg_desc },
	{ }
};

static struct platform_driver clk_mt6769_infracfg_drv = {
	.probe = mtk_clk_simple_probe,
	.driver = {
		.name = "clk-mt6769-infracfg",
		.of_match_table = of_match_clk_mt6769_infracfg,
	},
};

builtin_platform_driver(clk_mt6769_infracfg_drv);

/* Separate driver for second register bank */
static const struct of_device_id of_match_clk_mt6769_infracfg_1[] = {
	{ .compatible = "mediatek,mt6769-infracfg-ao", .data = &infracfg_desc_1 },
	{ .compatible = "mediatek,mt6769z-infracfg-ao", .data = &infracfg_desc_1 },
	{ .compatible = "mediatek,mt6768-infracfg-ao", .data = &infracfg_desc_1 },
	{ }
};

static struct platform_driver clk_mt6769_infracfg_1_drv = {
	.probe = mtk_clk_simple_probe,
	.driver = {
		.name = "clk-mt6769-infracfg-ao",
		.of_match_table = of_match_clk_mt6769_infracfg_1,
	},
};

builtin_platform_driver(clk_mt6769_infracfg_1_drv);
