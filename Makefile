CC = gcc
CFLAGS = 
LIBS = -lcurl

SRCS := $(wildcard *.c)
EXES := $(patsubst %.c,%,$(SRCS))

.PHONY: all clean

all: $(EXES)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(EXES)
