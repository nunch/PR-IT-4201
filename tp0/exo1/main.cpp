#include "truc.hh"
#include "vector.hh"
#include "matrix.hh"
#include "ops.hh"
#include <iostream>
//#include "fillmatrix.hh"
#include "fill.hh"

int main(int argc, char const *argv[])
{
	vector v1(5),v2(5);
	vector v = v1+5;
	matrix m(5,5);
	m.fill(2);
	
	//fill(m,6);
	//fill(v1,7);
	std::cout << v[1] << " super " << m(0,1) << std::endl;
	return 0;
}