build:
	gcc -o tema1 main.c functii.c
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1