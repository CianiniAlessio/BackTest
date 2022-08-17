#include "Option.h"

Option::Option(
    std::string side,
    std::string callPut,
    int dayToBuy,
    int monthToBuy,
    int yearToBuy,
    int daymaturity,
    int monthsmaturity,
    int yearmaturity,
    double K
)
{
    this->dayToBuy = dayToBuy;
    this->monthToBuy = monthToBuy;
    this->yearToBuy = yearToBuy;
    this->K = K;
    this->daymaturity = daymaturity;
    this->monthsmaturity = monthsmaturity;
    this->yearmaturity = yearmaturity;
    this->r = 0.05;
    this->optionprice = 0;
    this->payoff = 0;
    this->callPut = callPut;
    this->side = side;
}  
   

void 
Option::Price(
    double S_now
)


{
    double daysToMaturity = DateProcessor::calculatedifferencedate(this->dayToBuy, this->monthToBuy, this->yearToBuy, daymaturity, monthsmaturity, yearmaturity)/365;
    double price = 0;
    if (this->callPut == "PUT")
    {
        if (this->side == "LONG")
        {
            price = QuantLibrary::PutPrice(S_now, this->K, this->r, this->v, daysToMaturity);
        }
        else if (this->side == "SHORT")
        {
            price = QuantLibrary::CallPrice(S_now, this->K, this->r, this->v, daysToMaturity);
        }
    }
    else if (this->callPut == "CALL")
    {
        if (this->side == "LONG")
        {
            price = QuantLibrary::CallPrice(S_now, this->K, this->r, this->v, daysToMaturity);
        }
        else if (this->side == "SHORT")
        {
            price = QuantLibrary::PutPrice(S_now, this->K, this->r, this->v, daysToMaturity);
        }
    }
    else
    {
        price = -1;
    }

    this->optionprice = price >= 0 ? price : -1;
}

double
Option::Payoff(
    double S_now
)


{
    if (this->callPut == "CALL")
    {
        if (this->side == "LONG")
        {
            if (S_now > K)
            {
                this->payoff = S_now - this->K;
                return this->payoff;
            }
            else
            {
                this->payoff = 0;
                return 0;
            }
        }
        else if(this->side =="SHORT")
        {
            if (S_now > K)
            {
                this->payoff = - (S_now - this->K);
                return this->payoff;
            }
            else 
            {
                this->payoff = 0;
                return this->payoff;
            }
        }
        
    }
    else if (this->callPut == "PUT")
    {
        if (this->side == "LONG")
        {
            if (S_now > K)
            {
                this->payoff =0;
                return 0;
            }    
            else
            {
                this->payoff = -(S_now - this->K);
                return this->payoff;
            }
        }
        else if (this->side == "SHORT")
        {
            if (S_now < K)
            {
                this->payoff = -(S_now - this->K);
                return this->payoff;
            }
            else
            {
                this->payoff =0;
                return 0;
            }
        }
            
    }
    
        
}

double 
Option::InternalProfit(
    double S_now
)


{
    double poff = Payoff(S_now);
    if (this->side == "SHORT")
    {
        if (poff < 0)
        {
            return poff - this->optionprice;
        }
        else
        {
            return this->optionprice;
        }
    }
    else if (this->side == "LONG")
    {
        return poff - this->optionprice;
    }
    else
    {
        return -1;
    }
}

double
Option::Profit(
    double S_now,
    int day, 
    int month, 
    int year)



{
    if (year > this->yearmaturity )
    {
        if (this->side == "SHORT")
        {
            if (this->payoff < 0)
            {
                return this->payoff - this->optionprice;
            }
            else
            {
                return this->optionprice;
            }            
        }
        else if (this->side == "LONG")
        {
            return this->payoff;
        }        
    }
    else if (year < this->yearmaturity)
    {
        return InternalProfit(S_now);

    }
    else
    {
        if (month < this->monthsmaturity)
        {
            return InternalProfit(S_now);            
        }
        else if (month == this->monthsmaturity)
        {
            if (day <= this->daymaturity)
            {
                return InternalProfit(S_now);
            }
        }
    }
}

void
Option::SetInterestRate(
    double newIntRate
)


{
    this->r = newIntRate;
}
void 
Option::SetVolatility(
    double newVoltatilty
)


{
    this->v = newVoltatilty;
}
void
Option::SetLastProfit(
    double lastProfit
)


{
    this->lastProfit = lastProfit;
}
void 
Option::SettedPrice(
    bool isCalculated
)


{
    this->calculated = isCalculated;
}