APPS 	            = pong example tron screengrab fontdemo cube flappybird pong
HARDWARE_APPS     = $(addsuffix _hardware, $(APPS))
SIMULATOR_APPS    = $(addsuffix _simulator, $(filter-out screengrab,$(APPS)))

CXX               = g++
CC                = gcc
CXXFLAGS          = -std=c++0x `sdl2-config --cflags`
CPPFLAGS          = -O3

COMMON_OBJECTS    = ledstring.o color.o buttons.o coordinates.o font.o players.o vector.o coordinate.o line.o circle.o buffer.o
HARDWARE_OBJECTS  = hexxx.o $(COMMON_OBJECTS)
SIMULATOR_OBJECTS = hexxx_simulator.o $(COMMON_OBJECTS)

HARDWARE_LIBS     = ws2811/libws2811.a gpio/gpio.a -lX11
SIMULATOR_LIBS    = `sdl2-config --libs` -lSDL2_gfx

all: hardware simulator

hardware: $(HARDWARE_APPS)
simulator: $(SIMULATOR_APPS)

%_simulator: %.o $(SIMULATOR_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

$(HARDWARE_LIBS):
	cd ws2811 ; make
	cd gpio ; make

%_hardware: %.o $(HARDWARE_LIBS) $(HARDWARE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

clean:
	@rm -vf *.o *.a $(HARDWARE_APPS) $(SIMULATOR_APPS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

.PRECIOUS: %.o 