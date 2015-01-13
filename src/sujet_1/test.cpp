#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
template <typename T>
class test
{
public:
	test();
	~test();
	bool test1(T a);
};

int main(int argc, char const *argv[])
{
	test<int>::test1(int a){
		return a;
	};
	return 0;
}