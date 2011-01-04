CFLAGS = -dynamiclib
LDFLAGS = -L/usr/lib -lcurl
lib2ch.dylib : lib2ch.c connection.c
    gcc -o lib2ch.dylib lib2ch.c connection.c