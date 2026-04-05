# Firmware Setup for MerlinX Kernel 6.12

## Required Firmware Files

The following firmware blobs are required for full hardware functionality:

### 1. WiFi/Bluetooth (MT7663)
```
/lib/firmware/mediatek/WIFI_RAM_CODE_mt7663_1_1_hdr.bin
/lib/firmware/mediatek/BT_RAM_CODE_mt7663_1_1_hdr.bin
```
**Source**: Extract from vendor boot image or download from MediaTek SDK
- Vendor boot: `https://github.com/david568303/Redmi-note-9-Kernels/releases`
- Or extract from MIUI fastboot ROM: `firmware-update/` partition

### 2. Touchscreen (Novatek NT36672A)
```
/lib/firmware/novatek_ts_fw.bin
/lib/firmware/novatek_ts_mp.bin
```
**Source**: Extract from vendor `/vendor/firmware/` partition
```bash
# From device:
adb pull /vendor/firmware/NT36672A_B0.bin /lib/firmware/novatek_ts_fw.bin
adb pull /vendor/firmware/NT36672A_MP_B0.bin /lib/firmware/novatek_ts_mp.bin
```

### 3. GPU (Mali-G52)
Panfrost driver uses kernel-space firmware - no external blobs needed.

### 4. Sensors (BMI160, STK3310, AKM09918)
No firmware required - all work out of the box.

### 5. Display Panel
No firmware required - panel driver handles initialization.

---

## Firmware Extraction Script

Run this on your device to extract all firmware:

```bash
#!/system/bin/sh
# extract-firmware.sh - Run as root on stock ROM

FIRMWARE_DIR="/storage/emulated/0/kernel-firmware"
mkdir -p "$FIRMWARE_DIR/mediatek"

# WiFi/BT firmware
cp /vendor/firmware/WIFI_RAM_CODE_mt7663_1_1_hdr.bin "$FIRMWARE_DIR/mediatek/" 2>/dev/null
cp /vendor/firmware/BT_RAM_CODE_mt7663_1_1_hdr.bin "$FIRMWARE_DIR/mediatek/" 2>/dev/null

# Touchscreen firmware
cp /vendor/firmware/NT36672A_B0.bin "$FIRMWARE_DIR/novatek_ts_fw.bin" 2>/dev/null
cp /vendor/firmware/NT36672A_MP_B0.bin "$FIRMWARE_DIR/novatek_ts_mp.bin" 2>/dev/null

echo "Firmware extracted to $FIRMWARE_DIR"
echo "Push to device: adb push $FIRMWARE_DIR /data/vendor/firmware"
```

---

## Installation

After extracting firmware, push to device:

```bash
# For custom recovery (TWRP/OrangeFox):
adb push firmware /data/vendor/firmware/

# Or mount vendor and copy:
adb root
adb shell mkdir -p /vendor/firmware/mediatek
adb push firmware/mediatek/* /vendor/firmware/mediatek/
adb push firmware/novatek* /vendor/firmware/
```

---

## Without Firmware

The kernel will boot and work without firmware:
- ✅ eMMC/SD storage
- ✅ USB OTG
- ✅ Display (if panel initialized by bootloader)
- ✅ Touchscreen (if bootloader loaded firmware)
- ✅ Sensors (BMI160, STK3310, AKM09918)
- ✅ Audio
- ❌ WiFi (needs firmware)
- ❌ Bluetooth (needs firmware)
- ❌ Touchscreen init (needs firmware if not pre-loaded)
