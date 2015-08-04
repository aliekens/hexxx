hexxx: main.o
	g++ -o hexxx main.o ws2811/libws2811.a -O2

main.o: main.cpp
	g++ -o main.o -c -g -O2 main.cpp

%.o: %.c %.h 
	gcc -o $@ -c -g -O2 $<

%.o: %.cpp %.h 
	g++ -o $@ -c -g -O2 $<

clean:
	@rm -vf *.o *.a hexxx

distclean: clean
	make clean -C ws2811
