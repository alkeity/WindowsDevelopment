#include "Calculator.h"
#include<Windows.h>
#include<cstdio>
#include <math.h>


void Calculator::Add(double a, double b, char resultBuffer[], int size)
{
	double res = a + b;
	sprintf_s(resultBuffer, size, "%f", res);
}

void Calculator::Substract(double a, double b, char resultBuffer[], int size)
{
	double res = a - b;
	sprintf_s(resultBuffer, size, "%f", res);
}

void Calculator::Multiply(double a, double b, char resultBuffer[], int size)
{
	double res = a * b;
	sprintf_s(resultBuffer, size, "%f", res);
}

void Calculator::Divide(double a, double b, char resultBuffer[], int size)
{
	if (b == 0) { throw 1; }
	double res = a / b;
	sprintf_s(resultBuffer, size, "%f", res);
}

double Calculator::StringToDouble(char buffer[], int size)
{
	int iNum = atoi(buffer);
	char* pointPos = strchr(buffer, '.');
	if (pointPos == NULL) { return (double)iNum; }

	char tempBuffer[g_i_SIZE]{};
	int pos = pointPos - buffer;
	strncpy_s(tempBuffer, size, buffer + pos + 1, strlen(buffer) - pos);
	double fNum = atoi(tempBuffer) / pow(10, strlen(tempBuffer));
	return iNum + fNum;
}
