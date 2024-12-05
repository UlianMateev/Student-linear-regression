#pragma once
#include<raylib.h>

#define WIDTH 1000
#define HEIGHT 1000

void plot_graph() {

	int origin_x = WIDTH / 10;
	int origin_y = HEIGHT - (HEIGHT / 10);

	DrawLine(origin_x, origin_y, origin_x, HEIGHT / 10, BLACK);
	DrawLine(origin_x, origin_y, WIDTH - (WIDTH / 10), origin_y, BLACK);
	DrawCircle(origin_x, 100, 4, BLACK);
	DrawCircle(origin_x, 300, 4, BLACK);
	DrawCircle(origin_x, 500, 4, BLACK);
	DrawCircle(origin_x, 700, 4, BLACK);


	DrawCircle(1 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
	DrawCircle(2 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
	DrawCircle(3 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
	DrawCircle(4 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
	DrawCircle(5 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
	DrawCircle(6 * 133 + 100, HEIGHT - (HEIGHT / 10), 4, BLACK);
}

void plot_data_points_train(float data_x, float data_y) {

	data_x *= 10;
	data_y *= 10;

	int x = ((static_cast<int>(data_x) - 40) * 133) / 10 + 100;
	int y = (HEIGHT - (HEIGHT / 10)) - (static_cast<int>(data_y) * 20);
	int r = 4;

	DrawCircle(x, y, r, BLUE);
}

void plot_data_points_test(float data_x, float data_y) {

	data_x *= 10;
	data_y *= 10;

	int x = (((static_cast<int>(data_x) - 40) * 133) / 10) + 100;
	int y = (HEIGHT - (HEIGHT / 10)) - ((static_cast<int>(data_y) * 20));
	int r = 4;

	DrawCircle(x, y, r, ORANGE);
}

void fit_the_line(float slope, float y_intercept) {

	int origin_x = WIDTH / 10;
	int origin_y = HEIGHT - (HEIGHT / 10);

	int y = y_intercept * 200;
	int x = slope * 2;

	DrawLine(origin_x, origin_y - (y_intercept * 200), WIDTH - (WIDTH / 10), ((HEIGHT / 10) / (slope * 1.25)) - (y_intercept * 200), BLACK);
}


