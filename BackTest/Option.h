#pragma once
#include "QuantLibrary.h"
#include "DateProcessor.h"
#include <string>
#include <iostream>
class Option
{    
public:
    Option(std::string side, std::string callPut, int dayToBuy, int monthToBuy, int yearToBuy, int daymaturity, int monthsmaturity, int yearmaturity, double K );
    void SetInterestRate(double newIntRate);
    void SetVolatility(double newVoltatilty);
    void Price(double S_now);
    double Payoff(double S_now);
    double Profit(double S_now, int day,int month, int year);
    double InternalProfit(double S_now);
    void SetLastProfit(double lastProfit);
    void SettedPrice(bool isCalculated);
    double K, optionprice, r, v, payoff, lastProfit;
    int daymaturity, monthsmaturity, yearmaturity, dayToBuy, monthToBuy, yearToBuy;
    std::string callPut, side;
    bool calculated = false;
    
    


    

};

