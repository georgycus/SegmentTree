SegTree_TARGET = ./SegTree

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 -g

CLEAN = rm *.o
 
.PHONY: default all clean
 
default: $(SegTree_TARGET) $(matriz_TARGET)
all: default
 
SegTree_OBJECTS = $(patsubst %.c, %.o, SegTree.c main.c)
SegTree_HEADERS = $(T.h SegTree.h)
 
%.o: %.c $(SegTree_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
   
.PRECIOUS: $(SegTree_TARGET) $(SegTree_OBJECTS) $(matriz_TARGET) $(matriz_OBJECTS)
 
$(SegTree_TARGET): $(SegTree_OBJECTS)
	$(CC) $(SegTree_OBJECTS) -o $@
     
     
clean:
	$(CLEAN)
