#pragma once
#include <cstdio>

class Calculator
{
	static const int g_i_SIZE = 256;
public:
	static void Add(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static void Substract(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static void Multiply(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static void Divide(double a, double b, char resultBuffer[], int size = g_i_SIZE);
	static double StringToDouble(char buffer[], int size = g_i_SIZE);
};
