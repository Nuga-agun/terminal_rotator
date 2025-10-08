#include <stdio.h>

#define GRID_SIZE 20
#define EMPTY_CHAR ' '

void draw_grid(char grid[GRID_SIZE][GRID_SIZE]) {
	for (int i=0; i<GRID_SIZE; i++) {
		for (int j=0; j<GRID_SIZE; j++) {
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
}

void init_grid(char grid[GRID_SIZE][GRID_SIZE]) {
	for (int i=0; i<GRID_SIZE; i++) {
		for (int j=0; j<GRID_SIZE; j++) {
			grid[i][j] = EMPTY_CHAR;
		}
	}
}

int main(int argc, char *argv[]) {
	char grid[GRID_SIZE][GRID_SIZE];

	init_grid(grid);
	draw_grid(grid);

	return 0;
}
