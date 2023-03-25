CC=g++
CFLAGS=-Wall -Wextra -g -O3 -c
OBJECTS=expression.o main.o 

calculator.o: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o : %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

test: calculator.o
	gdb -ex run calculator.o

clean:
	rm *.o
