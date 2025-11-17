# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Common Build Commands

QMK uses the `qmk` CLI tool for all development tasks. The format is typically `qmk <command>` or `make <keyboard>:<keymap>[:<target>]`.

**Building firmware:**
```bash
# Using qmk CLI (recommended)
qmk compile -kb <keyboard> -km <keymap>
qmk compile  # Uses defaults from qmk config

# Using make
make <keyboard>:<keymap>
# Example: make controllerworks/mini36:zts

# Build for this repository's keyboards
make moonlander:zts             # Primary keyboard
make controllerworks/mini36:zts # Secondary keyboard
```

**Flashing firmware:**
```bash
qmk flash -kb <keyboard> -km <keymap>
qmk flash  # Uses defaults

# Or with make
make <keyboard>:<keymap>:flash
```

**Testing:**
```bash
# Run all tests
make test:all

# Run specific test
make test:<test_name>

# Example: make test:tap_hold_configurations
```

**Cleaning build artifacts:**
```bash
qmk clean          # Remove .build/ directory
make clean         # Same as above
make distclean     # Also removes *.bin, *.hex, *.uf2 files
```

**Listing keyboards and keymaps:**
```bash
qmk list-keyboards                    # List all keyboards
qmk list-keymaps -kb <keyboard>       # List keymaps for a keyboard
```

**Configuration:**
```bash
qmk config user.keyboard=<keyboard>   # Set default keyboard
qmk config user.keymap=<keymap>       # Set default keymap
```

**Creating new keymap:**
```bash
qmk new-keymap -kb <keyboard>         # Creates new keymap from default
```

## High-Level Architecture

### Directory Structure

QMK firmware is organized into several major components:

**keyboards/** - Keyboard-specific definitions
- Contains a directory for each supported keyboard (900+ keyboards)
- Each keyboard has: `info.json` (hardware definition), `rules.mk` (build config), `config.h` (firmware config), and `keymaps/` subdirectory
- Keyboard paths can be nested (e.g., `keyboards/controllerworks/mini36/`)
- The `info.json` defines the physical layout, matrix, and hardware features

**quantum/** - QMK's core feature layer
- High-level keyboard features: layers, tap-hold, combos, RGB, audio, etc.
- Action processing: `action.c`, `action_layer.c`, `action_tapping.c`
- Feature directories: `audio/`, `backlight/`, `debounce/`, `rgb_matrix/`, etc.
- This is where most QMK-specific functionality lives

**tmk_core/** - Low-level keyboard protocol implementation
- Based on the TMK keyboard firmware
- Protocol implementations for USB communication
- Core keyboard scanning and matrix routines
- Generally you don't need to modify this

**platforms/** - Hardware abstraction layer
- Platform-specific implementations: `avr/`, `chibios/`, `arm_atsam/`
- Provides hardware-agnostic APIs for GPIO, timers, EEPROM, etc.
- Each platform directory contains MCU-specific code

**builddefs/** - Build system makefiles
- `build_keyboard.mk` - Main keyboard build logic
- `common_features.mk` - Feature enablement (RGBLIGHT, AUDIO, etc.)
- Processes rules.mk and generates final build commands

**users/** - Userspace for shared code across keyboards
- Users can create `/users/<username>/` to share code between multiple keyboards
- Automatically included when building a keymap named `<username>`
- Useful for consistent behavior across multiple keyboards
- Contains user-specific `rules.mk`, `config.h`, and source files

**tests/** - Unit test suite
- Feature-specific tests for tap_hold, combos, caps_word, etc.
- Run with `make test:<test_name>` or `make test:all`

### How Keymaps Work

A **keymap** defines the behavior of a keyboard. Each keyboard can have multiple keymaps.

**Keymap location hierarchy:**
1. `/keyboards/<keyboard>/keymaps/<keymap>/` - Keyboard-specific keymaps
2. `/keyboards/<keyboard_parent>/keymaps/<keymap>/` - Can inherit from parent directories
3. `/layouts/<layout_name>/<keymap>/` - Layout-based keymaps (for standard layouts)
4. `/users/<username>/` - Userspace (auto-included if keymap name matches username)

**Keymap structure:**
- `keymap.c` - Required: Contains layer definitions in `keymaps[][]` array
- `config.h` - Optional: Keymap-specific configuration overrides
- `rules.mk` - Optional: Enable/disable features for this keymap

**Layer system:**
- Layers are stacked, with higher-numbered layers taking precedence
- Layer 0 is typically the default/base layer
- Use `KC_TRNS` (transparent) to let keypresses fall through to lower layers
- Common layer functions: `MO(layer)` (momentary), `LT(layer, kc)` (layer-tap), `TG(layer)` (toggle)

### Build System Flow

When you run `make <keyboard>:<keymap>:flash`:

1. **Makefile** parses the rule and calls `qmk list-keyboards` to validate
2. Loads `/keyboards/<keyboard>/rules.mk` to determine DEFAULT_FOLDER and features
3. Includes `/builddefs/build_keyboard.mk` which orchestrates the build
4. Loads keymap-specific files: `keymap.c`, `config.h`, `rules.mk`
5. If keymap matches a username, includes `/users/<username>/` files
6. Processes feature flags from `rules.mk` via `/builddefs/common_features.mk`
7. Includes platform-specific build rules from `/platforms/`
8. Compiles all source files into `.build/` directory
9. Links into `.elf`, generates `.hex`/`.bin`/`.uf2` firmware file
10. Copies firmware to project root (e.g., `controllerworks_mini36_zts.uf2`)
11. Executes flash command if `:flash` target specified

### Configuration Files

**info.json** - Hardware definition (per keyboard)
- Physical layout (key positions)
- Matrix configuration (rows/cols)
- Hardware features (MCU, bootloader, USB info)
- Processed by `qmk` CLI tools

**rules.mk** - Build configuration (per keyboard/keymap)
- Enable/disable features: `RGBLIGHT_ENABLE = yes`
- Set bootloader: `BOOTLOADER = atmel-dfu`
- Include additional source files: `SRC += custom.c`
- Can exist at keyboard level and keymap level

**config.h** - Firmware configuration (per keyboard/keymap)
- Define constants: `#define TAPPING_TERM 200`
- Configure features: `#define RGBLIGHT_ANIMATIONS`
- Pin definitions: `#define MATRIX_ROW_PINS { ... }`
- Can exist at keyboard level, keymap level, and userspace level

### This Repository

This is a fork of QMK firmware with custom keymaps for the user's keyboards.

**Current branch:** zts (this is the user's main branch, not 'main' or 'master')

#### Primary Keyboard: ZSA Moonlander

**Location:** `keyboards/moonlander/keymaps/zts/`

**Build command:** `make moonlander:zts`

**Hardware:**
- Split ergonomic keyboard with 72 keys (36 per side)
- Full 6-row layout with extensive thumb cluster
- RGB matrix lighting (72 individually addressable LEDs)
- Audio output capability (DAC additive driver)
- Custom matrix scanning implementation
- ARM-based (STM32) with external I2C EEPROM

**Keymap features:**
- **Home row mods:** CTRL/ALT/GUI/SHIFT on home row (A/S/D/F and J/K/L/;)
  - Custom tapping term: 216ms (tuned for home row mods)
  - Uses `TAPPING_FORCE_HOLD` for rapid tap-to-hold switching
  - Dynamic tapping term enabled (DT_UP/DT_DOWN keys to adjust on the fly)
- **Layers:** BASE, MOVE, MDIA, WNDW, SYMB, NUMP
  - BASE: QWERTY with home row mods
  - MOVE: Cursor movement, undo/cut/copy/paste, Mac back/forward navigation
  - MDIA: Media controls, RGB controls, screenshot shortcuts, Mac lock screen
  - WNDW: Window management (macOS space switching, Rectangle/Magnet-style positioning)
  - SYMB: Symbol layer with easy access to brackets, operators, special chars
  - NUMP: Full numpad layout on right side
- **macOS optimized:** Custom shortcuts for screenshots (Cmd+Shift+4, etc.), window management, media
- **Layout wrapper macros:** Uses `LAYOUT_moonlander_wrapper()` with row-based defines for cleaner keymap
- **Hyper Escape:** ALL_T(KC_ESCAPE) - Escape when tapped, all modifiers when held
- **Features enabled:** RGB Matrix, Audio, Mouse keys, N-Key Rollover, Swap Hands, Console/Command debug

**Configuration highlights:**
- RGB Matrix max brightness: 175 (to avoid power issues)
- RGB disabled when USB suspended
- Extensive RGB animation modes enabled
- Custom mousekey timing for precise control

#### Secondary Keyboard: ControllerWorks Mini36

**Location:** `keyboards/controllerworks/mini36/keymaps/zts/`

**Build command:** `make controllerworks/mini36:zts`

**Hardware:**
- Split 3x5_3 layout (36 keys total - ultra-compact)
- OLED displays on each half
- RP2040-based controller

**Keymap features:**
- **Home row mods:** Same style as Moonlander (CTRL/ALT/GUI/SHIFT on A/S/D/F and J/K/L/;)
- **Layers:** BASE, LOWER, RAISE, ADJUST, MOVE, WNDW, SYMB, NUMP
- **Layer-tap thumb keys:** Heavy use of LT() for layer access without dedicated layer keys
- **OLED display:** Shows current layer name and LED status
- **Optimized for 36 keys:** More aggressive layer usage due to minimal key count
- Builds to: `controllerworks_mini36_zts.uf2`

**Design philosophy:**
- Both keyboards share similar layer concepts (MOVE, WNDW, SYMB, NUMP)
- Both use home row mods for consistent muscle memory
- Mini36 is more aggressive with layer-tap keys due to space constraints
- Moonlander has more direct access keys due to larger layout

## Important Notes

- QMK firmware is based on C (for AVR/ARM microcontrollers)
- The `qmk` CLI tool requires Python 3
- Firmware files are generated in `.build/` and copied to project root
- Git submodules are used for libraries (under `lib/`) - run `qmk git-submodule` to sync
- Most QMK features are toggled via `rules.mk` and configured via `config.h`
- When editing keymaps, be careful with commas in the `keymaps[][]` array
- Use `KC_TRNS` or `_______` for transparent keys in higher layers
