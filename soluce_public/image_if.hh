#ifndef IMAGE_IF_HH
# define IMAGE_IF_HH

# include "image2d.hh"

namespace my
{

	template <typename D, typename F>
	class domaine_if
	{
	public:
		typedef typename D::point_type point_type;

		domaine_if(D& d, F& f):dom(d),fon(f){
		};

		domaine_if(const D& d,const F& f):dom(d),fon(f){
		};

		domaine_if(D& d,const F& f):dom(d),fon(f){
		};

		domaine_if(const D& d,F& f):dom(d),fon(f){
		};

		domaine_if(const domaine_if<D,F> &d):dom(d.getD()),fon(d.getF()){

		}

		domaine_if<D,F>& exact() { return *(domaine_if<D,F>*)(void*)this; }
		const domaine_if<D,F>& exact() const { return *(const domaine_if<D,F>*)(const void*)this; }

		bool has(const point_type &p){
			return dom.has(p) && fon(p);
		}

		bool has(const point_type &p)const{
			return dom.has(p) && fon(p);
		}

		D getD()const {return dom;}

		F getF()const {return fon;}

		D& getD() {return dom;}

		F& getF() {return fon;}
		
	private:
		D dom;
		F fon;
	};

	template <typename D, typename F>
	class domaine_if_iterator
	{
	public:
		domaine_if_iterator(D& d, F& f){
			dom = d;
			fon = f;
			//std::cout << dom.pmin() << " " << dom.pmax() << std::endl;
		};

		domaine_if_iterator(domaine_if<D,F> d):dom(d.getD()), fon(d.getF()){
			//std::cout << dom.pmin() << " " << dom.pmax() << " " << dom.pmax().row << std::endl;
		};

		void start(){
			p_ = dom.pmin();
			if(fon(p_) == 0) next();
			//std::cout << p_ << "truc de ouf de merde " << (fon(point2d(3,4))==1 && dom.has(point2d(3,4))) << std::endl;
			truc=1;
			/*
			if(!dom.has(p_) ||fon(p_) == false) {
				std::cout << "fuck it" <<std::endl;
				next();
			}
			std::cout  << "fon\n" << fon << "\n" <<  std::endl;*/
		}

		bool is_valid(){
			typename D::point_type p = p_;
			//std::cout << "super point " << p << std::endl;
			if(truc==1){
				truc=0;
				return 1;
			}
			while(p.row <= dom.pmax().row){
				//std::cout << "super point de merde " << p << " et le point de chiotte " << p_ << std::endl;
				p.col += 1;
				if (p.col > dom.pmax().col)
				{
					p.row += 1;
					p.col = dom.pmin().col;
				}
				if(dom.has(p) && fon(p) == 1) return 1;
				//std::cout << "point " << p << std::endl;
			}
			

			return 0;
		}

		void next(){
			if (not is_valid())	std::abort();
			p_.col += 1;
			if (p_.col > dom.pmax().col)
			{
				p_.row += 1;
				p_.col = dom.pmin().col;
			}
			if(!dom.has(p_) || fon(p_) == 0) next();
		}
		
		operator point2d() const // converter to point2d
	    {
	      return p_;
	    }
    
	private:
		D& dom;
		F& fon;
		typename D::point_type p_;
		int truc;
	};

	
  // FIXME: cut
	template <typename I, typename F>
	class image_if : public Image<image_if<I,F> >
	{
	public:
		typedef typename I::value_type value_type;

		typedef domaine_if<typename I::domain_type,F> domain_type;
		typedef typename I::point_type point_type;
		typedef domaine_if_iterator<typename I::domain_type,F> p_iterator_type;
		typedef typename I::n_iterator_type n_iterator_type;

		image_if(Image<I>& ima, const F& f)
		: ima_(ima.exact()),
		f_(f.exact()),
		dom(ima.exact().domain(),f)
		{
			std::cout<<"attention truc de merde !" << std::endl;
			fancy_print(f_,f_.domain());
		};

		image_if( Image<I>& ima, F& f)
		: ima_(ima.exact()),
		f_(f.exact()),
		dom(ima.exact().domain(),f)
		{
			
		};

		/*image_if(image_if<I,F>& ima):
		ima_(ima.getIma().exact()),
		f_(ima.getF()),
		dom(ima.domain())
		{

		}*/

		image_if(domain_type d):
		ima_(ima2_.exact()),
		ima2_(d.getD()),
		f_(d.getF()),
		dom(ima2_.exact().domain(),d.getF()){
			
		};

	    template <typename U>
	    struct with_value_type {
	    	typedef image_if<image2d<U>,F> ret;
	    };

	    /*image_if<I,F>& operator=(const image_if<I,F>& ima)
		ima_(ima.getIma().exact()),
		f_(ima.getF()),
		dom(ima.domain())
		{
			ima_ = new I(ima.getIma());
			f_ = new F()
			return *this;
	    };*/

		value_type& operator()(const point_type& p) const
		{
			
			if (not ima_.domain().has(p)) std::abort();

			//if(f_(p)==false) return -1;
			//return ima_(p);/*
			int i = ima_.domain().index_of(p);
			//std::cout << "truc" << i << std::endl;
		    if (i < 0 or i >= int(ima_.getData().size())) std::abort();
		    return ima_.getData()[i];
		}

		value_type& operator()(const point_type& p)
		{
			if (not ima_.domain().has(p)) std::abort();
			//if(f_(p)==false) return -1;
			//return ima_(p);
			int i = ima_.domain().index_of(p);
			//std::cout << "truc " << i << std::endl;
		    if (i < 0 or i >= int(ima_.getData().size())) std::abort();
		    return ima_.getData()[i];
		}



		const domain_type& domain() const
		{
			return dom.exact();
		}

		const I& getIma(){return ima_;}
		const F& getF(){return f_;}

		const I& getIma()const{return ima_;}
		const F& getF()const{return f_;}


	private:
		I& ima_;
		I ima2_;
		const F& f_;
		domain_type dom;
	};

	

	

	template <typename I, typename F>
	image_if<I,F>
	make_image_if( Image<I>& ima, F& f)
	{
		//std::cout<<"attention truc de merde !" << std::endl;
		//fancy_print(f,f.domain());
		return image_if<I,F>(ima, f);
	}


} // end of namespace my



#endif // ndef IMAGE_IF_HH
