CC ?= gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LIBS = sdl3 sdl3-image
LDCFLAGS = `pkg-config --cflags $(LIBS)`
LDLIBS = `pkg-config --libs $(LIBS)`

SRC = main.c  jsi.c keypress.c events.c
OBJS = $(SRC:.c=.o)
BIN = jsi

.PHONY: all
all: $(BIN)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS)-c $(SRC)

$(BIN): $(OBJS)
	$(CC) $(LDLIBS) $(OBJS) -o $(BIN)
	
.PHONY: clean
clean:
	rm $(BIN) $(OBJS)
