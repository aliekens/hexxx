all: tron

OBJS = hexxx.o ledstring.o color.o buttons.o coordinates.o
LIBS = ws2811/libws2811.a gpio/gpio.a 
CPPFLAGS = -std=c++0x -O2

tron: tron.o $(OBJS)
	g++ $(CPPFLAGS) -o tron tron.o $(OBJS) $(LIBS) -pthread

clean:
	@rm -vf *.o *.a hexxx

distclean: clean
	make clean -C ws2811
