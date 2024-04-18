CFLAGS = -Wall

# build all .c files in this directory
SRC=$(wildcard *.c)

solution: $(SRC)
	gcc -pthread -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm solution
