# HEXXX

HEXXX is a DIY 3-player console with a hexagonal grid of 400 RGB LEDs, 6 game buttons, and based on a Raspberry Pi. HEXXX is being built at http://opengarage.org

The repository contains various demos, such as Pong and Tron for three, Flappybird for 6, a X11 screengrabber and a cube demo.

It also contains a sample application in `example.cpp` that shows how to build your own HEXXX apps.

# Prerequisites

## X11

X11 is mianly required for the `screengrab` example. Install `libx11-dev` with

```sudo apt-get install libx11-dev```

## SDL

For the simulator, you'll need SDL2 (http://libsdl.org) and `SDL_gfx` for SDL2 (https://github.com/thp/SDL_gfx). To check whether you have SDL, run `sdl2-config`, which should be an existing executable.

LibSDL2 can be downloaded from https://www.libsdl.org/download-2.0.php, with binaries for your Mac or Windows development machine

Note that SDL2 isn't available as an apt package for the Raspberry Pi, so it needs to be compiled from source, which takes quite some time with the Raspberry Pi.

```
sudo apt-get install libxext
curl -O https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
tar -zxvf SDL2-2.0.3.tar.gz 
cd SDL2-2.0.3/
./configure && make && make install
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

The HEXXX source code comes with a simulator based on SDL. Only `hexxx.cpp` is replaced with a `hexxx_simulator.cpp`. When either `hexxx.o` or `hexxx_simulator.o` is linked with the application object all other objects, the game runs in SDL. 

Keys are simulated with V,B for player 0, O,P for player 1 and Q, W for player 3.

In order to compile the SDL example, run

```
make simulator
```

which generates a bunch of `*_simulator` executables.

