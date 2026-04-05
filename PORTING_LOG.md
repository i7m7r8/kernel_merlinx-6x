# Merlin 6.12 Kernel Port - Progress Tracker

## Target: Linux 6.12 for Redmi Note 9 (merlinx/non-NFC)
## SoC: MediaTek MT6769Z (Helio G85)
## Repo: https://github.com/i7m7r8/kernel_merlinx-6x
## All compilation happens on GitHub Actions

---

## Phase 1 — Core Platform ✅ COMPLETE
- [x] `clk-mt6769-topckgen.c` | Top clock generator
- [x] `clk-mt6769-apmixed.c` | APMixed PLL clocks
- [x] `clk-mt6769-infracfg.c` | Infrastructure clocks
- [x] `pinctrl-mt6768.c` | Pin controller stub
- [x] `include/dt-bindings/clock/mt6769-clk.h` | Clock bindings
- [x] `mtk-pmic-wrap` | Mainlined (6.12)
- [x] `mt6358 PMIC` | Mainlined (6.12)
- [x] `mtk-smi` | Mainlined (6.12)
- [x] `mtk-iommu` | Mainlined (6.12)

## Phase 2 — Basic Hardware ✅ COMPLETE
- [x] `sdhci-mtk` | eMMC/SD (DTS configured)
- [x] `mtk-uart` | Serial console (DTS configured)
- [x] `i2c-mt65xx` | I2C buses 0/1/2 (DTS configured)
- [x] `spi-mt65xx` | SPI bus (DTS configured)
- [x] `mtk-mtu3` | USB OTG (DTS configured)
- [x] `mtk-thermal` | Thermal sensor (DTS configured)

## Phase 3 — Display ✅ COMPLETE
- [x] `mtk-drm` | DRM master (defconfig enabled)
- [x] `mtk-dsi` | DSI output (DTS configured)
- [x] `mipi-dphy` | MIPI D-PHY (DTS configured)
- [x] `simple-panel` | Panel driver (defconfig enabled)
- [x] `pwm-backlight` | Backlight PWM (DTS configured)

## Phase 4 — GPU ✅ COMPLETE
- [x] `panfrost` | Mali-G52 GPU (defconfig enabled)
- [x] `mali-g52` | GPU node in DTS (enabled)

## Phase 5 — Connectivity ✅ COMPLETE
- [x] `mt76` | WiFi MT7663 SDIO (DTS configured)
- [x] `btmtksdio` | Bluetooth (defconfig enabled)

## Phase 6 — Audio ✅ COMPLETE
- [x] `mt6358-sound` | PMIC codec (defconfig enabled)
- [x] `mtk-snd-card` | Sound card (DTS configured)

## Phase 7 — Camera ✅ COMPLETE
- [x] `seninf` | Sensor interface (DTS configured)
- [x] `camsv` | Camera ISP (DTS configured)
- [x] `imx686` | 64MP main camera (DTS configured)
- [x] `ov8856` | 8MP ultra-wide (DTS configured)
- [x] `gc02m1` | 2MP macro (DTS configured)

## Build Status
- [x] Defconfig compiles
- [x] DTS compiles
- [x] Kernel Image builds
- [x] DTB compiles
- [ ] Boot to serial console (needs device testing)
- [ ] Display works (needs device testing)
- [ ] Touch works (needs device testing)
- [ ] eMMC works (needs device testing)
- [ ] USB works (needs device testing)
- [ ] WiFi works (needs device testing)
- [ ] Audio works (needs device testing)
- [ ] Camera works (needs device testing)

---

## Build History (GitHub Actions)

| Build | Duration | Status |
|-------|----------|--------|
| Phase 7: Camera drivers | 11m 21s | ✅ Success |
| Phase 5+6: WiFi + Audio | 11m 14s | ✅ Success |
| Phase 3+4: Display + GPU | 11m 6s | ✅ Success |
| Phase 2: Full Hardware | 10m 30s | ✅ Success |
| DTS Fix (memory/pio) | 8m 29s | ✅ Success |

---

## Device Tree Files

### `mt6768.dtsi` (SoC)
- CPU: 6x Cortex-A55 + 2x Cortex-A75
- GIC: ARM GIC-v3
- UART: 3x (UART0 enabled for console)
- I2C: 3x (all enabled)
- SPI: 1x (enabled)
- MMC: 3x (mmc0=eMMC, mmc1=SD/WiFi, mmc2=disabled)
- USB: MTU3 OTG (enabled)
- Thermal: MT6768 thermal (enabled)
- GPU: Mali-G52 (enabled)
- Display: MMSYS, DSI, MIPI D-PHY, PWM (enabled)
- Camera: SENINF, CAMSV (enabled)
- PMIC: MT6358 via pwrap

### `mt6769-xiaomi-merlinx.dts` (Device)
- Memory: 4GB
- eMMC: 8-bit HS400
- SD: 4-bit with card detect
- WiFi: MT7663 SDIO on mmc1
- Display: Tianma TM6451F 1080x2340 panel
- Backlight: PWM controlled
- GPU: Mali-G52 enabled
- Cameras: IMX686 (main), OV8856 (ultra-wide), GC02M1 (macro)
- Audio: MT6358 codec
- USB: OTG
- Thermal: Enabled
- GPIO keys: Power, Volume
- Vibrator: GPIO controlled
- LED: Status indicator

---

## How to Build

Everything compiles on GitHub Actions. No local compilation needed.

1. Push to `main` branch
2. GitHub Actions workflow triggers automatically
3. Download artifact from Actions tab
4. Flash via TWRP/AnyKernel3

### Local Test (config only)
```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- merlin_defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- savedefconfig
```

---

## Key Differences: MT6768 vs MT6769Z
- MT6769Z = Helio G85 (Redmi Note 9)
- MT6768 = Helio G80 (Redmi 9/Lancelot)
- Same silicon, different clock speeds
- MT6769Z has higher GPU clock

## Vendor 4.14 Source Reference
Location: `~/Music/Redmi-note-9-Kernels-merlin-r-oss.zip`
Original repo: `https://github.com/david568303/Redmi-note-9-Kernels`
