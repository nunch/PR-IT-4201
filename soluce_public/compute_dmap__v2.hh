#ifndef COMPUTE_DMAP__V2_HH
# define COMPUTE_DMAP__V2_HH

# include <queue>
# include "image2d.hh"


namespace my
{


	/*
		for all p in D
		,  dmap <- max

		for all p in D
		,  if input(p) = true
		,  ,  dmap(p) <- 0
		,  ,  for all n in N(p) and in D
		,  ,  ,  if input(n) = false
		,  ,  ,  ,  q.push(p)
		,  ,  ,  ,  break

		while q is not empty
		,  p <- q.pop()
		,  for all n in N(p)
		,  ,  if (dmap(n) = max)
		,  ,  ,  dmap(n) <- dmap(p) + 1
		,  ,  ,  q.push(n)
	*/




	template <typename I, typename F>
		typename I::template with_value_type<unsigned>::ret
		compute_dmap__v2(const Image<I>& input_, F& f)
		{
			typedef typename I::point_type point_type;
			typedef typename I::domain_type domain_type;
			typedef typename I::p_iterator_type p_iterator_type;
			typedef typename I::n_iterator_type n_iterator_type;

			typedef typename I::template with_value_type<unsigned>::ret dmap_type;

			const I& input = input_.exact();
			domain_type D = input.domain();

			const unsigned max = -1;
			dmap_type dmap(D);


			p_iterator_type p(D);
			for_all(p) {
				dmap(p) = max;
			}
			dmap(p) = max;
			f.prev(p)=point2d(0,0);

			std::queue<point_type> q;
			std::queue<point_type> seed;
			n_iterator_type n;

			for_all(p)
			if (input(p) != 0)
			{
				// FIXME: cut
				dmap(p) = 0;
			  	n.center_at(p);
			  	for (n.start(); n.is_valid(); n.next())
			  	  if (D.has(n) and input(n) == false)
			  	    {
			  	    	seed.push(p);
			  	    	q.push(p);
			      		break;
			  	    }
			}
			if (input(p) != 0)
			{
				// FIXME: cut
				dmap(p) = 0;
			  	n.center_at(p);
			  	for (n.start(); n.is_valid(); n.next())
			  	  if (D.has(n) and input(n) == false)
			  	    {
			  	    	q.push(p);
			      		break;
			  	    }
			}

			while (not q.empty())
			{
			 	point_type p = q.front();
			 	q.pop();
			 	n.center_at(p);
			 	for_all(n){

				 	if (D.has(n) and dmap(n) == max)
				 	{
				 		dmap(n) = dmap(p) + 1;
	  	      			q.push(n);
	  	      			f.prev(n)=p;
	  	      			f.next(p)=n;
				 	}
				}
		 	}

		 	while(not seed.empty()){
		 		point_type p = seed.front();
		 		seed.pop();
		 		//f.iz(p)=input.getIma()(p);
		 		int i=input.getIma()(p);
		 		point_type p2 = f.next(p);
		 		std::cout << p << " " << p2 << std::endl;
		 		while(p!=p2){
		 			f.iz(p)=i;
		 			p=p2;
		 			p2=f.next(p);
		 		}
		 		f.iz(p)=i;
		 	}
		 	
		 return dmap;
	 }

	 template <typename I>
		typename I::template with_value_type<unsigned>::ret
		compute_dmap__v2(const Image<I>& input_)
		{
			typedef typename I::point_type point_type;
			typedef typename I::domain_type domain_type;
			typedef typename I::p_iterator_type p_iterator_type;
			typedef typename I::n_iterator_type n_iterator_type;

			typedef typename I::template with_value_type<unsigned>::ret dmap_type;

			const I& input = input_.exact();
			domain_type D = input.domain();

			const unsigned max = -1;
			dmap_type dmap(D);

			p_iterator_type p(D);
			for_all(p)
			dmap(p) = max;

			std::queue<point_type> q;
			n_iterator_type n;

			for_all(p)
			if (input(p) != 0)
			{
				// FIXME: cut
				dmap(p) = 0;
			  	n.center_at(p);
			  	for (n.start(); n.is_valid(); n.next())
			  	  if (D.has(n) and input(n) == false)
			  	    {
			      		q.push(p);
			      		break;
			  	    }
			}

			while (not q.empty())
			{
			 point_type p = q.front();
			 q.pop();
			 n.center_at(p);
			 for_all(n)
			 if (D.has(n) and dmap(n) == max)
			 {
				dmap(n) = dmap(p) + 1;
  	      		q.push(n);
			 }
		 }

		 return dmap;
	 }

	  template <typename I>
		typename I::template with_value_type<unsigned>::ret
		compute_dmap__v2v2(const Image<I>& input_)
		{
			typedef typename I::point_type point_type;
			typedef typename I::domain_type domain_type;
			typedef typename I::p_iterator_type p_iterator_type;
			typedef typename I::n_iterator_type n_iterator_type;

			typedef typename I::template with_value_type<unsigned>::ret dmap_type;

			const I& input = input_.exact();
			domain_type D = input.domain();

			const unsigned max = -1;
			dmap_type dmap(D);

			p_iterator_type p(D);
			for_all(p) {
				dmap(p) = max;
			}
			dmap(p) = max;

			std::queue<point_type> q;
			n_iterator_type n;

			for_all(p)
			if (input(p) != 0)
			{
				// FIXME: cut
				dmap(p) = 0;
			  	n.center_at(p);
			  	for (n.start(); n.is_valid(); n.next())
			  	  if (D.has(n) and input(n) == false)
			  	    {
			  	    	std::cout << p << std::endl;
			      		q.push(p);
			      		break;
			  	    }
			}
			if (input(p) != 0)
			{
				// FIXME: cut
				dmap(p) = 0;
			  	n.center_at(p);
			  	for (n.start(); n.is_valid(); n.next())
			  	  if (D.has(n) and input(n) == false)
			  	    {
			  	    	q.push(p);
			      		break;
			  	    }
			}

			while (not q.empty())
			{
			 	point_type p = q.front();
			 	q.pop();
			 	n.center_at(p);
			 	for_all(n){

				 	if (D.has(n) and dmap(n) == max)
				 	{
				 		dmap(n) = dmap(p) + 1;
	  	      			q.push(n);
				 	}
				}
		 	}
		 	//dmap(point2d(2,4))=10;
		 return dmap;
	 }



	// FIXME: cut



} // end of namespace my


#endif // ndef COMPUTE_DMAP__V2_HH
