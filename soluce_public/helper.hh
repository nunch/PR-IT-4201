#ifndef HELPER_HH
# define HELPER_HH

#include "image2d.hh"
/*
	Aucune explication sur l'utilisation de ce fichier donc impossible à coder
*/


namespace my
{
	struct helper
  	{
  		helper(image2d<unsigned> i):
  		lab(i.exact()),
  		iz(i.domain()),
  		prev(i.domain()),
  		next(i.domain()){
  			box2d D = prev.domain();
  			box2d_iterator p(D);
  			for_all(p) {
  				prev(p) = p;
  				next(p) = p;
  			}
  		};

    	image2d<unsigned> &lab;
    	image2d<unsigned> iz;
    	image2d<point2d> prev;
    	image2d<point2d> next;

  };


} // end of namespace my



#endif // ndef HELPER_HH

