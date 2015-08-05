hexxx: main.o ledstring.o color.o
	g++ -std=c++0x -o hexxx main.o ledstring.o color.o ws2811/libws2811.a gpio/gpio.a -pthread -O2 

main.o: main.cpp
	g++ -std=c++0x -o main.o -c -g -O2 main.cpp

%.o: %.c %.h 
	gcc -o $@ -c -g -O2 $<

%.o: %.cpp %.h 
	g++ -std=c++0x -std=c++0x -o $@ -c -g -O2 $<

clean:
	@rm -vf *.o *.a hexxx

distclean: clean
	make clean -C ws2811
