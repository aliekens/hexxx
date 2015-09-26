# HEXXX

HEXXX is a DIY 3-player console with a hexagonal grid of 400 RGB LEDs, 6 game buttons, and based on a Raspberry Pi. HEXXX is being built at http://opengarage.org

# Prerequisites

Install libx11-dev

```sudo apt-get install libx11-dev```

For the simulator, you'll need SDL2 (http://libsdl.org). To check whether you have it, run `sdl2-config`.

# Actual version

Run 

```
make hardware
```

to compile the executables to run on the actual hardware.

# Simulator

The HEXXX source code comes with a simulator based on SDL. Only `hexxx.cpp` is replaced with a `hexxx_simulator.cpp`. When either `hexxx.o` or `hexxx_simulator.o` is linked with the application object all other objects, the game runs in SDL. 

Keys are simulated with V,B for player 0, O,P for player 1 and Q, W for player 3.

In order to compile the SDL example, run

```
make simulator
```

which generates a bunch of `*_simulator` executables.

