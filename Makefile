CC=gcc

.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: clean-build

all: setup password-manager

setup: clean-build
	mkdir build

password-manager: build/password-manager.o build/encryption.o build/csv.o linking

build/password-manager.o:
	$(CC) -c -g -o build/password-manager.o main.c `pkg-config --cflags --libs gtk4 libsodium`

build/encryption.o:
	$(CC) -c -g -o build/encryption.o libs/encryption.c `pkg-config --cflags --libs libsodium`


build/csv.o:
	$(CC) -c -g -o build/csv.o libs/csv.c 

linking:
	$(CC) -o password-manager build/csv.o build/password-manager.o build/encryption.o `pkg-config --cflags --libs gtk4 libsodium`
	rm -rf build

clean-build:
	rm -rf build


run:
	./password-manager

clean:
	rm -f password-manager


windows:
	mkdir build
	gcc.exe -c -g main.c -o ./build/password-manager.o -mwindows -mfpmath=sse -msse -msse2 -mms-bitfields -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/lzo -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lgtk-4 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -IC:/msys64/mingw64/include -L/c/Users/Vincent/Downloads/libsodium-stable/libsodium-stable/libsodium-win64/lib -lsodium
	gcc.exe -c -g -o ./build/encryption.o ./libs/encryption.c -mwindows -mfpmath=sse -msse -msse2 -mms-bitfields -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/lzo -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lgtk-4 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -IC:/msys64/mingw64/include -L/c/Users/Vincent/Downloads/libsodium-stable/libsodium-stable/libsodium-win64/lib -lsodium
	gcc.exe -c -g -o ./build/csv.o ./libs/csv.c 
	gcc.exe -o password-manager.exe ./build/csv.o ./build/password-manager.o ./build/encryption.o -mwindows -mfpmath=sse -msse -msse2 -mms-bitfields -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/lzo -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lgtk-4 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -IC:/msys64/mingw64/include -L/c/Users/Vincent/Downloads/libsodium-stable/libsodium-stable/libsodium-win64/lib -lsodium
	rm -rf build
