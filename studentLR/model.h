#pragma once
#include<iostream>
#include"data.h"

#define LR 0.01
#define EPOCH 4000 // 4/5000 e topa

//displayibg vector values
void display_data(vd& y_pred, int size) {

	std::cout << "Predictions:\n";
	for (int i = 0; i < size; i++) {
		std::cout << y_pred[i] << "\n";
	}
}

//forwarding inputs
void forward(vvd& data,vd& y_pred, double slope_x, double slope_z, double y_intercept, int size) {

	for (int i = 0; i < size; i++) {
		y_pred[i] = (data[i][0] * slope_x) + (data[i][1] * slope_z) + y_intercept;
	}
}

//calculating the cost
double costd(vvd& data, vd& y_pred, int size) {

	double cost = 0.0;
	for (int i = 0; i < size; i++) {
		cost += (data[i][2] - y_pred[i]) * (data[i][2] - y_pred[i]);
	}
	return cost / size;
}

//optimizing the parameters with gradient descent
void optimize(vvd& data, vd& y_pred, int size, double& slope_x, double& slope_z, double& y_intercept) {

	double gradient_y = 0.0;
	double gradient_x = 0.0;
	double gradient_z = 0.0;

	for (int i = 0; i < size; i++) {
		gradient_y += (data[i][2] - y_pred[i]);
	    gradient_x += (data[i][2] - y_pred[i]) * data[i][0];
	    gradient_z += (data[i][2] - y_pred[i]) * data[i][1];
	}
	gradient_y *= -(2.0 / size);
	gradient_x *= -(2.0 / size);
	gradient_z *= -(2.0 / size);

	slope_x -= static_cast<double>(LR) * gradient_x;
	slope_z -= static_cast<double>(LR) * gradient_z;
	y_intercept -= static_cast<double>(LR) * gradient_y;
}

//training the model Epoch times
void trainmodel(vvd& data, vd& y_pred, double& slope_x, double& slope_z, double& y_intercept, int size) {

	for (int i = 0; i < EPOCH; i++) {

		forward(data, y_pred, slope_x, slope_z, y_intercept, size);

		double loss = costd(data, y_pred, size);
		std::cout << "C=" << loss << " | train#:" << i << "\n";

		optimize(data, y_pred, size, slope_x, slope_z, y_intercept);
	}
}

//calculating R^2 and F statistical
void model_relyability(vvd& data, vd& y_pred, int size) {

	double y_mean = 0.0;

	for (int i = 0; i < size; i++) {
		y_mean += data[i][2];
	}
	y_mean /= size;

	double variance_mean = 0.0;
	double variance_fit = 0.0;

	for (int i = 0; i < size; i++) {
		variance_mean = (data[i][2] - y_mean) * (data[i][2] - y_mean);
		variance_fit = (data[i][2] - y_pred[i]) * (data[i][2] - y_pred[i]);
	}

	double R2 = 1.0 - (variance_fit / variance_mean);

	double chisli = (variance_mean - variance_fit) / 2;
	double znam = variance_fit / (size - 3);
	double F = chisli / znam; 

	std::cout << "\nR^2 = " << R2 << "  F = " << F << "\n";
}

//denormalizing the parameters
void denormalize(vvd& data, int size, double& x_slope, double& z_slope, double& y_intercept) {

	vd x_data;
	x_data.resize(size);
	vd z_data;
	z_data.resize(size);
	vd y_data;
	y_data.resize(size);

	double mean_x = 0.0;
	double mean_z = 0.0;

	for (int i = 0; i < size; i++) {
		x_data[i] = data[i][0];
		z_data[i] = data[i][1];
		y_data[i] = data[i][2];
		mean_x += data[i][0];
		mean_z += data[i][1];
	}
	mean_x /= size;
	mean_z /= size;

	double max_x = *std::max_element(x_data.begin(), x_data.end());
	double min_x = *std::min_element(x_data.begin(), x_data.end());

	double max_z = *std::max_element(z_data.begin(), z_data.end());
	double min_z = *std::min_element(z_data.begin(), z_data.end());

	double max_y = *std::max_element(y_data.begin(), y_data.end());
	double min_y = *std::min_element(y_data.begin(), y_data.end());

	x_slope = x_slope * ((max_y - min_y) / (max_x - min_x));
	z_slope = z_slope * ((max_y - min_y) / (max_z - min_z));

	y_intercept = min_y + (y_intercept * (max_y - min_y)) - ((x_slope * min_x) + (z_slope * min_z));
}

//testing on the validation set
void testmodel(vvd& test_data,vd& test_pred, double& x_slope, double& z_slope, double& y_intercept, int size) {
	
	int test_size = test_data.size();
	forward(test_data, test_pred, x_slope, z_slope, y_intercept, test_size);
	model_relyability(test_data, test_pred, test_size);
}