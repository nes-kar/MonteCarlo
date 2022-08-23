CC=gcc
OPTIONS=-g -Wall
LIBS=-lm

OBJ=main.o  newPositions.o  plummer.o  potentials.o  relaxation.o

ALL: MCsim

MCsim: $(OBJ)
	$(CC) $(OPTIONS) $(OBJ) -o MCsim $(LIBS)

%.o: %.c 
	$(CC) $(OPTIONS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ) MCsim
