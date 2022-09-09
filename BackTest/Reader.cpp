#include "Reader.h"


Reader::Reader()
{}

void
Reader::ReadFile(
	std::vector< std::vector <std::string>>& lines,
	std::string path, char splitter 
)

{
	std::ifstream myfile;
	myfile.open(path);
	std::string mystring;
	if (myfile.is_open()) {
		std::string mystring;
		while (std::getline(myfile, mystring)) {
			lines.push_back(Reader::Split(mystring, splitter));
		}
	}
}

std::vector<std::string>
Reader::Split(
	std::string mystring,
	char tosplit
)

{
	std::vector<std::string> splittedstring;
	std::string topush = "";
	for(int i= 0; i< mystring.size();++i)
	{
		if (mystring[i] != tosplit)
		{
			topush.push_back(mystring[i]);
		}
		else
		{
			splittedstring.push_back(topush);
			topush.clear();
		}
		if (i == mystring.size() - 1 && topush != "")
		{
			splittedstring.push_back(topush);
			topush.clear();
		}
	}
	return splittedstring;

}
std::vector<int>
Reader::SplitDate(
	std::string mystring,
	char tosplit
)

{
	std::vector<std::string> splittedstring;
	std::string topush = "";
	for (int i = 0; i < mystring.size(); ++i)
	{
		if (mystring[i] != tosplit)
		{
			topush.push_back(mystring[i]);
		}
		else
		{
			splittedstring.push_back(topush);
			topush.clear();
		}
		if (i == mystring.size() - 1 && topush != "")
		{
			splittedstring.push_back(topush);
			topush.clear();
		}
	}
	std::vector<int> datearray;
	datearray.push_back(stoi(splittedstring[0]));
	datearray.push_back(stoi(splittedstring[1]));
	datearray.push_back(stoi(splittedstring[2]));
	return datearray;

}

std::unordered_map<std::string, std::vector<double>>
Reader::ReturnMap(
	std::vector<std::vector <std::string>>& lines,
	std::vector<std::vector<int>>& dates
)

{
	
	std::string Date = lines[0][0], Open = lines[0][1], High = lines[0][2],
				Low = lines[0][3], Close = lines[0][4], AdjClose = lines[0][5],
				Volume = lines[0][6];
	std::vector<double>  Opens, Highs, Lows, Closes, AdjCloses, Volumes, Volatilities;
	
	int countrow = 0;
	std::string topush;
	for (auto& i : lines)
	{
		
		if (countrow != 0 && i.size()==7)
		{			
			std::vector<int> date= SplitDate(i[0], '-');
			dates.push_back(date);
			Opens.push_back(std::stod(i[1]));
			Highs.push_back(std::stod(i[2]));
			Lows.push_back(std::stod(i[3]));
			Closes.push_back(std::stod(i[4]));
			AdjCloses.push_back(std::stod(i[5]));
			Volumes.push_back(std::stod(i[6]));
			if (countrow == 1)
			{
				Volatilities.push_back(0);
			}
			else
			{
				Volatilities.push_back(abs(Closes[countrow-1] / Closes[countrow - 2] - 1));
			}
		
		}
		countrow++;
	}
	std::unordered_map<std::string, std::vector<double>> datamap{
		{Open,Opens},
		{High,Highs},
		{Low,Lows},
		{Close,Closes},
		{AdjClose,AdjCloses},
		{Volume,Volumes},
		{"Volatilities",Volatilities}
	};
	return datamap;
}

void
Reader::ReadTextFileStrategy(
	std::string pathStrategy, 
	std::vector< std::vector <std::string>>& optionStrategyLines,
	std::vector<Option*>& strategyToImplement
)

{	
	Reader::ReadFile(optionStrategyLines, pathStrategy, ' ');
	
	for (auto& i : optionStrategyLines)
	{
		std::vector<int> datesBuy = Reader::SplitDate(i[2], '/');
		std::vector<int> datesMaturity = Reader::SplitDate(i[3], '/');

		strategyToImplement.push_back(new Option(i[0],
			i[1],
			datesBuy[0],
			datesBuy[1],
			datesBuy[2],
			datesMaturity[0],
			datesMaturity[1],
			datesMaturity[2],
			std::stod(i[4])
		));

	}
}