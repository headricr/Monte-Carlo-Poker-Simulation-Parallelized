
#got some help from http://www.puxan.com/web/howto-write-generic-makefiles/
CC=mpicc
CFLAGS=-I. -fopenmp
LDFLAGS= -fopenmp
USEMATH = -lm
TIMEFLAGS = -DTIME

#EXEC = hello
OBJECTS = $(SOURCES:.c=.o)
SOURCES = $(wildcard *.c)
BINS=$(SOURCES:.c=)  #to compile a target, compile its c


# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


all: $(BINS)

poker: card.o hand.o deck.o serial.o parallel.o parallel-mp.o cardtests.o
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(USEMATH)

poker-time: card.o hand.o deck.o serial.o parallel.o parallel-mp.o cardtests.o
	$(CC) $(LDFLAGS) $(TIMEFLAGS) $(OBJECTS) -o $@ $(USEMATH)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXEC) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
