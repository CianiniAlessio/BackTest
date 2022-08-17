#include "DateProcessor.h"

double
DateProcessor::calculatedifferencedate(int dayOne, int monthOne, int yearOne, int dayTwo, int monthTwo, int yearTwo)

{
	double remainingDays = 0;

	if (yearOne < yearTwo)
	{
		if (monthOne < monthTwo)
		{
			remainingDays = NumberDaysMonth(monthOne) - dayOne;
			for (int i = monthOne + 1; i < monthTwo; ++i)
			{
				remainingDays += NumberDaysMonth(i);
			}
			remainingDays += dayTwo;
			remainingDays += 365 * (yearTwo - yearOne);
		}
		else if (monthOne > monthTwo)
		{

			for (int i = monthOne - 1; i > monthTwo; --i)
			{
				remainingDays += NumberDaysMonth(i);
			}
			remainingDays += NumberDaysMonth(monthTwo) - dayTwo + dayOne;
			remainingDays = (365 - remainingDays);
			remainingDays += 365 * (yearTwo - yearOne - 1);
		}
		else
		{
			return 365 * (yearTwo - yearOne) + yearTwo - yearOne;
		}
	}
	else if (yearOne == yearTwo)
	{
		if (monthOne < monthTwo)
		{

			remainingDays = NumberDaysMonth(monthOne) - dayOne;
			for (int i = monthOne + 1; i < monthTwo; ++i)
			{
				remainingDays += NumberDaysMonth(i);
			}
			remainingDays += dayTwo;

		}
		else if (monthOne == monthTwo)
			remainingDays = (dayOne <= dayTwo) ? dayTwo - dayOne : -1;
		else
			return -1;
		return remainingDays;
	}
	else
		return -1;

	
	

}
int
DateProcessor::NumberDaysMonth(int months)

{
	switch (months)
	{
	case 1:
		return Jan;
	case 2:
		return Feb;
	case 3:
		return Mar;
	case 4:
		return Apr;
	case 5:
		return May;
	case 6:
		return Jun;
	case 7:
		return Jul;
	case 8:
		return Aug;
	case 9:
		return Sept;
	case 10:
		return Oct;
	case 11:
		return Nov;
	case 12:
		return Dec;
	default:
		break;
	}
}
