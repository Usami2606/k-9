BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= grav_hybrid.c  

run:
	mkdir -p $(BIN_DIR)
	mpicc -fopenmp -o $(TARGET) $(FILE) -lm

clean:
	rm -rf $(BIN_DIR)
	rm -rf ./grav_data/result1000
	rm -rf ./report