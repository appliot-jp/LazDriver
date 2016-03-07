CC=gcc
CFLAGS= -g -c -DIEEE_HEADR_TEST
CFILES=test.c ieee802154e.c
COBJS=$(CFILES:.c=.o)

.c.o: 
	$(CC) $(CFLAGS) $<

program: $(COBJS) 
	$(CC) -o test $(COBJS)

clean:
	\rm *.o
