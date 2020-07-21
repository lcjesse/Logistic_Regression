/*
Author: LiChang
Student ID: 119039910099
Time: 2020.3.18
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Logistic_Regression.h"

int main()
{
	const char* file = "logistic_regression_data-1.txt";
	const char* testfile = "test.txt";
	Data* data = new Data[sampnum];
	double* theta = new double[compnum + 1];
	Data* test = new Data[testnum];
	ofstream output;

	output.open("test_result.txt", ios::out | ios::app);

	if (-1 != Read(data, file))
		Logi(data, theta);
	
	for (int i = 0; i < (compnum + 1); i++)
	{
		output << "Theta" << i << " is " << theta[i] << "\t\t";
	}
	output << endl;

	int correct = 0;

	if (-1 != Read(test, testfile))
	{
		for (int i = 0; i < testnum; i++)
		{
			bool hit = Predict(test[i], theta).result;
			bool prediction = Predict(test[i], theta).prediction;
			output << "Prediction of data no." << i + 1 << " is " << prediction << ".\t The ture value is " << test[i].x[0] << "   " << test[i].x[1] << "   " << test[i].y<<"		";
			if (hit)
			{
				correct++;
				output << "This prediction is correct." << endl;
			}
			else
				output << "This prediction is wrong." << endl;
		}
	}

	double accuracy_rate = double(correct) / testnum;
	
	output << "Accuracy rate: " << accuracy_rate * 100 << "\%" << endl;

	delete[]data;
	delete[]theta;
	delete[]test;

	output.close();

	return 0;
}