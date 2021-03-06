CC := gcc
WARNINGS := -Wall -Werror
FLAGS := $(WARNINGS) --std=gnu99 -DDEBUG

OBJECTS := instructions.o

simulator: $(OBJECTS) main.c
	$(CC) $(FLAGS) $< main.c -o simulator

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f *.o simulator
