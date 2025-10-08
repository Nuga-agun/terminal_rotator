#include <stdio.h>

#define GRID_SIZE 20
#define EMPTY_CHAR ' '
#define MAX_LENGTH_INPUT 10

void clear_screen() {
	printf("\033[2J\033[1;1H");
}

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
	char user_input[MAX_LENGTH_INPUT];
	char buffer[MAX_LENGTH_INPUT];

	init_grid(grid);
	printf("Entrez le texte à animer : ");
	scanf("%[^\n]", user_input);
	int middle_index = GRID_SIZE/2;
	for (int j=0; j<MAX_LENGTH_INPUT; j++) {
		grid[middle_index][j + middle_index] = user_input[j];
	}

	clear_screen();
	draw_grid(grid);

	return 0;
}
