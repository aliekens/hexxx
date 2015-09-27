# HEXXX

HEXXX is a DIY 3-player console with a hexagonal grid of 400 RGB LEDs, 6 game buttons, and based on a Raspberry Pi. HEXXX is being built at http://opengarage.org

For development without the hardware, HEXXX applications can be run in a HEXXX simulator on systems that supports building with SDL (http://libsdl.org/ - Mac, Linux confirmed to work).

The repository contains various demos, such as Pong and Tron for three, Flappybird for 6, a X11 screengrabber and a cube demo. The sample application in `example.cpp` shows you how to build your own HEXXX apps.

The repository also contains the Inkscape SVG files for laser cutting and constructing your own HEXXX hardware. 

# Prerequisites

## X11

X11 is mainly required for the `screengrab` example. Install `libx11-dev` with

```sudo apt-get install libx11-dev```

## SDL

For the simulator, you'll need SDL2 (http://libsdl.org) and `SDL_gfx` for SDL2 (https://github.com/thp/SDL_gfx). To check whether you have SDL, run `sdl2-config`, which should be an existing executable.

LibSDL2 can be downloaded from https://www.libsdl.org/download-2.0.php, with binaries for your Mac or Windows development machine. Mind that the binary distribution only includes the runtime framework and not the binaries (e.g. `sdl2-config`). So for development, you will need to grab the sources and compile them.

Note that SDL2 isn't available as an apt package for the Raspberry Pi, so it needs to be compiled from source, which takes quite some time with the Raspberry Pi.

```
sudo apt-get install libxext
curl -O https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
tar -zxvf SDL2-2.0.3.tar.gz 
cd SDL2-2.0.3/
./configure && make && sudo make install
```

`SDL_gfx` can be installed with

```
git clone git@github.com:thp/SDL_gfx.git
cd SDL_gfx/
./configure && make && sudo make install
```

# Build hardware version

Run 

```
make hardware
```

to compile the executables to run on the actual hardware. The executables need `sudo` for accessing the lower level hardware.

# Simulator

The HEXXX source code comes with a simulator based on SDL, on which you can simulate LEDs and button presses. 

Keys are simulated with V,B for player 0 (bottom), O,P for player 1 (top left) and Q, W for player 2 (top right).

In order to compile the SDL example, run

```
make simulator
```

which generates a bunch of `*_simulator` executables.

## How the simulator works

The interface (and main loop of the programs) defined in `hexxx.h` is implemented in `hexxx.cpp` to work on the Raspberry Pi only, because it tracks GPIO for button presses and uses Raspberry Pi-only hardware to light the LEDs. The rest of the whole framework is hardware independent. 

The alternative `hexxx_simulator.cpp` also implements the `hexxx.h` interface, but contains calls to SDL to handle graphics and button presses. Linking your application with `hexxx.o` and hardware-related libraries makes it run on the hardware, while linking with `hexxx_simulator.o` and the SDL library provides us with a simulated version of the HEXXX application.

## Gamma error

The simulator also support erroneous LED illumination with a faked Gamma error. The library in `color.h` supports Gamma correction, but it needs to be used pro-actively (except when using video buffers as in `buffer.h`, which handles Gamma correction upon copying to the actual screen).