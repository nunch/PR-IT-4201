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
  // FIXME: cut
	template <typename I, typename F>
	class image_if : public Image<image_if<I,F> >
	{
	public:
		typedef typename F::value_type value_type;

		typedef domaine_if<typename I::domain_type,F> domain_type;
		typedef typename I::point_type point_type;
		typedef typename I::p_iterator_type p_iterator_type;
		typedef typename I::n_iterator_type n_iterator_type;

		image_if(const Image<I>& ima, F f)
		: ima_(ima.exact()),
		f_(f),
		dom(ima.exact().domain(),f)
		{
		};

		value_type operator()(const point_type& p) const
		{
			if (not ima_.domain().has(p))
				std::abort();
			if(f_(p)==false) return -1;
			return ima_(p);
		}

		const domain_type& domain() const
		{
			return dom.exact();
		}

	private:
		const I& ima_;
		F f_;
		domain_type dom;
	};

	

	template <typename D, typename F>
	class domaine_if_iterator
	{
	public:
		domaine_if_iterator(D& d, F& f){
			dom = d;
			fon = f;
		};

		void start(){
			p_ = dom.pmin();
		}

		bool is_valid(){
			return p_.row <= dom.pmax().row;
		}

		void next(){
			if (not is_valid())
					std::abort();
			p_.col += 1;
			if (p_.col > dom.pmax().col)
			{
				p_.row += 1;
				p_.col = dom.pmin().col;
			}if(!dom.has(p_) || fon(p_) == false) next();
		}
		
	private:
		D& dom;
		F& fon;
		typename D::point_type p_;
	};

	template <typename I, typename F>
	image_if<I,F>
	make_image_if(const Image<I>& ima, F f)
	{
		return image_if<I,F>(ima, f);
	}


} // end of namespace my



#endif // ndef IMAGE_IF_HH
