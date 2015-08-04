test: gpio.a main.o
	g++ -o test main.o gpio.a -O2

main.o: main.cpp
	g++ -o main.o -c -g -O2 main.cpp

gpio.a: gpio.o
	ar rc gpio.a gpio.o
	ranlib gpio.a

%.o: %.c %.h 
	gcc -o $@ -c -g -O2 $<

clean:
	rm -rf *.o *.a test