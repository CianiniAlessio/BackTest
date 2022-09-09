## Introduction


While trying to find a platform on the internet in which is possible to backtest an option strategy I decided to develop my own. 
The option pricing is based on a Black & Scholes model and of course it's limited to its assumption, but it can be a good approximation of the reality.

## Black \& Scholes Model
About the B&S model, in order to apply its formula, we need to assume that the market consists of at least one risky asset and one riskless asset.
The assumption concerning the risky asset are:
- The Riskless rate is constant 
- The stock does not pay a dividend 
- The log-return of a stock price is an infinitesimal random walk with drift. This means that our stock needs to follow a Geometric Brownian Motion.
We consider a stochastic-process $S_t$ to be a Geometric Brownian Motion if it satisfies the following SDE: $$dS_t = \mu S_tdt + \sigma S_tdW_t$$ in which $W_t$ is a Brownian Motion, $\mu$ the drift and $\sigma$ the volatility.
We have also some assumption to be made for the market and those are:
- No arbitrage opportunity 
- Ability to borrow and lend any amount.
- Ability to buy and sell any amount
- The above transactions do not incur any fees or costs
With all these assumption we can introduce the B&S equation:
$\frac{\partial V}{\partial t} + \frac{1}{2}\sigma^2 S^2 \frac{\partial ^2 V}{\partial S^2} + rS\frac{\partial V}{\partial S} - rV = 0.$
This formula calculates the price of Put and Call European Option and the value is obtained through these steps:\\
The price for a Call Option is :
$C(S_t,t) = \mathcal{N}(d_1)S_t - \mathcal{N}(d_2)Ke^{r(T-t)}$
in which 
$d_1 = \frac{1}{\sigma \sqrt{T-t}} \left [ ln \left (\frac{S_t}{K}\right ) + \left (r + \frac{\sigma^2}{2} \right )(T-t) \right ]$
while 
$d_2 = d1 - \sigma \sqrt{T-t}.$
If we want to compute the price for a Put Option we just have:
$P(S_t,t) = \mathcal{N}(-d_2)Ke^{-r(T-t)} - \mathcal{N}(-d1)S_t$
## How the code works
 In this project I created different class with different meanings:
 The class **DateProcessor** and **Reader** are two simple class to prepare the data.
 The class **QuantLibrary** presents the math needed to compute the price of the option
 The class **Option** defines the object Option which I'll use to calculate the final profit.
 The class **BackTest** contains the main method in which I've done all the code for the backtest of the strategy
 To create a strategy is needed to change the file strategy.txt, in the file it's already present a prototype of how you should define the object option.
The sintax for it is:
 **LONG CALL 1/1/2001 1/1/2022 50** in which the first value is the side of the option, then the second is if it's a call or a put, the third is the date in which you desire to buy the option during the backtest, the fourth is the maturity date, and the last number is the strike price.

If for example we want a strategy that consists of more than 3 option we have to write it like this:


**SHORT CALL 2/8/2022 2/12/2022 285**

**LONG CALL 2/2/2017 2/2/2022 150**

**LONG PUT 29/12/2021 29/12/2022 325**

In the GitHub folder there are 2 sets of data, one for ISP.MI and the other for SHEL. Both have more than 25 year of data which can be used to backtest the strategy. If you want to Backtest a different company just download from yahoo finance the historical data and upload them in the folder in which there are the other 2 files.

**Is needed to change the path for the file containing the data and the one containing the strategy.**


At the end of the backtest you'll have a debug screen like this:


![debug](https://user-images.githubusercontent.com/109857992/189388949-1ec9c77c-7301-4064-9ecf-af834a1af953.png)

In which there are the data about the option, the premium paid and the profit at maturity. The final profit is the sum of all the profits and losses.



While in the file csvProfits there are the results for each iteration (date): 

![profits](https://user-images.githubusercontent.com/109857992/189389445-9090a201-9fac-4051-a48e-e068447ab4fa.png)

and at the end:

![profitsfinal](https://user-images.githubusercontent.com/109857992/189389329-6ed23871-0f0e-4fc5-a1d3-11e719ea19d3.png)


Of course this strategy is just a random strategy which doesn't make any sense for the data in which I did the backtest. ( strike of 285 with option price of 1.4\$). 
