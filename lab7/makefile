grid_test: grid.c main.c
	gcc -g -std=c99 -Wall -Werror -c grid.c -o grid.o
	gcc -g -std=c99 -Wall -Werror -c main.c -o main.o
	gcc -g -std=c99 -Wall -Werror main.o grid.o grid_provided.o -o grid

clean:
	rm grid.o
	rm main.o
	rm grid
	rm sol_*

grid1: grid_test
	./grid grid1.txt sol_grid1.txt

grid2: grid_test
	./grid grid2.txt sol_grid2.txt

grid3: grid_test
	./grid grid3.txt sol_grid3.txt

all:
	$(MAKE) main.c
