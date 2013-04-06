DOT-OHS = stack.o queue.o main.o

happyfuntimewoo: $(DOT-OHS)
	gcc -o main $(DOT-OHS)

stack.o: stack.c stack.h
	gcc -c stack.c

queue.o: queue.h queue.c
	gcc -c queue.c

main.o: main.c stack.h queue.h
	gcc -c main.c

clean:
	rm $(DOT-OHS)
	rm *~