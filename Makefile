TARGETS = hardware simulator

all: $(TARGETS)

hardware: example tron screengrab fontdemo cube flappybird pong

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
	g++ `sdl2-config --cflags` $(CXXFLAGS) -c -o hexxx_simulator.o hexxx_simulator.cpp

example: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) example.o
	g++ $(CXXFLAGS) -o example example.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

example_simulator: $(SIMULATOR_OBJECTS) example.o
	g++ $(CXXFLAGS) -o example_simulator example.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

tron: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) tron.o
	g++ $(CXXFLAGS) -o tron tron.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

tron_simulator: $(SIMULATOR_OBJECTS) tron.o
	g++ $(CXXFLAGS) -o tron_simulator tron.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

screengrab: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) screengrab.o
	g++ $(CXXFLAGS) -o screengrab screengrab.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

fontdemo: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) fontdemo.o
	g++ $(CXXFLAGS) -o fontdemo fontdemo.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

cube: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) cube.o
	g++ $(CXXFLAGS) -o cube cube.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

cube_simulator: $(SIMULATOR_OBJECTS) cube.o
	g++ $(CXXFLAGS) -o cube_simulator cube.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

flappybird: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) flappybird.o
	g++ $(CXXFLAGS) -o flappybird flappybird.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

flappybird_simulator: $(SIMULATOR_OBJECTS) flappybird.o
	g++ $(CXXFLAGS) -o flappybird_simulator flappybird.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

pong: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) pong.o
	g++ $(CXXFLAGS) -o pong pong.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

pong_simulator: $(SIMULATOR_OBJECTS) pong.o
	g++ $(CXXFLAGS) -o pong_simulator pong.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

clean:
	@rm -vf *.o *.a $(TARGETS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

force_look :
	true
