CC=gcc

all: 
	$(CC) -o password-manager main.c `pkg-config --cflags --libs gtk4`

run:
	./password-manager

clean:
	rm -f password-manager