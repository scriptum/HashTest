#include <iostream>
#include <string>
#include <map>
#include "read.hpp"
#include "perf_timer.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE words.size()
#endif

int main()
{
	if(read_dict() == 0)
		return -1;
	std::map<std::string, int> ht;
	perf_timer_start();
	for(int i = 0; i < 20000000; i++)
		ht[words[i % TABLE_SIZE]]++;
	perf_timer_end();
	perf_timer_print();
	return 0;
}
