
all : test_long test_short

test_long : test_long.c nmea_long.c
	gcc -O2 test_long.c nmea_long.c -o test_long

test_short : test_short.c nmea_short.c
	gcc -O2 test_short.c nmea_short.c -o test_short

clean :
	rm -f test_short
	rm -f test_long

