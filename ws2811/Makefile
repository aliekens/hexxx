libws2811.a: ws2811.o pwm.o dma.o board_info.o mailbox.o
	ar rc libws2811.a ws2811.o pwm.o dma.o board_info.o mailbox.o
	ranlib libws2811.a

%.o: %.c %.h 
	gcc -o $@ -c -g -O2 $<

clean:
	rm -rf *.o *.a test