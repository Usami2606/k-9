BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= ompsum.c  # default ompsum.c

run:
	mkdir -p $(BIN_DIR)
	gcc -fopenmp -o $(TARGET) $(FILE) -lm

clean:
	rm -rf $(BIN_DIR)
