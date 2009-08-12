CC=gcc
CFLAGS=-Wall -O3 -dynamiclib

OBJ=activesupport.o
TARGET=libactivesupport.dylib

$(TARGET):$(OBJ) $(HDR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) 

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)
