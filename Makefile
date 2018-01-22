all: 
	gcc -o shell shell.c
	gcc -o ./commands/ls ./commands/ls.c
clean:
	rm -rf shell ./commands/ls