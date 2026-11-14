# DeepSDR 101 open firmware — APM32F407 build

**Unofficial fork.** This is the [DeepSDR 101 open firmware](https://github.com/gmtii/deepsdr-101-open-firmware)
by gmtii, ported to DeepSDR 101 radios that have a **Geehy APM32F407VGT6**
instead of the GigaDevice GD32F450. The upstream project does not support this
chip (see upstream issue #68) — please don't report problems with this build
there; open an issue on this fork instead.

> ⚠ **Early test release.** It runs on one radio so far. Read *Status* below
> before flashing, and **back up your flash first** (step 2). Everything here
> is reversible as long as you have that backup.

## Do I have an APM32 radio?

Put the radio into the chip's ROM DFU mode (see step 1) and run `lsusb`:

| You see | Chip | Use |
|---|---|---|
| `314b:0106 Geehy APM32 ISP DFU mode` | **APM32F407** | this fork |
| `28e9:0189 GD32 DFU` | GD32F450/470 | the [upstream firmware](https://github.com/gmtii/deepsdr-101-open-firmware) |

**Never flash the upstream `update.bin` / `customboot.bin` on an APM32 radio,
and never flash these APM32 files on a GD32 radio.** They will not run.

## What is different from the GD32 firmware

The APM32 has 128 KB of main RAM (the GD32F450 has 192 KB) and runs at
144 MHz (GD32: 200 MHz). To fit, this build is based on **V6.72** and:

| | APM32 build |
|---|---|
| **Removed modes** | FT8, HFDL, WSPR, JTTY, STANAG. They still appear in the mode menu; selecting one gives plain USB with an empty panel. |
| **Signal identifier** ("What signal is it?") | does not start (needs more RAM than is free) |
| **Waterfall** | 60 rows of history at half horizontal resolution (each point 2 px wide), with a 12-px black strip below it. GD32: 72 rows, full resolution. |
| **Still working** | AM, SSB, CW, NFM, WFM + RDS, SSTV, WEFAX, AIS, DSC, ALE, Hell, APRS/AX.25, RTTY, PSK31, NAVTEX, DCF77, maps, USB disk |
| **Firmware updates from the USB disk** | **not supported yet** — install with DFU only (below) |
| **Info screen** | SRAM / flash limits still show GD32 values (cosmetic) |

## Status (tested on one radio, 2026-11-13/14, V6.72 build)

| Check | Result |
|---|---|
| Bootloader starts, 144.384 MHz clock, USB disk, SPI flash, DFU knob gesture | ✅ |
| Main screen, touch, knob tuning, spectrum + waterfall | ✅ |
| AM and FM audio | ✅ |
| Settings kept across power cycles | ✅ |
| No false OVERLOAD / garbled input after power-on or AM↔WFM switching (3 power cycles, ~10 round trips, no antenna) | ✅ |
| Decoders (RDS, SSTV, …), USB serial port, selecting a removed mode | not yet checked |

**Fixed in this build — the APM32's I2S erratum.** The APM32F407 copies a
documented STM32F4 flaw: the I2S receiver must be switched on while the
frame-sync line (WS) is high, otherwise it starts mid-sample and stays
misaligned. Symptoms were OVERLOAD with no antenna, a flat spectrum with no
stations, and constant hiss — at random after power-on or after switching back
from WFM. This build waits for a WS rising edge before enabling the receiver.
If you still see those symptoms, open Info, note **Audio load** /
**Audio health** before power-cycling, and please open an issue.

A red **OVERLOAD** badge with a strong antenna on a busy band is genuine: press
**ATT**.

## Installing (Linux / macOS, `dfu-util`)

You need `dfu-util` (Arch: `pacman -S dfu-util`, Debian/Ubuntu: `apt install dfu-util`,
macOS: `brew install dfu-util`). Windows: not tested — the GD32 tool from the
upstream README is for GD32 chips.

Download `customboot_apm32.bin` and `update_apm32.bin` from the
[Releases](https://github.com/artlugovoy/deepsdr-101-open-firmware/releases) page. **Battery connected and charged** for every
write.

**Always pass `-d 314b:0106`** so `dfu-util` can't write to some other DFU
device on your computer (audio interfaces, DACs, …).

### 1. Enter ROM DFU

- **Knob gesture:** radio off → hold the knob pressed → power on → turn the knob
  at least 2 clicks within about a second. The screen stays dark/frozen; that is
  normal.
- **If that doesn't work** (it didn't with the factory bootloader on our radio):
  open the radio and bridge **BOOT0 (right pad of R11) to +3.3 V (right pad of
  C15)** *before* powering on, power on, then remove the bridge. See
  `INSTALL_HOWTO_EN-ES.pdf`, p. 7.

Check: `lsusb` shows `314b:0106 Geehy APM32 ISP DFU mode`.

> USB does nothing at all? On our radio, USB only worked after the **R8 mod**
> (2.4 kΩ → 22 Ω) described in `INSTALL_HOWTO_EN-ES.pdf`, p. 6.

### 2. Back up the whole flash (do not skip)

```sh
dfu-util -d 314b:0106 -a 0 -s 0x08000000:1048576 -U factory_full_flash_1.bin
dfu-util -d 314b:0106 -a 0 -s 0x08000000:1048576 -U factory_full_flash_2.bin
cmp factory_full_flash_1.bin factory_full_flash_2.bin && echo BACKUP OK
```

Keep this file safe — it is your way back to the factory firmware.

### 3. Flash bootloader and firmware

```sh
dfu-util -d 314b:0106 -a 0 -s 0x08000000 -D customboot_apm32.bin
dfu-util -d 314b:0106 -a 0 -s 0x08008000 -D update_apm32.bin
```

Optional read-back check (Linux):

```sh
dfu-util -d 314b:0106 -a 0 -s 0x08008000:$(stat -c %s update_apm32.bin) -U check.bin
cmp update_apm32.bin check.bin && echo MATCH
```

### 4. Power-cycle normally

The main screen should appear. Later updates: knob gesture → step 3 (the
firmware file only, unless the release notes say the bootloader changed).

## Going back to the factory firmware

ROM DFU is built into the chip and cannot be erased, so this always works:

```sh
dfu-util -d 314b:0106 -a 0 -s 0x08000000 -D factory_full_flash_1.bin
```

**Never** use `dfu-util` options or tools that "unprotect", "mass-erase" or
"remove read protection".

## Building from source

```sh
make apm32               # -> update_apm32.bin (fails if RAM use > 129,024 B)
make -C boot apm32       # -> boot/customboot_apm32.bin
```

Everything APM32-specific is behind `#ifdef CHIP_APM32F407`; the GD32 builds
(`make`, `make update470`) are byte-identical to upstream's. Technical notes on
the port: [`docs/APM32_PORT.md`](APM32_PORT.md).

## Licence

AGPL-3.0, same as upstream (see `LICENSE` and `PROCEDENCIA.md`). All credit for
the firmware itself goes to the upstream authors; this fork only adds the
APM32 port.
