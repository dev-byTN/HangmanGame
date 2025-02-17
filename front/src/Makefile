EXEC = hangMan

SRC = front.c

CFLAGS = -Wall

LDFLAGS = -lraylib

all: $(EXEC)

$(EXEC): $(SRC)
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXEC)

