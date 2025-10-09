#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define GRID_SIZE 50
#define EMPTY_CHAR ' '
#define REFRESH_DELAY 1000000
#define ROTATION_PER_SECOND 0.25
#define ANGLE (2*M_PI * ROTATION_PER_SECOND * REFRESH_DELAY/1000000)

struct point{
	float x;
	float y;
	char letter;
};

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

void write_in_grid(struct point p, char grid[GRID_SIZE][GRID_SIZE]) {
	float i = p.y + GRID_SIZE/2;
	float j = p.x + GRID_SIZE/2;
	if (i>=0 && i<GRID_SIZE && j>=0 && j<GRID_SIZE) {
		grid[(int) round(i)][(int) round(j)] = p.letter;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage : rotator MESSAGE");
		return 1;
	}
	int len_input = strlen(argv[1]);
	char grid[GRID_SIZE][GRID_SIZE];
	struct point message_points[strlen(argv[1])];
	for (int index=0; index<len_input; index++) {
		message_points[index].x = index;
		message_points[index].y = 0;
		message_points[index].letter = argv[1][index];
	}

	while (1) {
		clear_screen();
		init_grid(grid);

		for (int index=0; index<len_input; index++) {
			float old_x = message_points[index].x;
			float old_y = message_points[index].y;
			message_points[index].x = old_x * cos(ANGLE) - old_y * sin(ANGLE);
			message_points[index].y = old_x * sin(ANGLE) + old_y * cos(ANGLE);
			write_in_grid(message_points[index], grid);
		}

		draw_grid(grid);
		usleep(REFRESH_DELAY);
	}

	return 0;
}
