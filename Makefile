start: ./commands/rm ./commands/mkdir ./commands/ls ./commands/cat ./commands/date shell.c
	gcc -o shell shell.c
./commands/rm: ./commands/rm.c
	gcc -o ./commands/rm ./commands/rm.c
./commands/cat: ./commands/cat.c
	gcc -o ./commands/cat ./commands/cat.c
./commands/ls: ./commands/ls.c
	gcc -o ./commands/ls ./commands/ls.c
./commands/date: ./commands/date.c
	gcc -o ./commands/date ./commands/date.c
./commands/mkdir: ./commands/mkdir.c
	gcc -o ./commands/mkdir ./commands/mkdir.c
all: 
	gcc -o shell shell.c
	gcc -o ./commands/ls ./commands/ls.c
	gcc -o ./commands/date ./commands/date.c
	gcc -o ./commands/cat ./commands/cat.c
	gcc -o ./commands/rm ./commands/rm.c
	gcc -o ./commands/mkdir ./commands/mkdir.c
clean:
	rm -rf shell ./commands/ls ./commands/date ./commands/date ./commands/rm ./commands/mkdir