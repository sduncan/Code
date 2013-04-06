DOT-OHS = shell.o seashell.o

nutshell: $(DOT-OHS)
	gcc -o seashell $(DOT-OHS)

shell.o: shell.c shell.h
	gcc -c shell.c

clean:
	rm $(DOT-OHS)
	rm *~