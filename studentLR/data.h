#pragma once
#include<iostream> 
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using std::string;
using std::vector;
typedef vector<vector<double>> vvd;
typedef vector<double> vd;

//parsing the data from a csv format
vector<vector<string>> parseCSV(const string& filename) {
    vector<vector<string>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) { // Read the file line by line
        vector<string> row;
        std::stringstream lineStream(line);
        string cell;

        while (std::getline(lineStream, cell, ',')) { // Split each line into cells by comma
            row.push_back(cell);
        }

        data.push_back(row); // Add the row to the main data structure
    }

    file.close();
    return data;
} 

//casting the data into double data type
vvd init_values(vector<vector<string>>& data, size_t rows, size_t cols) {

    vvd data_values;
    data_values.resize(rows, vd(cols));//the data values that will be used

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data_values[i][j] = std::stod(data[i][j]);
        }
    }
    return data_values;
}

//normalizing the values wtih min max normalization
void normalization(vvd& data, int size) {

    vd x_data;   x_data.resize(size);
    vd z_data;   z_data.resize(size);
    vd y_data;   y_data.resize(size);

    for (int i = 0; i < size; i++) {
        x_data[i] = data[i][0];
        z_data[i] = data[i][1];
        y_data[i] = data[i][2];
    }

    double max_x = *std::max_element(x_data.begin(), x_data.end());
    double min_x = *std::min_element(x_data.begin(), x_data.end());

    double max_z = *std::max_element(z_data.begin(), z_data.end());
    double min_z = *std::min_element(z_data.begin(), z_data.end());

    double max_y = *std::max_element(y_data.begin(), y_data.end());
    double min_y = *std::min_element(y_data.begin(), y_data.end());

    for (int i = 0; i < size; i++) {
        data[i][0] = (data[i][0] - min_x) / (max_x - min_x);
        data[i][1] = (data[i][1] - min_z) / (max_z - min_z);
        data[i][2] = (data[i][2] - min_y) / (max_y - min_y);
    }

}

//setting the validation set
vvd validation(vvd& data, int size, size_t rows, size_t cols) {

    vvd set;
    set.resize(rows - size, vd(cols));

    int k = 0;
    for (int i = size; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            set[k][j] = data[i][j];
        }
        k++;
    }
    return set;
}

string filename = "studentdataset.csv";
vector<vector<string>> data = parseCSV(filename); //the whole data in string

size_t rows = data.size();
size_t cols = data[0].size(); // sizes of the datasets and batches
int size = 1500; // batch

vvd data_values = init_values(data, rows, cols); //the data batch in double
vvd data_norm = init_values(data, rows, cols);
vvd validation_set = validation(data_values, size, rows, cols);