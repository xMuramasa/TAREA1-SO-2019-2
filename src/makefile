CC=gcc
CFLAGS=-I.
DEPS = ../include/headerFile.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

out: obj/main.o obj/functions.o 
	$(CC) -o out obj/main.o obj/functions.o 

clean:
	rm -f obj/* *~ core $(INCDIR)/*~ 

run:
	./out