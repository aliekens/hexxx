TARGETS = example tron screengrab fontdemo

all: $(TARGETS)

OBJS = hexxx.o ledstring.o color.o buttons.o coordinates.o font.o
LIBS = ws2811/libws2811.a gpio/gpio.a -lX11
CPPFLAGS = -std=c++0x -O2

$(LIBS): force_look
	cd ws2811 ; make
	cd gpio ; make

example: example.o $(OBJS) $(LIBS)
	g++ $(CPPFLAGS) -o example example.o $(OBJS) $(LIBS) -pthread

tron: tron.o $(OBJS) $(LIBS)
	g++ $(CPPFLAGS) -o tron tron.o $(OBJS) $(LIBS) -pthread

screengrab: screengrab.o $(OBJS) $(LIBS)
	g++ $(CPPFLAGS) -o screengrab screengrab.o $(OBJS) $(LIBS) -pthread

fontdemo: fontdemo.o $(OBJS) $(LIBS)
	g++ $(CPPFLAGS) -o fontdemo fontdemo.o $(OBJS) $(LIBS) -pthread

clean:
	@rm -vf *.o *.a $(TARGETS)

distclean: clean
	make clean -C ws2811
	make clean -C gpio

force_look :
	true
