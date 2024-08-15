# Left-handed Artsey.io Dvorak Layout for the Work Louder Micro using QMK

This is a left-handed layout for the Work Louder Micro macro pad, using the Artsey.io layout mapped to Dvorak.

- [Artsey.io](https://artsey.io/) is a one-handed keyboard layout that uses 8 keys in a 2x4 grid and a lot of chords to access all the keys on a standard keyboard.
- Left-handed means that the layout is designed to be used with the left hand, leaving the right hand free to use the mouse.
- Dvorak is an alternative keyboard layout that is designed to be more efficient than the standard QWERTY layout. This does not matter if you are using a one-handed keyboard, but I use Dvorak on my main keyboard do not want to switch input methods when using the macro pad.
- [QMK](https://qmk.fm/) is an open-source firmware for custom keyboards that allows you to program your keyboard to do whatever you want.
- The Work Louder Micro is a 16-ish-key macro pad with dual encoders, per-key RGB, RGB underglow, and more. It is available from the [Work Louder shop](https://worklouder.cc/creator-micro/).

## Usage

Create a new keymap in QMK for the Work Louder Micro:

```bash
qmk new-keymap -kb work_louder/micro -km dvorak-artsey-lh
```

Copy the contents of this repository into grandparent directory of the new keymap. This needs to be done because we have to patch `rgb_functions.c` so that we can disable the RGB underglow and reduce firmware size.

```bash
cp -r * ../qmk/keyboards/work_louder
```

Do the normal QMK build process:

```bash
qmk compile -kb work_louder/micro -km dvorak-artsey-lh
```

Flash the firmware to the Work Louder Micro (enter the bootloader first by holding down the horizontal encoder and plugging in the keyboard)

```bash
qmk flash -kb work_louder/micro -km dvorak-artsey-lh
```

I've mapped the top right encoder button to reset, so that you can easily enter the bootloader without having to unplug the keyboard in subsequent flashes.

## Thanks

This would not be possible without the work of the QMK team and the creators of the Artsey.io layout.

## work_louder/micro

![work_louder/micro](https://i.imgur.com/4Hdt41Gh.jpg)

A 16 "key" macro pad, with dual encoders, per key RGB, RGB underglow and more

* Keyboard Maintainer: [Drashna Jael're](https://github.com/Drashna Jael're)
* Hardware Supported:  atmega32u4 based PCB
* Hardware Availability: [Work Louder shop](https://worklouder.cc/creator-micro/)

Make example for this keyboard (after setting up your build environment):

    make work_louder/micro:default

Flashing example for this keyboard:

    make work_louder/micro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the horizontal encoder (top left) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
