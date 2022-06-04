CC=gcc

.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: clean-build

all: setup password-manager

setup: clean-build
	mkdir build

password-manager: build/password-manager.o build/csv.o linking

build/password-manager.o:
	$(CC) -c -g -o build/password-manager.o main.c `pkg-config --cflags --libs gtk4`

build/csv.o:
	$(CC) -c -g -o build/csv.o libs/csv.c 

linking:
	$(CC) -o password-manager build/csv.o build/password-manager.o `pkg-config --cflags --libs gtk4`
	rm -rf build

clean-build:
	rm -rf build


run:
	./password-manager

clean:
	rm -f password-manager