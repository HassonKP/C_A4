all:    a4.c
	gcc -Wall -g -o a4 a4.c -lm
clean:
	rm -f $(PROGS) *.o ~* *.log

