all: archives login

clean:
	rm -f archives
	rm -f login

archives:
	gcc -o archives point1.c -Wall

login:
	gcc -o login point2.c -Wall
