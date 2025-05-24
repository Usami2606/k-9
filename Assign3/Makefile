BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= allgather.c


run:
	mkdir -p $(BIN_DIR)
	mpicc -Wall -o $(TARGET) $(FILE)

clean:
	rm -rf $(BIN_DIR)
	rm -rf report