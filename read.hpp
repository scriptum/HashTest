#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<std::string> words;

static inline int read_dict()
{
	std::ifstream inf("dictionary.txt");
	if(inf.is_open())
	{
		std::string line;
		while(std::getline(inf, line))
		{
			size_t p = line.find_first_of("\r\n");
			line[p] = '\0';
			words.push_back(line);
		}
		return 1;
	}
	else
		return 0;
}
