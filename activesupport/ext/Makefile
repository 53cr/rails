CC=gcc
CFLAGS=-Wall -O3 -dynamiclib

OBJ=activesupport.o inflector.o starts_ends_with.o filters.o access.o
HDR=inflector.h starts_ends_with.h filters.h access.h
TARGET=libactivesupport.dylib

$(TARGET):$(OBJ) $(HDR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) 

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)
