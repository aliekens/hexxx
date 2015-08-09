TARGETS = example tron screengrab fontdemo

all: $(TARGETS)

OBJS = hexxx.o ledstring.o color.o buttons.o coordinates.o font.o players.o
LIBS = ws2811/libws2811.a gpio/gpio.a -lX11
CPPFLAGS = -std=c++0x -O2

$(LIBS): force_look
	cd ws2811 ; make
	cd gpio ; make

example: $(LIBS) $(OBJS) example.o
	g++ $(CPPFLAGS) -o example example.o $(OBJS) $(LIBS) -pthread

tron: $(LIBS) $(OBJS) tron.o
	g++ $(CPPFLAGS) -o tron tron.o $(OBJS) $(LIBS) -pthread

screengrab: $(LIBS) $(OBJS) screengrab.o
	g++ $(CPPFLAGS) -o screengrab screengrab.o $(OBJS) $(LIBS) -pthread

fontdemo: $(LIBS) $(OBJS) fontdemo.o
	g++ $(CPPFLAGS) -o fontdemo fontdemo.o $(OBJS) $(LIBS) -pthread

clean:
	@rm -vf *.o *.a $(TARGETS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

force_look :
	true
