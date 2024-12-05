#include<iostream>
#include"model.h"
#include"visual.h"

int main() {

	InitWindow(WIDTH, HEIGHT, "Sleep hours per day & GPA");
	SetTargetFPS(60);

	normalization(data_norm, size); //normalized data

	vd y_pred;//container for the predictions 
	y_pred.resize(size);
	vd test_pred;
	test_pred.resize(validation_set.size());

	double x_slope = 0.0;
	double z_slope = 0.0; //the parameters of the model
	double y_intr= 0.0;
	
	trainmodel(data_norm, y_pred, x_slope, z_slope, y_intr, size);
	denormalize(data_values, size, x_slope, z_slope, y_intr);//denormalizing the parameters values after training

	forward(data_values, y_pred, x_slope, z_slope, y_intr,size);
	model_relyability(data_values, y_pred, size); //and calculating the R^2 and F values 

	std::cout << "\nPress anything to start testing model";
	std::cin.get();

	testmodel(validation_set, test_pred, x_slope, z_slope, y_intr, rows-size); // testing the model on a validation set

	while (!WindowShouldClose()) {
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			plot_graph();

			/*for (int i = 0; i < size; i++) {
				plot_data_points_train(data_values[i][0], data_values[i][2]);
			}
			*/
			for (int i = 0; i < validation_set.size(); i++) {
				plot_data_points_test(validation_set[i][0], validation_set[i][2]);
			}

			fit_the_line(x_slope, y_intr);

		}
		EndDrawing();
	}
	CloseWindow();
}