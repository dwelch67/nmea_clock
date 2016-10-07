
all : test_long test_short make_time

test_long : test_long.c nmea_long.c
	gcc -O2 test_long.c nmea_long.c -o test_long

test_short : test_short.c nmea_short.c
	gcc -O2 test_short.c nmea_short.c -o test_short

make_time : make_time.c
	gcc -O2 make_time.c -o make_time

clean :
	rm -f test_short
	rm -f test_long
	rm -f make_time
	rm -f *.dat

