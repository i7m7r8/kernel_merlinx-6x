#!/system/bin/sh
# extract-firmware.sh - Extract firmware from stock MIUI ROM
# Run as root on stock ROM, or from TWRP with stock firmware installed

FIRMWARE_DIR="/storage/emulated/0/kernel-firmware"
mkdir -p "$FIRMWARE_DIR/mediatek"

echo "=== Extracting MerlinX Firmware ==="

# WiFi/BT firmware (MT7663)
for f in WIFI_RAM_CODE_mt7663_1_1_hdr.bin BT_RAM_CODE_mt7663_1_1_hdr.bin; do
    for path in /vendor/firmware/mediatek/$f /vendor/firmware/$f /system/vendor/firmware/$f; do
        if [ -f "$path" ]; then
            cp "$path" "$FIRMWARE_DIR/mediatek/$f"
            echo "✓ $f found and copied"
            break
        fi
    done
done

# Touchscreen firmware (Novatek NT36672A)
for ts_fw in NT36672A_B0.bin NT36672A_B0_MP.bin NT36672A.bin; do
    for path in /vendor/firmware/$ts_fw /vendor/firmware/mediatek/$ts_fw /system/vendor/firmware/$ts_fw; do
        if [ -f "$path" ]; then
            cp "$path" "$FIRMWARE_DIR/novatek_ts_fw.bin"
            echo "✓ Touchscreen firmware found: $ts_fw"
            break
        fi
    done
done

# MP calibration
for ts_mp in NT36672A_MP_B0.bin NT36672A_MP.bin; do
    for path in /vendor/firmware/$ts_mp /vendor/firmware/mediatek/$ts_mp; do
        if [ -f "$path" ]; then
            cp "$path" "$FIRMWARE_DIR/novatek_ts_mp.bin"
            echo "✓ Touchscreen MP calibration found: $ts_mp"
            break
        fi
    done
done

echo ""
echo "=== Summary ==="
ls -la "$FIRMWARE_DIR/mediatek/" 2>/dev/null
ls -la "$FIRMWARE_DIR/novatek_ts_fw.bin" 2>/dev/null
ls -la "$FIRMWARE_DIR/novatek_ts_mp.bin" 2>/dev/null
echo ""
echo "Firmware extracted to: $FIRMWARE_DIR"
echo ""
echo "To install on custom ROM:"
echo "  adb push $FIRMWARE_DIR/mediatek/* /vendor/firmware/mediatek/"
echo "  adb push $FIRMWARE_DIR/novatek*.bin /vendor/firmware/"
