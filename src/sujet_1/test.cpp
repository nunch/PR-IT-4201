#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
	std::string s1, s2;
	s1 = "youpi";
	s2 = "you";
	bool b = s1>s2;
	std::cout << b <<std::endl;
	return 0;
}