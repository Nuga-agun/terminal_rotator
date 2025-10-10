#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define GRID_SIZE 50
#define EMPTY_CHAR ' '
#define REFRESH_DELAY 200000
#define ROTATION_PER_SECOND 0.75
#define ANGLE (2*M_PI * ROTATION_PER_SECOND * REFRESH_DELAY/1000000)

struct point{
	float x;
	float y;
	char letter;
};

void clear_screen() {
	system("clear");
}

void draw_grid(const char grid[GRID_SIZE][GRID_SIZE]) {
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

void write_in_grid(const struct point p, char grid[GRID_SIZE][GRID_SIZE]) {
	float i = p.y + GRID_SIZE/2;
	float j = p.x + GRID_SIZE/2;
	if (i>=0 && i<GRID_SIZE && j>=0 && j<GRID_SIZE) {
		grid[(int) round(i)][(int) round(j)] = p.letter;
	}
}

int main(int argc, char* restrict argv[]) {
	if (argc != 2) {
		printf("Usage : rotator MESSAGE");
		return 1;
	}
	int len_input = strlen(argv[1]);
	if (len_input >= GRID_SIZE) {
		printf("Message is too long to be displayed");
	}

	char grid[GRID_SIZE][GRID_SIZE];
	struct point message_points[len_input];
	for (int msg_index=0; msg_index<len_input; msg_index++) {
		message_points[msg_index].x = msg_index;
		message_points[msg_index].y = 0;
		message_points[msg_index].letter = argv[1][msg_index];
	}

	while (1) {
		clear_screen();
		init_grid(grid);

		float cos_angle = cos(ANGLE);
		float sin_angle = sin(ANGLE);
		for (int msg_index=0; msg_index<len_input; msg_index++) {
			float old_x = message_points[msg_index].x;
			float old_y = message_points[msg_index].y;
			message_points[msg_index].x = old_x * cos_angle - old_y * sin_angle;
			message_points[msg_index].y = old_x * sin_angle + old_y * cos_angle;
			write_in_grid(message_points[msg_index], grid);
		}

		draw_grid(grid);
		usleep(REFRESH_DELAY);
	}

	return 0;
}


