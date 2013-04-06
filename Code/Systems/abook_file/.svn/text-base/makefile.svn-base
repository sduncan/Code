DOT-OHS = linklist.o addressbook.o adbook.o

happyfuntime: $(DOT-OHS)
	gcc -o adbook $(DOT-OHS)

linklist.o: linklist.c linklist.h
	gcc -c linklist.c

addressbook.o: addressbook.c addressbook.h linklist.h
	gcc -c addressbook.c

adbook.o: adbook.c addressbook.h linklist.h
	gcc -c adbook.c

clean:
	rm $(DOT-OHS)
	rm *~