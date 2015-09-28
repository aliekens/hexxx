# HEXXX Hardware

![Completed HEXXX](https://raw.github.com/aliekens/hexxx/master/util/hardware/photo.jpg)

## Lasercutting files

The Inkscape SVG plans for lasercutting of the boards are available in this directory.

![A view from the side of a HEXXX](https://raw.github.com/aliekens/hexxx/master/util/hardware/side_photo.jpg)

The "hardware stack" consists of 3 plates. 

A 3mm top layer in MDF (LEDs snap into this layer), glued to a support layer in 4mm concreteplex (for added strength, the LEDs weigh some 2 kg and the MDF will bend without extra multiplexed support). 

The other two layers are also 4mm concreteplex. The center layer supports the weight of the LED string and keeps the LEDs in position. The PSU, Raspberry Pi and a multifunctional breadboard are glued to the bottom of this center plate. The bottom plate closes the machines and helps steadiness. 

The machine is bolted together with 6 M8 12mm bolts and pieces of M8 aluminium tubing to keep plates separated where I want them.

## LED strings

I used 12mm ws2811 LED strings ("strings", not "strips", available from china for cheap). They come in strings of 50 and can easily be connected to make a longer string (of 400 in this case). Each string of 50 LEDs needs to be powered with 5V and consumes about 1A (when all lights are white), so you'll need a 5V PSU with at least 10A.

LED #0 is the center LED. The ring of 6 LEDs surrounding that are next, following with a ring of 12, and so on. The first LED in each ring is the LED in the corner closest to player 0's left button.

The LED string is controlled by GPIO pin 18.

## Buttons

The buttons have been recovered from an "iCade core", they fit in 24mm holes but I understand that such buttons are easily sourced. The buttons are connected as defined in `hexxx.h`:

```
#define BUTTON_0_LEFT_GPIO 2
#define BUTTON_0_RIGHT_GPIO 3
#define BUTTON_1_LEFT_GPIO 4
#define BUTTON_1_RIGHT_GPIO 17
#define BUTTON_2_LEFT_GPIO 27
#define BUTTON_2_RIGHT_GPIO 22
```

Please note that buttons have been wired with pull-up resistors.

## Raspberry Pi

Everything is wired up to a Raspberry Pi to run the repository.﻿
