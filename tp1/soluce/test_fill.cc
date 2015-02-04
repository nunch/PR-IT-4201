#include "image2d.hh"
#include "fun_image.hh"


// mÃ©thode Ã  ajouter dans la classe image2d:
/*
template <typename U, unsigned n>
void fill(U (&data)[n])
{
	if (n != domain().npoints())
		std::abort();
	box2d_iterator p(domain());
	unsigned i = 0;
	for_all(p)
	(*this)(p) = data[i++];
}
*/


namespace my
{

	template <typename I>
	void fancy_print(const Image<I>& ima_,
		const box2d& b,
		std::ostream& ostr = std::cout)
	{
		const I& ima = ima_.exact();
		point2d p;
		int& row = p.row;
		int& col = p.col;
		for (row = b.pmin().row; row <= b.pmax().row; row += 1)
		{
			for (col = b.pmin().col; col <= b.pmax().col; col += 1)
				if (ima_.domain().has(p))
					ostr << ima(p) << ' ';
				else
					ostr << "  ";
				ostr << std::endl;
			}
			ostr << std::endl;
		}

} // end of my



int main()
{
	using namespace my;

	box2d b(4, 5);

	bool_t msk_dta[]   = {0, 0, 0, 1, 1,
		1, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		1, 1, 1, 1, 1};

		unsigned lab_dta[] = {0, 0, 0, 0, 0,
			1, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			2, 0, 0, 0, 0};

			image2d<bool_t> msk(b);
			msk.fill(msk_dta);
			msk.debug_print();

			image2d<unsigned> lab(b);
			lab.fill(lab_dta);
			lab.debug_print();


	//             col =  0  1  2  3  4     row
	unsigned out_dta[] = 
			{0, 0, 0, 1, 1,  // 0
			 1, 1, 1, 1, 0,  // 1
			 0, 0, 0, 0, 0,  // 2
			 2, 2, 2, 2, 2}; // 3

			image2d<unsigned> out(b);
			out.fill(out_dta);
			out.debug_print();

			std::cout << "lab == 1" << std::endl;
			fancy_print(make_fun_image(out, equals(1)), b);

			std::cout << "lab == 2" << std::endl;
			fancy_print(make_fun_image(out, equals(2)), b);
		}