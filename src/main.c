#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define GRID_SIZE 50
#define EMPTY_CHAR ' '
#define LEN_INPUT GRID_SIZE/2 
#define REFRESH_DELAY 100000
#define ROTATION_PER_SECOND 0.5
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

int write_in_grid(struct point p, char grid[GRID_SIZE][GRID_SIZE]) {
	int i = (int) p.y + GRID_SIZE/2;
	int j = (int) p.x + GRID_SIZE/2;
	if (i>=GRID_SIZE || j>=GRID_SIZE) {
		return 1;
	}
	grid[i][j] = p.letter;
	return 0;
}

int main(int argc, char *argv[]) {
	char grid[GRID_SIZE][GRID_SIZE];
	char user_input[LEN_INPUT];
	char buffer[LEN_INPUT];

	printf("Entrez le texte à animer : ");
	scanf("%[^\n]", user_input);
	struct point message_points[LEN_INPUT];
	for (int index=0; index<LEN_INPUT; index++) {
		message_points[index].x = index;
		message_points[index].y = 0;
		message_points[index].letter = user_input[index];
	}

	while (1) {
		clear_screen();
		init_grid(grid);

		for (int index=0; index<LEN_INPUT; index++) {
			float old_x = message_points[index].x;
			float old_y = message_points[index].y;
			message_points[index].x = old_x * cos(ANGLE) - old_y * sin(ANGLE);
			message_points[index].y = old_x * sin(ANGLE) + old_y * cos(ANGLE);
			if (write_in_grid(message_points[index], grid) != 0) {
				return 1;
			}
		}

		draw_grid(grid);
		usleep(REFRESH_DELAY);
	}

	return 0;
}
