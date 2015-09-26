TARGETS = hardware simulator

all: $(TARGETS)

hardware: example tron screengrab fontdemo cube flappybird dogfight vectors pong

simulator: example_simulator

COMMON_OBJECTS = ledstring.o color.o buttons.o coordinates.o font.o players.o vector.o coordinate.o line.o circle.o buffer.o
HARDWARE_OBJECTS = hexxx.o $(COMMON_OBJECTS)
SIMULATOR_OBJECTS = hexxx_simulator.o $(COMMON_OBJECTS)

HARDWARE_LIBS = ws2811/libws2811.a gpio/gpio.a -lX11

#CPPFLAGS = -std=c++0x -O2
#CFLAGS = -O2

$(HARDWARE_LIBS): force_look
	cd ws2811 ; make
	cd gpio ; make

example: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) example.o
	g++ $(CPPFLAGS) -o example example.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

example_simulator: $(SIMULATOR_LIBS) $(SIMULATOR_OBJECTS) example.o
	g++ $(CPPFLAGS) -o example_simulator example.o $(SIMULATOR_OBJECTS) $(SIMULATOR_LIBS) -lpthread

tron: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) tron.o
	g++ $(CPPFLAGS) -o tron tron.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

screengrab: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) screengrab.o
	g++ $(CPPFLAGS) -o screengrab screengrab.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

fontdemo: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) fontdemo.o
	g++ $(CPPFLAGS) -o fontdemo fontdemo.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

cube: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) cube.o
	g++ $(CPPFLAGS) -o cube cube.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

flappybird: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) flappybird.o
	g++ $(CPPFLAGS) -o flappybird flappybird.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

dogfight: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) dogfight.o
	g++ $(CPPFLAGS) -o dogfight dogfight.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

vectors: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) vectors.o
	g++ $(CPPFLAGS) -o vectors vectors.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

pong: $(HARDWARE_LIBS) $(HARDWARE_OBJECTS) pong.o
	g++ $(CPPFLAGS) -o pong pong.o $(HARDWARE_OBJECTS) $(HARDWARE_LIBS) -pthread

clean:
	@rm -vf *.o *.a $(TARGETS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

force_look :
	true
