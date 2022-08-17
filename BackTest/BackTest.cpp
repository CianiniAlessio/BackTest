#include <iostream>
#include <string>
#include <random>
#include <stdio.h>
#include <chrono>
#include "Reader.h"
#include "QuantLibrary.h"
#include "Option.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<fstream>

int main()
{
   
    std::vector< std::vector <std::string>> optionStrategyLines;
    std::string pathStrategy = "strategy.txt";
    std::vector<Option*> strategy;
    Reader::ReadTextFileStrategy(pathStrategy, optionStrategyLines, strategy);
   
    
    std::vector< std::vector <std::string>> lines;
    std::string path = "MSFT.csv";
    Reader::ReadFile(lines,  path,',');
    std::vector<std::vector<int>> dates;
    std::unordered_map<std::string, std::vector<double>> map = Reader::ReturnMap(lines,dates);

    for (auto& option : strategy)
    {
        option->SetInterestRate(0.05);
    }  
    int day, month, year;
    double priceClose, dailyProfit = 0, finalProfit;
    bool passedMaturity = false;
    
    std::ofstream foutProfits;
    std::ofstream foutClosing;

    foutProfits.open("csvProfits.csv", std::ofstream::out | std::ofstream::trunc);
    foutClosing.open("csvClosing.csv", std::ofstream::out | std::ofstream::trunc);
    
    for (int i = 0; i < map["Adj Close"].size() - 1; ++i)
    {
        day = dates[i][2];
        month = dates[i][1];
        year = dates[i][0];
        
        for (auto& option : strategy)
        {
            passedMaturity = false;
            option->SetVolatility(map["Volatilities"][i] + 0.2);
            priceClose = map["Adj Close"][i];
            if (option->dayToBuy <= day && option->monthToBuy == month && option->yearToBuy == year && option->calculated == false)
            {
                option->Price(priceClose);
                option->SettedPrice(true);
            }
            if (option->yearmaturity < year)
            {
                passedMaturity = true;
            }
            else if (option->yearmaturity == year)
            {
                if (option->monthsmaturity < month)
                {
                    passedMaturity = true;
                }
                else if (option->monthsmaturity == month)
                {
                    if (option->daymaturity < day)
                    {
                        passedMaturity = true;
                    }
                    else
                    {
                        passedMaturity = false;
                    }
                }
                else
                {
                    passedMaturity = false;
                }
            }
            if (!passedMaturity)
            {
                option->SetLastProfit(option->Profit(priceClose, day, month, year));
                dailyProfit += option->lastProfit;

            }
            else
            {
                dailyProfit += option->lastProfit;
            }
            if (foutProfits.is_open())
            {
                double temp = round(option->lastProfit * 100) / 100;

                foutProfits << std::to_string(temp).substr(0, std::to_string(temp).find('.') + 2 + 1) + ", ";
            }
        }
        finalProfit = dailyProfit;
        dailyProfit = 0;

        
        

        if (foutProfits.is_open())
        {
            foutProfits << "Cumulated Profit: " + std::to_string(finalProfit);
            foutClosing << std::to_string(map["Adj Close"][i]) + ',';
        }
        
        
        if (foutProfits.is_open())
        {
            foutProfits <<'\n';
        }
        
    }

    for (auto& opt : strategy)
    {
        std::cout << opt->side << " " << opt->callPut << " ~ STRIKE: " << opt->K << " PREMIUM OPTION: " << opt->optionprice << " LAST PROFIT: " << opt->lastProfit << std::endl;
    }
    std::cout << "\nFINAL TOTAL PROFIT: " << finalProfit << std::endl;
}
