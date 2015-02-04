#include "fun_image.hh"


int main()
{
	using namespace my;

	image2d<int> ima(2,2);
	debug_iota(ima);
	
	std::cout << "ima  = " << ima << std::endl;
	std::cout << "ima' = " << make_fun_image(ima, equals(1)) << std::endl;
}
