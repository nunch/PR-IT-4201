#ifndef ANALYZE_HH
# define ANALYZE_HH

#include "image2d.hh"
#include "image_if.hh"
#include "helper.hh"
#include "compute_dmap__v2.hh"



namespace my
{
	image2d<unsigned> analyze(image2d<unsigned>& lab,
					helper &h,
					image2d<bool_t>& msk)
	{
		image2d<unsigned> dmap = compute_dmap__helper(lab,h,msk);
		std::queue<point2d> queue;
		box2d_iterator p(lab.domain());
		for_all(p){
			if(lab(p)!=0) {
				queue.push(p);
			}
		}
		while(!queue.empty()){
			point2d pp = queue.front();
			queue.pop();
			point2d resP;
			int resI=-1;
			int tmp=-1;
			for_all(p){
				if(h.iz(p)==lab(pp)){
					tmp = dmap(p);
					if(tmp>resI){
						resI = tmp;
						resP=p;
					}
				}
			}

			std::cout << "label " << lab(pp) << ":  max distance = " << resI << ",  max point = " << resP << std::endl;
		}
		std::cout  << std::endl;
		return dmap;
	}

	



} // end of namepace my


#endif // ndef ANALYZE_HH
