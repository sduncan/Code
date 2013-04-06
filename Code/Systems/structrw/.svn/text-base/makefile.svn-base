DOT-OHS = mcguffin.o structrw.o

lezdoit: $(DOT-OHS)
	gcc -o structrw $(DOT-OHS)

mcguffin.o: mcguffin.c mcguffin.h
	gcc -c mcguffin.c

structrw.o: structrw.c mcguffin.h
	gcc -c structrw.c

clean:
	rm $(DOT-OHS)
	rm *~