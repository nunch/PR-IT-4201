#ifndef HELPER_HH
# define HELPER_HH

#include "image2d.hh"


namespace my
{
  struct helper
  	{
  		helper(image2d<unsigned> i):
  		lab(i.exact()),
  		iz(i.domain()),
  		prev(i.domain()){
  			box2d D = prev.domain();
  			box2d_iterator p(D);
  			for_all(p) prev(p) = p;
  		};

      helper& exact() { return *(helper*)(void*)this; }

      const helper& exact() const { return *(const helper*)(const void*)this; }

    	image2d<unsigned> &lab;
      image2d<unsigned> iz;
    	image2d<point2d> prev;

  };


} // end of namespace my



#endif // ndef HELPER_HH

