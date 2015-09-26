TARGETS = hardware simulator

all: $(TARGETS)

hardware: example tron screengrab fontdemo cube flappybird vectors pong

simulator: example_simulator tron_simulator cube_simulator flappybird_simulator pong_simulator

COMMON_OBJECTS = ledstring.o color.o buttons.o coordinates.o font.o players.o vector.o coordinate.o line.o circle.o buffer.o
HARDWARE_OBJECTS = hexxx.o $(COMMON_OBJECTS)
SIMULATOR_OBJECTS = hexxx_simulator.o $(COMMON_OBJECTS)

HARDWARE_LIBS = ws2811/libws2811.a gpio/gpio.a -lX11
SIMULATOR_LIBS=`sdl2-config --libs` -lSDL2_gfx

CXXFLAGS = -std=c++0x -O3
CPPFLAGS = -O3

$(HARDWARE_LIBS): force_look
	cd ws2811 ; make
	cd gpio ; make

hexxx_simulator.o: hexxx_simulator.cpp
	g++ `sdl2-config --cflags` -O3 -c -o hexxx_simulator.o hexxx_simulator.cpp

example: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) example.o
	g++ $(CPPFLAGS) -o example example.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

example_simulator: $(SIMULATOR_OBJECTS) example.o
	g++ $(CPPFLAGS) -o example_simulator example.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

tron: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) tron.o
	g++ $(CPPFLAGS) -o tron tron.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

tron_simulator: $(SIMULATOR_OBJECTS) tron.o
	g++ $(CPPFLAGS) -o tron_simulator tron.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

screengrab: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) screengrab.o
	g++ $(CPPFLAGS) -o screengrab screengrab.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

fontdemo: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) fontdemo.o
	g++ $(CPPFLAGS) -o fontdemo fontdemo.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

cube: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) cube.o
	g++ $(CPPFLAGS) -o cube cube.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

cube_simulator: $(SIMULATOR_OBJECTS) cube.o
	g++ $(CPPFLAGS) -o cube_simulator cube.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

flappybird: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) flappybird.o
	g++ $(CPPFLAGS) -o flappybird flappybird.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

flappybird_simulator: $(SIMULATOR_OBJECTS) flappybird.o
	g++ $(CPPFLAGS) -o flappybird_simulator flappybird.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

pong: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) pong.o
	g++ $(CPPFLAGS) -o pong pong.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

pong_simulator: $(SIMULATOR_OBJECTS) pong.o
	g++ $(CPPFLAGS) -o pong_simulator pong.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

clean:
	@rm -vf *.o *.a $(TARGETS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

force_look :
	true
