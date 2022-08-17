#include "QuantLibrary.h"
QuantLibrary::QuantLibrary()
{

}
double QuantLibrary::BSFormula()
{
	return 0;
}
double QuantLibrary::NormCdf(const double& x) {
    double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) {
        return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
    }
    else {
        return 1.0 - NormCdf(-x);
    }
}
double QuantLibrary::NormPdf(const double& x) {
    return (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x);
}
double QuantLibrary::dj(const int& j, const double& S, const double& K, const double& r, const double& v, const double T) {
    return (log(S / K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (pow(T, 0.5)));
}
double QuantLibrary::CallPrice(const double& S, const double& K, const double& r, const double& v, const double T) {
    
    return T>=0 ? S * NormCdf(dj(1, S, K, r, v, T)) - K * exp(-r * T) * NormCdf(dj(2, S, K, r, v, T)) : -1;
}
double QuantLibrary::PutPrice(const double& S, const double& K, const double& r, const double& v, const double T) {
    return T >= 0 ? K * exp(-r * T) * NormCdf(-dj(2, S, K, r, v, T)) - S * NormCdf(-dj(1, S, K, r, v, T)) : -1;
}