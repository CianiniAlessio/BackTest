#pragma once
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323
class QuantLibrary
{
public:
	QuantLibrary();
	~QuantLibrary()
	{
		std::cout << "Deleting QuantLibrary Object " << std::endl;
	}
	static double CallPrice(const double& S, const double& K, const double& r, const double& v, const double T);
	static double PutPrice(const double& S, const double& K, const double& r, const double& v, const double T);
private:
	static double BSFormula();
	static double NormCdf(const double& x);
	static double NormPdf(const double& x);
	static double dj(const int& j, const double& S, const double& K, const double& r, const double& v, const double T);
	
};

