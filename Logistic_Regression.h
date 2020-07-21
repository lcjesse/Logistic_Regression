/*
Author: LiChang
Student ID: 119039910099
Time: 2020.3.18
*/

#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include "string"
#include "string.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <memory.h>

#include "math.h"

using namespace std;

const double alph = 0.01;			//学习率
const int compnum = 2;			//x分量数量
const int sampnum = 41;		//训练样本数量
const int testnum = 10;		//测试样本数量

struct Data
{
	double x[compnum];
	bool y;
};

struct Result
{
	bool prediction;			//预测结果
	bool result;			//预测对错
};

int StrToInt(char* c)
{
	int a;
	stringstream str;
	str << c;
	str >> a;
	str.clear();
	return a;
}

double StrToDoub(char* c)
{
	double a;
	stringstream str;
	str << c;
	str >> a;
	str.clear();
	return a;
}

int Read(Data* data, const char* file)
{
	FILE* File;
	errno_t err;
	char input[1024];
	char* buf2;
	char* buf3;
	char* buf4;
	err = fopen_s(&File, file, "rt");

	int row = 0;
	int cloumn = 0; 
	char delim[] = ",";
	char* tmpdata = NULL;

	while (!feof(File) && row < sampnum)
	{
		input[0] = '\0';
		fgets(input, 1024, File);

		if (input[strlen(input) - 1] == '\n')
		{
			input[strlen(input) - 1] = '\0';
		}

		for (int column = 0; column < (compnum+1); column++)
		{
			if (column == 0)			//第一列为X1
			{
				tmpdata = strtok_s(input, delim, &buf2);
				data[row].x[column] = StrToDoub(tmpdata);
			}
			else if (column < compnum)			//第二列为X2
			{
				tmpdata = strtok_s(buf2, delim, &buf3);
				data[row].x[column] = StrToDoub(tmpdata);
			}
			else               //第三列是Y
			{
				tmpdata = strtok_s(buf3, delim,&buf4);
				if (tmpdata[0] == '1')
					data[row].y = 1;
				else
					data[row].y = 0;
			}
		}
		row++;
	}
	return 1;
}

void Logi(Data* data, double* theta)
{
	for (int i = 0; i < (compnum + 1); i++)
	{
		theta[i] = 1.0;
	}
	double t[3];
	double h = 0.0;
	double error = 0.0;
	//ofstream cost_log;
	//cost_log.open("cost_function.txt", ios::out | ios::app);
	//double cost = 0.0;
	for (int i = 0; i < 3; i++)
		t[i] = 0.0;
	for (int iter = 0; iter < 20000; iter++)
	{
		//for (int i = 0; i < 3; i++)
		//	t[i] = 0.0;
		for (int row = 0; row < sampnum; ++row)
		{
			h = 0.0;
			for (int column = 0; column < compnum; column++)
			{
				h += data[row].x[column] * theta[column + 1];
			}
			h += theta[0];
			h = 1 / (1 + exp(-h));

			error = data[row].y - h;
			//cost += data[row].y*log(h)+(1-data[row].y)*log(1-h);
			t[0] += error * alph;
		}
		for (int k = 0; k < compnum; k++)
		{
			for (int row = 0; row < sampnum; ++row)
			{
				h = 0.0;
				for (int column = 0; column < compnum; column++)
				{
					h += data[row].x[column] * theta[column + 1];
				}
				h += theta[0];
				h = 1 / (1 + exp(-h));

				error = data[row].y - h;

				t[k + 1] += error * alph * data[row].x[k];
			}
		}
		//double sigma=0;
		for (int i = 0; i < 3; i++)
		{
			theta[i] += t[i] / 41;
			//sigma += theta[i];
		}
		//for (int j = 0; j < 3; j++)
		//	theta[j] = theta[j] / sigma;
		
		printf("%f\t%f\t%f\n", theta[0], theta[1], theta[2]);
		//cost_log << iter << "\t" << -1/41*cost << "\n";
	}
	//cost_log.close();
}

Result Predict(Data data, double* theta)
{
	Result tmpresult;
	double h = 0.0;
	tmpresult.prediction = 0;
	tmpresult.result = 0;
	for (int column = 0; column < compnum; column++)
	{
		h += data.x[column] * theta[column+1];
	}
	h += theta[0];
	h = 1 / (1 + exp(-h));

	if (h > 0.5)
		tmpresult.prediction = 1;
	else
		tmpresult.prediction = 0;

	if (tmpresult.prediction == data.y)
		tmpresult.result = 1;
	else
		tmpresult.result = 0;
	
	return tmpresult;
}
#endif