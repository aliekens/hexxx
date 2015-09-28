# HEXX Hardware

## Lasercutting files

The Inkscape SVG plans for lasercutting of the boards are here. in this directory.

It consists of a 3mm top layer in MDF (LEDs snap into this layer), glued to a support layer in 4mm concreteplex (for added strength, the LEDs weigh some 2 kg and the MDF will bend without extra multiplexed support). The other two layers are also 4mm concreteplex. The machine is bolted together with 6 M8 12mm bolts and pieces of M8 aluminium tubing to keep plates separated where I want them.

## LED strings

I used 12mm ws2811 LED strings ("strings", not "strips", available from china for cheap). They come in strings of 50 and can easily be connected to make a longer string (of 400 in this case). Each string of 50 LEDs needs to be powered with 5V and consumes about 1A (when all lights are white), so you'll need a 5V PSU with at least 10A.

LED #0 is the center LED. The ring of 6 LEDs surrounding that are next, following with a ring of 12, and so on. The first LED in each ring is the LED in the corner closest to player 0's left button.

The buttons have been recovered from an "iCade core", they fit in 24mm holes but I understand that such buttons are easily sourced.

Everything is wired up to a Raspberry Pi to run the repository.﻿
