#pragma once
#include <cstdio>

class Calculator
{
	static const int g_i_SIZE = 256;
public:
	static void Add(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static double Add(double a, double b);
	static void Substract(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static double Substract(double a, double b);
	static void Multiply(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static double Multiply(double a, double b);
	static void Divide(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static double Divide(double a, double b);

	static double StringToDouble(char buffer[], int size = g_i_SIZE);
	static void DoubleToString(double number, char buffer[], int size = g_i_SIZE);
};
