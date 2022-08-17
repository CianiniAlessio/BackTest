#pragma once
class DateProcessor
{
private:
	
	static int NumberDaysMonth(int month);

public:
	static const int Jan = 31, Feb = 28, Mar = 31, Apr = 30, May = 31, Jun = 30, Jul = 31, Aug = 31, Sept = 30, Oct = 31, Nov = 30, Dec = 31;
	static double calculatedifferencedate(int, int, int, int, int, int);
	
};

