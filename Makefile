FLAGS = -Wall -Wextra -g
SOURCES = src/main.c src/worker.c src/ipc_manager.c

all: pi_sim

pi_sim: src/main.o src/ipc_manager.o src/worker.o
	gcc $(FLAGS) -o $@ $^

%.o: %.c include/types.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o pi_sim
