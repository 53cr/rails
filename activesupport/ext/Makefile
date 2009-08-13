CC=gcc
CFLAGS=-Wall -O3
TARGETFLAGS=-dynamiclib

OBJ= \
	inflector.o \
	core_ext/string/starts_ends_with.o \
	core_ext/string/filters.o \
	core_ext/string/access.o

HDR= \
	activesupport.h \
	inflector.h \
	core_ext/string/starts_ends_with.h \
	core_ext/string/filters.h \
	core_ext/string/access.h

TEST_OBJ= activesupport_test.o
TEST_TARGET= activesupport_test

TARGET=libactivesupport.dylib

$(TARGET):$(OBJ) $(HDR)
	$(CC) $(CFLAGS) $(TARGETFLAGS) $(OBJ) -o $(TARGET) 

test:$(OBJ) $(HDR) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(OBJ) -o $(TEST_TARGET)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	rm -f $(TARGET)
