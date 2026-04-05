# Merlin 6.12 Kernel Port - Progress Tracker

## Target: Linux 6.12 for Redmi Note 9 (merlinx/non-NFC)
## SoC: MediaTek MT6769Z (Helio G85)

---

## Phase 1 — Core Platform
- [x] `include/dt-bindings/clock/mt6769-clk.h` | Clock bindings header
- [x] `clk-mt6769-topckgen.c` | Top clock generator
- [x] `clk-mt6769-apmixed.c` | APMixed PLL clocks
- [x] `clk-mt6769-infracfg.c` | Infrastructure clocks
- [ ] `pinctrl-mt6768.c` | Pin controller (stub)
- [ ] `mtk-pmic-wrap.c` | PMIC wrapper (use mainline)
- [ ] `mt6358 PMIC` | Already mainlined
- [ ] `scpsys-mt6768.c` | Power domains
- [ ] `mtk-smi` | Already mainlined (need MT6768 ID)
- [ ] `mtk-iommu` | Already mainlined (need MT6768 ID)

## Phase 2 — Basic Hardware
- [ ] `sdhci-mtk` | Mainlined (DTS only)
- [ ] `mtk-uart` | Mainlined (DTS only)
- [ ] `i2c-mt65xx` | Mainlined (DTS only)
- [ ] `spi-mt65xx` | Mainlined (DTS only)
- [ ] `mtk-mtu3` (USB) | Mainlined (DTS only)
- [ ] `mtk-thermal` | Mainlined (DTS only)

## Phase 3 — Display/GPU
- [ ] `mtk-drm` | Need port
- [ ] `mtk-dsi` | Need port
- [ ] `panel driver` | Need port
- [ ] `mali-g52` | Partial mainline

## Phase 4 — Input
- [ ] Touchscreen (NT36672A) | Need driver
- [ ] `bmi160` IMU | Mainlined
- [ ] `stk3310` proximity | Mainlined
- [ ] GPIO keys | Mainlined

## Phase 5 — Connectivity
- [ ] `mt76` WiFi (MT7663) | Mainlined (SDIO partial)
- [ ] `btmtksdio` BT | Mainlined (partial)

## Phase 6 — Audio
- [ ] `mt6358-sound` | Mainlined
- [ ] `mtk-afe-pcm` | Need port
- [ ] Sound card glue | Need port

## Phase 7 — Camera
- [ ] `mtk-seninf` | Need port
- [ ] `mtk-camsys` | Need port
- [ ] `imx686` sensor | Need driver
- [ ] `ov8856` sensor | Mainlined

## Build Status
- [ ] Defconfig compiles
- [ ] DTS compiles
- [ ] Boot to serial
- [ ] Display works
- [ ] Touch works
- [ ] eMMC works
- [ ] USB works
- [ ] WiFi works
- [ ] Audio works
- [ ] Camera works

---

## Vendor 4.14 Source Reference
Location: `~/Music/Redmi-note-9-Kernels-merlin-r-oss.zip`
This contains the original 4.14 kernel from david568303's repo.

## Key Differences: MT6768 vs MT6769Z
- MT6769Z = Helio G85 (Redmi Note 9)
- MT6768 = Helio G80 (Redmi 9/Lancelot)
- Same silicon, different clock speeds
- MT6769Z has higher GPU clock
