#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include "Option.h"
class Reader
{

public:
	Reader();
	static void ReadFile(std::vector< std::vector <std::string>>& lines, std::string path, char splitter);
	static std::unordered_map<std::string, std::vector<double>>
		ReturnMap(std::vector<std::vector <std::string>>& lines, std::vector<std::vector<int>>& dates);
	static std::vector<std::string> Split(std::string mystring, char tosplit);
	static std::vector<int> SplitDate(std::string mystring, char tosplit);
	static void ReadTextFileStrategy(std::string pathStrategy, std::vector< std::vector <std::string>>& optionStrategyLines,
		std::vector<Option*>& strategyToImplement);

};

