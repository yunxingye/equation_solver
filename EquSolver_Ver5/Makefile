CC = g++
LD = g++
#CFLAGS = -Wall -pthread -ggdb3 -O0 -std=c++11 
CFLAGS = -Wall -pthread -ggdb3 -std=c++11 
SRCS = *.cpp 
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	#$(LD) -o equaSolver $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIB)
	$(LD) -o equaSolver $(CFLAGS) $(OBJS) 

%.o: %.c
	#$(CC) $(CFLAGS) $(INCLUDE) -o $@ -cpp $<
	$(CC) $(CFLAGS)  -o $@ -cpp $<

clean:	
	rm -f *.o *~ ./../../lib/*.o ./../../lib/*~ \
	./../*.o ./equaSolver 


